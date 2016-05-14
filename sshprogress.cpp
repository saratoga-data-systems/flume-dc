#include "sshprogress.h"
#include "ui_sshprogress.h"

SshProgress::SshProgress(QWidget *parent, QString server, QString port) :
    QDialog(parent),
    ui(new Ui::SshProgress)
{
    ui->setupUi(this);

    serverName = server;
    portNumber = port;

    setWindowTitle("Saving Configuration for Server " + server);
    sendKey();
}

SshProgress::~SshProgress()
{
    delete ui;
}

void SshProgress::sendKey()
{
    QThread *th = new QThread();

    SendKey *send = new SendKey(NULL, serverName, portNumber);

    send->moveToThread(th);

    connect(th, &QThread::started, send, &SendKey::begin);
    connect(send, &SendKey::error, this, &SshProgress::fileError);
    connect(send, &SendKey::beat, this, &SshProgress::incrementBar);
    connect(send, &SendKey::finished, this, &SshProgress::close);

    th->start();
}

void SshProgress::fileError(QString err)
{
    QMessageBox msg;

    msg.setText(err);

    msg.exec();
}

void SshProgress::incrementBar()
{
    ui->progressBar->setValue(ui->progressBar->value() + 10);
}
