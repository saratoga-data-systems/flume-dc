#include "progressdialog.h"
#include "ui_progressdialog.h"

LIBSSH2_SESSION *session;
int sock;
extern QSettings *prefs;

ProgressDialog::ProgressDialog(QWidget *parent, QString name, QString file) :
    QDialog(parent),
    ui(new Ui::ProgressDialog)
{
    ui->setupUi(this);

    serverName = name;
    fileName = file;

    ui->progressBar->setValue(0);

    err = 0;

    fp = new QProcess;

    prefs->beginGroup(serverName);

    QStringList configuration = prefs->allKeys();

    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QString flumeConfigPath = appDataPath + "/flumeConfig";
    QFile outfile(flumeConfigPath);

    outfile.open(QIODevice::WriteOnly | QIODevice::Text);

    for (int i = 0; i < configuration.size(); i++) {
        if (configuration[i] != "targetName" &&
                configuration[i] != "targetHostname" &&
                configuration[i] != "targetDirectory" &&
                configuration[i] != "targetUsername" &&
                configuration[i] != "targetPassword" &&
                configuration[i] != "targetPort") {
            QString line;
            line.append(configuration[i]).append(" ").append(prefs->value(configuration[i]).toString());
            line += "\n";
            qDebug() << line;

            increment();

            QByteArray a = line.toLocal8Bit();

            outfile.write(a, a.size());

            increment();
        }
    }

    prefs->endGroup();

    outfile.close();

    QStringList args;

    args << "-f" << flumeConfigPath.replace("/", "\\").replace("C:","") << "-summon" << prefs->value(name + "/summonMethod", "ssh").toString() + ":" + prefs->value(name + "/targetPort", "22").toString() << file.replace("/", "\\") << prefs->value(name + "/targetUsername", "flumer").toString() + "@" + prefs->value(name + "/targetHostname", "localhost").toString() + ":" + prefs->value(name + "/targetDirectory", "/tmp").toString();

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("PATH", "C:\\bin\\");

    QStringList sargs;
    sargs << "/c" << "ssh.exe" << "-o" << "StrictHostKeyChecking=no" << "-p" << prefs->value(name + "/targetPort", "22").toString() << prefs->value(name + "/targetUsername", "flumer").toString() + "@" + prefs->value(name + "/targetHostname", "localhost").toString() << "exit";

    fp->setEnvironment(env.toStringList());
    fp->start("C:\\WINDOWS\\System32\\cmd.exe", sargs);
    qDebug() << sargs;

    fp->waitForFinished();

    connect(fp, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(directFinished(int, QProcess::ExitStatus)));
    connect(fp, &QProcess::readyReadStandardError, this, &ProgressDialog::printOutput);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &ProgressDialog::stop);
    fp->setEnvironment(env.toStringList());
    fp->start("C:\\bin\\flume.exe", args);
    qDebug() << args;

    //socketConnect();
}
void ProgressDialog::stop() {
    qDebug() << "Flume process stopped";
    fp->kill();
    returnCode = 200;
    close();
}

ProgressDialog::~ProgressDialog()
{
    //sshDisconnect();
    delete ui;
}

void
ProgressDialog::printOutput()
{
    qDebug("%s", fp->readAllStandardError().data());
    increment();
}

int
ProgressDialog::returnValue()
{
    return returnCode;
}

void
ProgressDialog::directFinished(int code, QProcess::ExitStatus exit)
{
        QMessageBox msg;
        QString error;

        if (code >= 200) {
            error = "File Not Transferred";
        } else {
            error = "File Transferred";
        }

        msg.setText(error);
        msg.exec();

        returnCode = code;

        qDebug() << "ret: " << code;

        close();
}

void
ProgressDialog::socketConnect()
{
    if (err != 0) {
        return;
    }

    QThread *th = new QThread(this);
    SshConnect *sc = new SshConnect(0, prefs->value("proxyHostname", "localhost").toString(), prefs->value("proxyPort", "22").toString());

    sc->moveToThread(th);

    connect(th, &QThread::started, sc, &SshConnect::begin);
    connect(sc, &SshConnect::error, this, &ProgressDialog::fileError);
    connect(sc, &SshConnect::beat, this, &ProgressDialog::increment);
    connect(sc, &SshConnect::finished, this, &ProgressDialog::transferConfig);

    th->start();
}

void
ProgressDialog::transferConfig()
{
    if (err != 0) {
        return;
    }

    qDebug() << "Transfering configuration for server" << serverName;
    ConfigTransfer *ct = new ConfigTransfer(serverName);
    QThread *th = new QThread;

    ct->moveToThread(th);

    connect(th, &QThread::started, ct, &ConfigTransfer::begin);
    connect(ct, &ConfigTransfer::error, this, &ProgressDialog::fileError);
    connect(ct, &ConfigTransfer::finishing, this, &ProgressDialog::startFileTransfer);
    connect(ct, &ConfigTransfer::beat, this, &ProgressDialog::increment);

    th->start();
}

void
ProgressDialog::transferFinished()
{
    QMessageBox s;
    s.setText("File transfer succeded");
    s.setWindowTitle("Success");
    s.exec();

    close();
}

void
ProgressDialog::startFileTransfer()
{
    if (err != 0) {
        return;
    }

    qDebug() << "Transfering File: " << fileName;

    FileTransfer *ft = new FileTransfer(NULL, fileName, serverName);
    QThread *th = new QThread;

    ft->moveToThread(th);

    connect(th, &QThread::started, ft, &FileTransfer::begin);
    connect(ft, &FileTransfer::beat, this, &ProgressDialog::increment);
    connect(ft, &FileTransfer::error, this, &ProgressDialog::fileError);
    connect(ft, &FileTransfer::finished, this, &ProgressDialog::transferFinished);

    th->start();
}

void
ProgressDialog::fileError(QString signal)
{
    err = 1;
    QMessageBox mesg;
    mesg.setText(signal);
    mesg.setWindowTitle("Error");
    mesg.exec();
}

void
ProgressDialog::increment()
{
    ui->progressBar->setValue(ui->progressBar->value() + 1);
}

void
ProgressDialog::sshDisconnect()
{
    qDebug() << "Disconnecting";

    libssh2_session_disconnect(session, "So long, and thanks for all the fish!");

    libssh2_session_free(session);

    libssh2_exit();

    closesocket(sock);

    WSACleanup();
}
