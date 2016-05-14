#ifndef VERIFYPROGRESS_H
#define VERIFYPROGRESS_H

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

extern QSettings *prefs;

namespace Ui {
class VerifyProgress;
}

class VerifyProgress : public QDialog
{
    Q_OBJECT

public:
    explicit VerifyProgress(QWidget *parent = 0, QString name = "");
    ~VerifyProgress();

public slots:
    void printOutput();
    void directFinished(int code, QProcess::ExitStatus exit);

signals:
    void invalid();

private:
    Ui::VerifyProgress *ui;
    void increment();
    QString serverName;
    QProcess *fp;
};

#endif // VERIFYPROGRESS_H
