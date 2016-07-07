#include "progressdialog.h"
#include "ui_progressdialog.h"

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
    killAll = 0;

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

    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &ProgressDialog::stop);

    fp->setEnvironment(env.toStringList());
    fp->start("C:\\bin\\flume.exe", args);
}

void ProgressDialog::stop() {
    qDebug() << "Flume process stopped";
    fp->kill();
    returnCode = 200;
    close();
}

ProgressDialog::~ProgressDialog()
{
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
