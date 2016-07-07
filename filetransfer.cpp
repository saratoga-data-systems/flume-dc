#include "filetransfer.h"

extern LIBSSH2_SESSION *session;
extern QSettings *prefs;

FileTransfer::FileTransfer(QObject *parent, QString file, QString name) : QObject(parent)
{
    serverName = name;
    fileName = file;
}

void
FileTransfer::begin()
{
    emit beginning();

    qDebug() << "Transfering file" << fileName << "to destination " << serverName;

    LIBSSH2_CHANNEL *channel;

    if ((channel = libssh2_channel_open_session(session)) == NULL) {
        qDebug() << "Couldn't allocate channel struct";
        emit error("Couldn't allocate channel struct");
        emit finished();
        return;
    }

    emit beat();

    QStringList path = fileName.split('/');

    QString command = "flume -f /tmp/flumeConfig ";
    command.append("- ")
            .append(prefs->value(serverName + "/targetUsername").toString())
            .append("@")
            .append(prefs->value(serverName + "/targetHostname").toString())
            .append(":")
            .append(prefs->value(serverName + "/targetDirectory").toString())
            .append("/")
            .append(path.last());

    qDebug() << command;

    if (libssh2_channel_exec(channel, command.toLocal8Bit().data())) {
        qDebug() << "Couldn't run command on remote host";
        emit error("Couldn't run command on remote host");
        emit finished();
        return;
    }

    emit beat();

    char buf[1000];

    QFile input(fileName);

    if (!input.open(QIODevice::ReadOnly | QIODevice::Text)) {
        qDebug() << "Couldn't open file to be transfered";
        emit error("Couldn't open file to be transfered");
        emit finished();
        return;
    }

    QDataStream stream(&input);


    while(!stream.atEnd()) {
        int size = stream.readRawData(buf, sizeof(buf));
        int retry = 0;
        while(libssh2_channel_write(channel, buf, size) < size && retry++ < 5);

        emit beat();

        if (retry == 4) {
            emit error("Unable to write file to channel");
            emit finished();
            return;
        }
    }

    libssh2_channel_send_eof(channel);

    int rc = 0;

    do {
        memset(buf, 0, sizeof(buf));
        rc = libssh2_channel_read_stderr(channel, buf, sizeof(buf));
        qDebug() << buf;
        emit beat();
    } while(rc > 0);

    libssh2_channel_close(channel);

    int status = 0;

    if ((status = libssh2_channel_get_exit_status(channel)) < 0) {
        QString err = "Flume failed with exit status ";
        err += QString::number(status);
        emit error(err);
    }


    if ((status = libssh2_channel_get_exit_status(channel)) > 0) {
        QString err = "Flume exited with warning ";
        err += QString::number(status);
        emit error(err);
    }

    qDebug() << "return code = " << status;


    emit finished();
}

