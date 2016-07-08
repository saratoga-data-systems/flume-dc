/*
 * Copyright (C) 2015-2016 by Saratoga Data Systems, Inc.
 * All Rights Reserved.
 *
 * Author: Matthew Voss
 */
#ifndef CONFIGTRANSFER_H
#define CONFIGTRANSFER_H

#include <QObject>
#include <QDebug>
#include <QSettings>
#include <libssh2.h>
#include <libssh2_sftp.h>

class ConfigTransfer : public QObject
{
    Q_OBJECT

public:
    explicit ConfigTransfer(QString name);
signals:
    void starting();
    void finishing();
    void error(QString signal);
    void beat();
public slots:
    void begin();
private:
    QString serverName;
};

#endif // CONFIGTRANSFER_H
