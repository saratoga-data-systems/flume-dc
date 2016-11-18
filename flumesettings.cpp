/*
 * Copyright (C) 2015-2016 by Saratoga Data Systems, Inc.
 * All Rights Reserved.
 *
 * Author: Matthew Voss
 */
#include "flumesettings.h"
#include "ui_flumesettings.h"

extern QSettings *prefs;

void
setCheckbox(QCheckBox* box, QString name, QString sub)
{
    if (prefs->value(name + sub, "false").toString() == "true") {
        box->setCheckState(Qt::Checked);
    } else {
        box->setCheckState(Qt::Unchecked);
    }
}

void
setCombobox(QComboBox* box, QString name, QString sub)
{
    QString text = prefs->value(name + sub, "").toString();

    int index = box->findText(text);

    box->setCurrentIndex(index);
}

void
setSpinbox(QSpinBox* box, QString name, QString sub)
{
    int n = prefs->value(name + sub, 0).toInt();

    box->setValue(n);
}

FlumeSettings::FlumeSettings(QWidget *parent, QString name) :
    QWidget(parent),
    ui(new Ui::FlumeSettings)
{
    ui->setupUi(this);

    ui->tabWidget->setCurrentIndex(0);
    serverName = name;
    setUi(name);

    connect(ui->pushButton_3, &QPushButton::clicked, this, &FlumeSettings::emitRemove);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &FlumeSettings::reset);
    connect(ui->verifyButton, &QPushButton::clicked, this, &FlumeSettings::verifyServer);
    connect(ui->summonMethodBox, SIGNAL(currentIndexChanged(QString)), this, SLOT(setSummonPort(QString)));

    connect(ui->allowFileNameBrowse, &QPushButton::clicked, this, &FlumeSettings::setAllowFileName);
    connect(ui->flexlmLicenseDirectoryBrowse, &QPushButton::clicked, this, &FlumeSettings::setFlexlmLicenseDirectory);
    connect(ui->logDirectoryBrowse, &QPushButton::clicked, this, &FlumeSettings::setLogDirectory);
    connect(ui->portsFileNameBrowse, &QPushButton::clicked, this, &FlumeSettings::setPortsFileName);
    connect(ui->sshFileNameBrowse, &QPushButton::clicked, this, &FlumeSettings::setSshFileName);
    connect(ui->runDirectoryBrowse, &QPushButton::clicked, this, &FlumeSettings::setRunDirectory);
    connect(ui->tempDirectoryBrowse, &QPushButton::clicked, this, &FlumeSettings::setTempDirectory);

    setWindowTitle("Edit Target List");
}

