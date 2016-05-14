#ifndef SSHCONNECT_H
#define SSHCONNECT_H

#define _WIN32_WINNT 0x501

#include <QObject>
#include <QString>
#include <QSettings>
#include <QtDebug>
#include <libssh2.h>
#include <cstring>
#include <ws2tcpip.h>

class SshConnect : public QObject
{
    Q_OBJECT

public:
    explicit SshConnect(QObject *parent = 0, QString server = "", QString port = "");
public slots:
    void begin();
signals:
    void started();
    void beat();
    void error(QString code);
    void finished();
private:
    QString serverName;
    QString portNumber;
};

#endif // SSHCONNECT_H
