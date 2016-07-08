/*
 * Copyright (C) 2015-2016 by Saratoga Data Systems, Inc.
 * All Rights Reserved.
 *
 * Author: Matthew Voss
 */
#include "configtransfer.h"

extern LIBSSH2_SESSION *session;
extern QSettings *prefs;
ConfigTransfer::ConfigTransfer(QString name) : QObject()
{
    serverName = name;
}

void
ConfigTransfer::begin()
{
    emit starting();

    qDebug() << "Starting config transfer to server" << serverName;

    LIBSSH2_SFTP *sftp_session;

    sftp_session = libssh2_sftp_init(session);

    emit beat();

    LIBSSH2_SFTP_HANDLE *sftp_handle;

    if ((sftp_handle = libssh2_sftp_open(sftp_session, "/tmp/flumeConfig",
                                    LIBSSH2_FXF_CREAT | LIBSSH2_FXF_TRUNC | LIBSSH2_FXF_WRITE,
                                    LIBSSH2_SFTP_S_IRUSR | LIBSSH2_SFTP_S_IWUSR | LIBSSH2_SFTP_S_IRGRP | LIBSSH2_SFTP_S_IROTH)) == NULL) {
        qDebug() << "Failed to open temp config file";
        emit finishing();
        return;
    }

    prefs->beginGroup(serverName);

    QStringList configuration = prefs->allKeys();

    for (int i = 0; i < configuration.size(); i++) {
        if (configuration[i] != "targetName" &&
                configuration[i] != "targetHostname" &&
                configuration[i] != "targetDirectory" &&
                configuration[i] != "targetUsername" &&
                configuration[i] != "targetPort") {
            QString line;
            line.append(configuration[i]).append(" ").append(prefs->value(configuration[i]).toString());
            line += "\n";
            qDebug() << line;

            emit beat();

            char *data = strdup(line.toLocal8Bit().data());

            int nread = strlen(data);
            int rc = 0;

            do {
                /* write data in a loop until we block */
                rc = libssh2_sftp_write(sftp_handle, data, nread);

                if(rc < 0) {
                    break;
                }

                data += rc;
                nread -= rc;
            } while (nread);
        }
    }

    prefs->endGroup();

    libssh2_sftp_close(sftp_handle);

    libssh2_sftp_shutdown(sftp_session);

    emit beat();

    emit finishing();
}
