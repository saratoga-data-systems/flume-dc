#ifndef VERIFYCONFIG_H
#define VERIFYCONFIG_H

#include <libssh2.h>
#include <QObject>
#include <QSettings>
#include <QMessageBox>
#include <QtDebug>
#include <cstring>
#include <ws2tcpip.h>

class VerifyConfig : public QObject
{
    Q_OBJECT

public:
    VerifyConfig(QObject *parent = 0);

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

#endif // VERIFYCONFIG_H