void
FlumeSettings::setUi(QString name)
{
    ui->targetNameEdit->setText(name);
    ui->targetHostnameEdit->setText(prefs->value(name + "/targetHostname", "localhost").toString());
    ui->targetUsernameEdit->setText(prefs->value(name + "/targetUsername", "flumer").toString());
    ui->targetDirectoryEdit->setText(prefs->value(name + "/targetDirectory", "C:\\Flume\\tmp").toString());
    ui->targetPortEdit->setText(prefs->value(name + "/targetPort", "22").toString());
    ui->targetPortEdit->setValidator(new QIntValidator(0,65535));
    setCombobox(ui->summonMethodBox, name, "/summonMethod");
    setCheckbox(ui->DFBox, name, "/DF");
    ui->MTUEdit_2->setText(prefs->value(name + "/MTU", "1500").toString());
    ui->MTUEdit_2->setValidator(new QIntValidator(68,8192));
    ui->allowFileNameEdit_2->setText(prefs->value(name + "/allowFileName","C:\\Flume\\etc\\allow").toString());
    //setCombobox(ui->checksumSpecBox, name, "/checksumSpec");
    setSpinbox(ui->compressionLevelBox, name, "/compressionLevel");
    //setCombobox(ui->compressionStrategyBox, name, "/compressionStrategy");
    setSpinbox(ui->debugBox, name, "/debug");
    ui->derivativePidFactorEdit_2->setText(prefs->value(name + "/derivativePIDfactor", "0.050000").toString());
    ui->derivativePidFactorEdit_2->setValidator(new QDoubleValidator);
    ui->flexlmLicenseDirectoryEdit_2->setText(prefs->value(name + "/flexlmLicenseDirectory", "C:\\Flume\\etc\\license").toString());
    //setCombobox(ui->hashSpecBox, name, "/hashSpec");
    ui->initSpeedFactorEdit_2->setText(prefs->value(name + "/initSpeedFactor", "100").toString());
    ui->initSpeedFactorEdit_2->setValidator(new QIntValidator);
    ui->integralPidFactorEdit_2->setText(prefs->value(name + "/integralPIDfactor", "0.000000").toString());
    ui->integralPidFactorEdit_2->setValidator(new QDoubleValidator);
    ui->localInterfaceIpEdit_2->setText(prefs->value(name + "/localInterfaceIp", "0.0.0.0").toString());
    ui->logDirectoryEdit_2->setText(prefs->value(name + "/logDirectory","C:\\Flume\\var\\log").toString());
    setCheckbox(ui->measureIPDBox, name, "/measureIPD");
    setCheckbox(ui->numericIdsBox, name, "/numericIds");
    ui->pagePortDefaultEdit_2->setText(prefs->value(name + "/pagePortDefault", "2317").toString());
    ui->pagePortDefaultEdit_2->setValidator(new QIntValidator(68,8192));
    setCheckbox(ui->performFsyncsBox, name, "/performFsyncs");
    ui->portsFileNameEdit_2->setText(prefs->value(name + "/portsFileName", "C:\\Flume\\etc\\ports").toString());
    ui->proportionalPidFactorEdit_2->setText(prefs->value(name + "/proportionalPIDfactor", "0.500000").toString());
    ui->proportionalPidFactorEdit_2->setValidator(new QDoubleValidator);
    ui->sshFileNameEdit_2->setText(prefs->value(name + "/sshFileName", "ssh").toString());
    ui->speedMinimumEdit_2->setText(prefs->value(name + "/speedMinimum", "0.000000").toString());
    ui->speedMinimumEdit_2->setValidator(new QDoubleValidator);
    ui->runDirectoryEdit_2->setText(prefs->value(name + "/runDirectory", "C:\\Flume\\var\\run").toString());
    setCheckbox(ui->remoteBinDirFromLocalBox, name, "/remoteBinDirFromLocal");
    ui->summonTimeoutThresholdEdit_2->setText(prefs->value(name + "/summonTimeoutThreshold", "0").toString());
    ui->summonTimeoutThresholdEdit_2->setValidator(new QIntValidator);
    ui->speedMaximumEdit->setText(prefs->value(name + "/speedMaximum", "60.00000").toString());
    ui->speedMaximumEdit->setValidator(new QDoubleValidator);
    ui->summonPortDefaultEdit_2->setText(prefs->value(name + "/summonPortDefault", "22").toString());
    ui->summonPortDefaultEdit_2->setValidator(new QIntValidator(68,8192));
    setCheckbox(ui->recurseBox, name, "/recurse");
    ui->synIntervalEdit_2->setText(prefs->value(name + "/synInterval", "100").toString());
    ui->synIntervalEdit_2->setValidator(new QIntValidator);
    ui->targetErrorBasisPointsEdit_2->setText(prefs->value(name + "/targetErrorBasisPoints", "200").toString());
    ui->targetErrorBasisPointsEdit_2->setValidator(new QIntValidator);
    ui->tempDirectoryEdit_2->setText(prefs->value(name + "/tempDirectory","C:\\Flume\\tmp").toString());
    ui->timeoutThresholdEdit_2->setText(prefs->value(name + "/timeoutThreshold","1").toString());
    ui->timeoutThresholdEdit_2->setValidator(new QIntValidator);
    ui->uploadSpeedMaximumEdit->setText(prefs->value(name + "/uploadSpeedMaximum","10000.00").toString());
    ui->uploadSpeedMaximumEdit->setValidator(new QDoubleValidator);
    setCheckbox(ui->verboseBox, name, "/verbose");
  }

FlumeSettings::~FlumeSettings()
{
    delete ui;
}

void
FlumeSettings::setSummonPort(QString text)
{
    if (text == "inetd") {
        ui->summonPortDefaultEdit_2->setText("2354");
        ui->targetPortEdit->setText("2354");
    } else if (text == "ssh") {
        ui->summonPortDefaultEdit_2->setText("22");
        ui->targetPortEdit->setText("22");
    } else {
        ui->summonPortDefaultEdit_2->setText("2354");
        ui->targetPortEdit->setText("2354");
    }
}

void
FlumeSettings::setAllowFileName()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Select File"));
    if (file != "") {
        ui->allowFileNameEdit_2->setText(file);
    }
}

void
FlumeSettings::setFlexlmLicenseDirectory()
{
    QFileDialog fd;
    fd.setFileMode(QFileDialog::Directory);
    fd.setOption(QFileDialog::ShowDirsOnly, true);
    QString file = fd.getExistingDirectory(this, tr("Select Directory"));
    if (file != "") {
        ui->flexlmLicenseDirectoryEdit_2->setText(file);
    }
}

