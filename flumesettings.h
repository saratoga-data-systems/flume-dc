#ifndef FLUMESETTINGS_H
#define FLUMESETTINGS_H

#include <QWidget>
#include <QDebug>
#include <QSettings>
#include <QPushButton>
#include <QValidator>

#include "sshprogress.h"
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

signals:
    void remove(int tabIndex, QString name);

private:
    Ui::FlumeSettings *ui;
    QString serverName;
};

#endif // FLUMESETTINGS_H
