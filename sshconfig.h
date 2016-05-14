#ifndef SSHCONFIG_H
#define SSHCONFIG_H

#include <QDialog>
#include <QSettings>
#include <cstring>

namespace Ui {
class sshconfig;
}

class sshconfig : public QDialog
{
    Q_OBJECT

public:
    explicit sshconfig(QWidget *parent = 0);
    ~sshconfig();
    bool logincheck();
    void sendkey();
    void updateTargetList();
    void updateInformation();

private:
    Ui::sshconfig *ui;
};

#endif // SSHCONFIG_H
