/*
 * Copyright (C) 2015-2016 by Saratoga Data Systems, Inc.
 * All Rights Reserved.
 *
 * Author: Matthew Voss
 */
#include "verifyprogress.h"
#include "ui_verifyprogress.h"

VerifyProgress::VerifyProgress(QWidget *parent, QString name) :
    QDialog(parent),
    ui(new Ui::VerifyProgress)
{
    ui->setupUi(this);


    serverName = name;

    QString msg("Validating configuration for destination ");

    setWindowTitle(msg + serverName);

    ui->progressBar->setValue(0);

    fp = new QProcess;
    connect(fp, SIGNAL(finished(int, QProcess::ExitStatus)), this, SLOT(directFinished(int, QProcess::ExitStatus)));
    connect(fp, &QProcess::readyReadStandardError, this, &VerifyProgress::printOutput);

    prefs->beginGroup(serverName);

    QStringList configuration = prefs->allKeys();

    QString appDataPath = "C:\\Flume\\etc";
    QString flumeConfigPath = appDataPath + "/flumeConfig";
    QFile outfile(flumeConfigPath);

    outfile.open(QIODevice::WriteOnly | QIODevice::Text);

    for (int i = 0; i < configuration.size(); i++) {
        if (configuration[i] != "targetName" &&
                configuration[i] != "targetHostname" &&
                configuration[i] != "targetDirectory" &&
                configuration[i] != "targetUsername" &&
                configuration[i] != "targetPassword" &&
                configuration[i] != "targetPort") {
            QString line;
            line.append(configuration[i]).append(" ").append(prefs->value(configuration[i]).toString());
            line += "\n";
            qDebug() << line;

            increment();

            QByteArray a = line.toLocal8Bit();

            outfile.write(a, a.size());

            increment();
        }
    }

    prefs->endGroup();

    outfile.close();

    QStringList args;

    args << "-f" << flumeConfigPath.replace("/", "\\") << prefs->value(name + "/targetUsername", "flumer").toString() + "@" + prefs->value(name + "/targetHostname", "localhost").toString();

    qDebug() << args;

    QProcessEnvironment env = QProcessEnvironment::systemEnvironment();
    env.insert("PATH", "C:\\Flume\\bin\\");

    fp->setEnvironment(env.toStringList());
    fp->start("C:\\Flume\\bin\\flume_validate.exe", args);
}

VerifyProgress::~VerifyProgress()
{
    delete ui;
}

void
VerifyProgress::increment()
{
    ui->progressBar->setValue(ui->progressBar->value() + 1);
}

void
VerifyProgress::printOutput()
{
    qDebug("%s", fp->readAllStandardError().data());
    increment();
}

void
VerifyProgress::directFinished(int code, QProcess::ExitStatus exit)
{
        QString error("Configuration for destination ");
        error += serverName;

        if (code >= 200) {
            emit invalid();
            error += " is invalid.";
        } else {
            error += " is valid.";
        }

        QMessageBox msg;
        msg.setText(error);
        msg.exec();


        close();
}
