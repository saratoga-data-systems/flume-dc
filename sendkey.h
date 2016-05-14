#ifndef SENDKEY_H
#define SENDKEY_H

#include <libssh2.h>
#include <QObject>
#include <QSettings>
#include <QMessageBox>
#include <QtDebug>
#include <cstring>
#include <ws2tcpip.h>

class SendKey : public QObject
{
    Q_OBJECT

public:
    SendKey(QObject *parent = 0, QString server = "", QString port = "");

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

#endif // SENDKEY_H
