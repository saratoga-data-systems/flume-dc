#ifndef SERVERDIALOG_H
#define SERVERDIALOG_H

#include <QDialog>
#include <QtDebug>
#include <QString>
#include <QMessageBox>
#include <QInputDialog>
#include <QThread>
#include "flumesettings.h"
#include "verifyprogress.h"

namespace Ui {
class ServerDialog;
}

class ServerDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ServerDialog(QWidget *parent = 0, int index = 0);
    ~ServerDialog();

public slots:
    void addTarget();
    void removeTab(int tabIndex, QString name);
    void verifyConfiguration();
    void invalidate();

private:
    Ui::ServerDialog *ui;
    void addTab(QString name);
};

#endif // SERVERDIALOG_H
