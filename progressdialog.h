#ifndef PROGRESSDIALOG_H
#define PROGRESSDIALOG_H

#include <QDialog>
#include <QDebug>
#include <QSettings>
#include <QMessageBox>
#include <QProcessEnvironment>
#include <QProcess>
#include <QThread>
#include <QStandardPaths>
#include <QFile>
#include <string>
#include <cstring>

#include "configtransfer.h"
#include "filetransfer.h"
#include "sshconnect.h"

namespace Ui {
class ProgressDialog;
}

class ProgressDialog : public QDialog
{
    Q_OBJECT

public:
    explicit ProgressDialog(QWidget *parent = 0, QString name = "", QString files = "");
    ~ProgressDialog();

public slots:
    void increment();
    void fileError(QString signal);
    void transferFinished();
    void printOutput();
    void directFinished(int code, QProcess::ExitStatus exit);
    int returnValue();

private:
    Ui::ProgressDialog *ui;
    void socketConnect();
    void transferConfig();
    void startFileTransfer();
    void sshDisconnect();
    QString fileName;
    QString serverName;
    QProcess *fp;
    int err;
    int returnCode;
};

#endif // PROGRESSDIALOG_H
