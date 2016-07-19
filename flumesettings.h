/*
 * Copyright (C) 2015-2016 by Saratoga Data Systems, Inc.
 * All Rights Reserved.
 *
 * Author: Matthew Voss
 */
#ifndef FLUMESETTINGS_H
#define FLUMESETTINGS_H

#include <QWidget>
#include <QDebug>
#include <QSettings>
#include <QPushButton>
#include <QValidator>
#include <QFileDialog>

#include "verifyprogress.h"

namespace Ui {
class FlumeSettings;
}

class FlumeSettings : public QWidget
{
    Q_OBJECT

public:
    explicit FlumeSettings(QWidget *parent = 0, QString name = "<uninitialized>");
    ~FlumeSettings();
    int tabIndex;

public slots:
    void saveServer();
    void emitRemove();
    void reset();
    void verifyServer();
    void invalidate();
    void setAllowFileName();
    void setFlexlmLicenseDirectory();
    void setLogDirectory();
    void setPortsFileName();
    void setSshFileName();
    void setRunDirectory();
    void setTempDirectory();

signals:
    void remove(int tabIndex, QString name);

private:
    Ui::FlumeSettings *ui;
    QString serverName;
    void setUi(QString name);
};

#endif // FLUMESETTINGS_H