void
FlumeSettings::setLogDirectory()
{
    QFileDialog fd;
    fd.setFileMode(QFileDialog::Directory);
    fd.setOption(QFileDialog::ShowDirsOnly, true);
    QString file = fd.getExistingDirectory(this, tr("Select Directory"));
    if (file != "") {
        ui->logDirectoryEdit_2->setText(file);
    }
}

void
FlumeSettings::setPortsFileName()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Select File"));
    if (file != "") {
        ui->portsFileNameEdit_2->setText(file);
    }
}

void
FlumeSettings::setSshFileName()
{
    QString file = QFileDialog::getOpenFileName(this, tr("Select File"));
    if (file != "") {
        ui->sshFileNameEdit_2->setText(file);
    }
}

void
FlumeSettings::setRunDirectory()
{
    QFileDialog fd;
    fd.setFileMode(QFileDialog::Directory);
    fd.setOption(QFileDialog::ShowDirsOnly, true);
    QString file = fd.getExistingDirectory(this, tr("Select Directory"));
    if (file != "") {
        ui->runDirectoryEdit_2->setText(file);
    }
}

void
FlumeSettings::setTempDirectory()
{
    QFileDialog fd;
    fd.setFileMode(QFileDialog::Directory);
    fd.setOption(QFileDialog::ShowDirsOnly, true);
    QString file = fd.getExistingDirectory(this, tr("Select Directory"));
    if (file != "") {
        ui->tempDirectoryEdit_2->setText(file);
    }
}

void
FlumeSettings::reset()
{
    ui->targetHostnameEdit->setText("localhost");
    ui->targetUsernameEdit->setText("flumer");
    ui->targetDirectoryEdit->setText("C:\\Flume\\tmp");
    ui->targetPortEdit->setText("22");
    int i = ui->summonMethodBox->findText("inetd");
    ui->summonMethodBox->setCurrentIndex(i);
    ui->DFBox->setChecked(false);
    ui->MTUEdit_2->setText("1500");
    ui->allowFileNameEdit_2->setText("C:\\Flume\\etc\\allow");
    i = ui->checksumSpecBox->findText("Fletcher32");
    ui->checksumSpecBox->setCurrentIndex(i);
    ui->compressionLevelBox->setValue(0);
    i = ui->compressionStrategyBox->findText("default");
    ui->compressionStrategyBox->setCurrentIndex(i);
    ui->debugBox->setValue(0);
    ui->derivativePidFactorEdit_2->setText("0.050000");
    ui->flexlmLicenseDirectoryEdit_2->setText("C:\\Flume\\etc\\license");
    i = ui->hashSpecBox->findText("MD4");
    ui->hashSpecBox->setCurrentIndex(i);
    ui->initSpeedFactorEdit_2->setText("100");
    ui->integralPidFactorEdit_2->setText("0.000000");
    ui->localInterfaceIpEdit_2->setText("0.0.0.0");
    ui->logDirectoryEdit_2->setText("C:\\Flume\\var\\log");
    ui->measureIPDBox->setChecked(false);
    ui->numericIdsBox->setChecked(false);
    ui->pagePortDefaultEdit_2->setText("2317");
    ui->performFsyncsBox->setChecked(false);
    ui->portsFileNameEdit_2->setText("C:\\Flume\\etc\\ports");
    ui->proportionalPidFactorEdit_2->setText("0.500000");
    ui->sshFileNameEdit_2->setText("ssh");
    ui->speedMinimumEdit_2->setText("0.000000");
    ui->runDirectoryEdit_2->setText("C:\\Flume\\var\\run");
    ui->remoteBinDirFromLocalBox->setChecked(false);
    ui->remoteBinDirFromLocalBox->setChecked(false);
    ui->summonTimeoutThresholdEdit_2->setText("0");
    ui->speedMaximumEdit->setText("60.00000");
    ui->summonPortDefaultEdit_2->setText("22");
    ui->recurseBox->setChecked(false);
    ui->synIntervalEdit_2->setText("100");
    ui->targetErrorBasisPointsEdit_2->setText("200");
    ui->tempDirectoryEdit_2->setText("C:\\Flume\\tmp");
    ui->timeoutThresholdEdit_2->setText("1");
    ui->uploadSpeedMaximumEdit->setText("10000.00");
    ui->verboseBox->setChecked(false);
}

void
FlumeSettings::emitRemove()
{
    QMessageBox ask;

    ask.setWindowTitle("Flume");
    ask.setText("Are you sure you want to remove this destination?");
    ask.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    ask.setDefaultButton(QMessageBox::No);

    if (ask.exec() != QMessageBox::No) {
        saveServer();

        emit remove(tabIndex, ui->targetNameEdit->text());
        qDebug() << "Remove self";
    }
}

