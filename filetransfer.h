/*
 * Copyright (C) 2015-2016 by Saratoga Data Systems, Inc.
 * All Rights Reserved.
 *
 * Author: Matthew Voss
 */
#ifndef FILETRANSFER_H
#define FILETRANSFER_H

#include <QObject>
#include <QtDebug>
#include <QSettings>
#include <QFile>
#include <QDataStream>
#include <QMessageBox>
#include <libssh2.h>

class FileTransfer : public QObject
{
    Q_OBJECT

public:
    explicit FileTransfer(QObject *parent = 0, QString file = "", QString name = "");
public slots:
    void begin();
signals:
    void beginning();
    void finished();
    void error(QString code);
    void beat();
private:
    QString serverName;
    QString fileName;
};

#endif // FILETRANSFER_H
