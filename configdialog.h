#ifndef CONFIGDIALOG_H
#define CONFIGDIALOG_H

#include <QDialog>
#include <QSettings>

namespace Ui {
class ConfigDialog;
}

class ConfigDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ConfigDialog(QWidget *parent = 0);
    ~ConfigDialog();

public slots:
    void saveConfig();


private:
    Ui::ConfigDialog *ui;
    QString serverName;
};

#endif // CONFIGDIALOG_H