void
FlumeSettings::verifyServer()
{
    if (!QFile::exists("C:\\Flume\\bin\\flume_validate.exe")) {
        QMessageBox msg;
        msg.setWindowTitle("Flume DC Error");
        msg.setText("Please install Flume and try again.");
        msg.exec();
        return;
    }
    VerifyProgress *vp = new VerifyProgress(NULL, serverName);
    connect(vp, &VerifyProgress::invalid, this, &FlumeSettings::invalidate);
    ui->verifyLabel->setText("Valid");

    vp->exec();

}

void
FlumeSettings::invalidate()
{
    ui->verifyLabel->setText("Invalid");
}

void
FlumeSettings::saveServer()
{
    qDebug() << "Saving Server";

    QString name = ui->targetNameEdit->text();

    prefs->setValue(name + "/targetHostname", ui->targetHostnameEdit->text());
    prefs->setValue(name + "/targetPort", ui->targetPortEdit->text());
    prefs->setValue(name + "/targetUsername", ui->targetUsernameEdit->text());
    prefs->setValue(name + "/targetDirectory", ui->targetDirectoryEdit->text());
    prefs->setValue(name + "/summonMethod", ui->summonMethodBox->currentText());
    prefs->setValue(name + "/DF", ui->DFBox->isChecked() ? "true" : "false");
    prefs->setValue(name + "/MTU", ui->MTUEdit_2->text());
    prefs->setValue(name + "/allowFileName", ui->allowFileNameEdit_2->text());
    prefs->setValue(name + "/checksumSpec", ui->checksumSpecBox->currentText());
    prefs->setValue(name + "/compressionLevel", ui->compressionLevelBox->value());
    prefs->setValue(name + "/compressionStrategy", ui->compressionStrategyBox->currentText());
    prefs->setValue(name + "/debug", ui->debugBox->value());
    prefs->setValue(name + "/derivativePIDfactor", ui->derivativePidFactorEdit_2->text());
    prefs->setValue(name + "/flexlmLicenseDirectory", ui->flexlmLicenseDirectoryEdit_2->text());
    prefs->setValue(name + "/hashSpec", ui->hashSpecBox->currentText());
    prefs->setValue(name + "/initSpeedFactor", ui->initSpeedFactorEdit_2->text());
    prefs->setValue(name + "/integralPIDfactor", ui->integralPidFactorEdit_2->text());
    prefs->setValue(name + "/localInterfaceIp", ui->localInterfaceIpEdit_2->text());
    prefs->setValue(name + "/logDirectory", ui->logDirectoryEdit_2->text());
    prefs->setValue(name + "/measureIPD", ui->measureIPDBox->isChecked() ? "true" : "false");
    prefs->setValue(name + "/numericIds", ui->numericIdsBox->isChecked() ? "true" : "false");
    prefs->setValue(name + "/pagePortDefault", ui->pagePortDefaultEdit_2->text());
    prefs->setValue(name + "/performFsyncs", ui->performFsyncsBox->isChecked() ? "true" : "false");
    prefs->setValue(name + "/portsFileName", ui->portsFileNameEdit_2->text());
    prefs->setValue(name + "/proportionalPIDfactor", ui->proportionalPidFactorEdit_2->text());
    prefs->setValue(name + "/sshFileName", ui->sshFileNameEdit_2->text());
    prefs->setValue(name + "/speedMinimum", ui->speedMinimumEdit_2->text());
    prefs->setValue(name + "/runDirectory", ui->runDirectoryEdit_2->text());
    prefs->setValue(name + "/remoteBinDirFromLocal", ui->remoteBinDirFromLocalBox->isChecked() ? "true" : "false");
    prefs->setValue(name + "/summonTimeoutThreshold", ui->summonTimeoutThresholdEdit_2->text());
    prefs->setValue(name + "/speedMaximum", ui->speedMaximumEdit->text());
    prefs->setValue(name + "/summonPortDefault", ui->summonPortDefaultEdit_2->text());
    prefs->setValue(name + "/recurse", ui->recurseBox->isChecked() ? "true" : "false");
    prefs->setValue(name + "/synInterval", ui->synIntervalEdit_2->text());
    prefs->setValue(name + "/targetErrorBasisPoints", ui->targetErrorBasisPointsEdit_2->text());
    prefs->setValue(name + "/tempDirectory", ui->tempDirectoryEdit_2->text());
    prefs->setValue(name + "/timeoutThreshold", ui->timeoutThresholdEdit_2->text());
    prefs->setValue(name + "/uploadSpeedMaximum", ui->uploadSpeedMaximumEdit->text());
    prefs->setValue(name + "/verbose", ui->verboseBox->isChecked() ? "true" : "false");

    prefs->sync();
}
