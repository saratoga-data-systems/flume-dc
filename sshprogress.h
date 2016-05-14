#ifndef SSHPROGRESS_H
#define SSHPROGRESS_H

#include <QDialog>
#include <QProgressBar>
#include <QThread>
#include <QProcess>
#include <QProgressDialog>

#include "sendkey.h"

namespace Ui {
class SshProgress;
}

class SshProgress : public QDialog
{
    Q_OBJECT

public:
    explicit SshProgress(QWidget *parent = 0, QString server = "", QString port = "");
    ~SshProgress();
    void sendKey();

public slots:
    void fileError(QString msg);
    void incrementBar();

private:
    Ui::SshProgress *ui;
    QString serverName;
    QString portNumber;
    QProcess *fp;
};

#endif // SSHPROGRESS_H
