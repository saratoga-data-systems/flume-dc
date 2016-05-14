#include "flumesettings.h"
#include "ui_flumesettings.h"

extern QSettings *prefs;

FlumeSettings::FlumeSettings(QWidget *parent, QString name) :
    QWidget(parent),
    ui(new Ui::FlumeSettings)
{
    ui->setupUi(this);

    serverName = name;

    ui->targetNameEdit->setText(name);
    ui->targetHostnameEdit->setText(prefs->value(name + "/targetHostname", "localhost").toString());
    ui->targetUsernameEdit->setText(prefs->value(name + "/targetUsername", "flumer").toString());
    ui->targetPasswordEdit->setText(prefs->value(name + "/targetPassword", "flumer").toString());
    ui->targetDirectoryEdit->setText(prefs->value(name + "/targetDirectory", "/tmp").toString());
    ui->targetPortEdit->setText(prefs->value(name + "/targetPort", "22").toString());
    ui->summonMethodEdit->setText(prefs->value(name + "/summonMethod", "ssh").toString());
    ui->DFEdit_2->setText(prefs->value(name + "/DF", "false").toString());
    ui->MTUEdit_2->setText(prefs->value(name + "/MTU", "1500").toString());
    ui->allowFileNameEdit_2->setText(prefs->value(name + "/allowFileName","/etc/flume/allow").toString());
    ui->checksumSpecEdit_2->setText(prefs->value(name + "/checksumSpec", "Fletcher32").toString());
    ui->compressionLevelEdit->setText(prefs->value(name + "/compressionLevel", "0").toString());
    ui->compressionStrategyEdit_2->setText(prefs->value(name + "/compressionStrategy", "default").toString());
    ui->debugEdit->setText(prefs->value(name + "/debug", "0").toString());
    ui->derivativePidFactorEdit_2->setText(prefs->value(name + "/derivativePIDfactor", "0.050000").toString());
    ui->flexlmLicenseDirectoryEdit_2->setText(prefs->value(name + "/flexlmLicenseDirectory", "/etc/flume/license").toString());
    ui->hashSpecEdit_2->setText(prefs->value(name + "/hashSpec", "MD4").toString());
    ui->initSpeedFactorEdit_2->setText(prefs->value(name + "/initSpeedFactor", "100").toString());
    ui->integralPidFactorEdit_2->setText(prefs->value(name + "/integralPIDfactor", "0.000000").toString());
    ui->localInterfaceIpEdit_2->setText(prefs->value(name + "/localInterfaceIp", "0.0.0.0").toString());
    ui->logDirectoryEdit_2->setText(prefs->value(name + "/logDirectory","/var/log/flume").toString());
    ui->measureIPDEdit_2->setText(prefs->value(name + "/measureIPD","false").toString());
    ui->numericIdsEdit_2->setText(prefs->value(name + "/numericIds", "false").toString());
    ui->pagePortDefaultEdit_2->setText(prefs->value(name + "/pagePortDefault", "2317").toString());
    ui->performFsyncsEdit_2->setText(prefs->value(name + "/performFsyncs", "false").toString());
    ui->portsFileNameEdit_2->setText(prefs->value(name + "/portsFileName", "/etc/flume/ports").toString());
    ui->proportionalPidFactorEdit_2->setText(prefs->value(name + "/proportionalPIDfactor", "0.500000").toString());
    ui->sshFileNameEdit_2->setText(prefs->value(name + "/sshFileName", "ssh").toString());
    ui->speedMinimumEdit_2->setText(prefs->value(name + "/speedMinimum", "0.000000").toString());
    ui->runDirectoryEdit_2->setText(prefs->value(name + "/runDirectory", "/var/run/flume").toString());
    ui->remoteBinDirFromLocalEdit_2->setText(prefs->value(name + "/remoteBinDirFromLocal","false").toString());
    ui->summonTimeoutThresholdEdit_2->setText(prefs->value(name + "/summonTimeoutThreshold", "0.000000").toString());
    ui->speedMaximumEdit->setText(prefs->value(name + "/speedMaximum", "60.00000").toString());
    ui->summonPortDefaultEdit_2->setText(prefs->value(name + "/summonPortDefault", "22").toString());
    ui->recurseEdit->setText(prefs->value(name + "/recurse","false").toString());
    ui->synIntervalEdit_2->setText(prefs->value(name + "/synInterval", "100").toString());
    ui->targetErrorBasisPointsEdit_2->setText(prefs->value(name + "/targetErrorBasisPoints", "200").toString());
    ui->tempDirectoryEdit_2->setText(prefs->value(name + "/tempDirectory","/tmp").toString());
    ui->timeoutThresholdEdit_2->setText(prefs->value(name + "/timeoutThreshold","1").toString());
    ui->uploadSpeedMaximumEdit->setText(prefs->value(name + "/uploadSpeedMaximum","10000.00").toString());
    ui->verboseEdit->setText(prefs->value(name + "/verbose","false").toString());
    ui->wholeFileEdit_2->setText(prefs->value(name + "/wholeFile", "true").toString());

    connect(ui->pushButton_3, &QPushButton::clicked, this, &FlumeSettings::emitRemove);
    connect(ui->pushButton_4, &QPushButton::clicked, this, &FlumeSettings::reset);
    connect(ui->verifyButton, &QPushButton::clicked, this, &FlumeSettings::verifyServer);

    setWindowTitle("Edit Target List");
}

FlumeSettings::~FlumeSettings()
{
    delete ui;
}

void
FlumeSettings::reset()
{
    ui->targetHostnameEdit->setText("localhost");
    ui->targetUsernameEdit->setText("flumer");
    ui->targetPasswordEdit->setText("flumer");
    ui->targetDirectoryEdit->setText("/tmp");
    ui->targetPortEdit->setText("22");
    ui->summonMethodEdit->setText("ssh");
    ui->DFEdit_2->setText("false");
    ui->MTUEdit_2->setText("1500");
    ui->allowFileNameEdit_2->setText("/etc/flume/allow");
    ui->checksumSpecEdit_2->setText("Fletcher32");
    ui->compressionLevelEdit->setText("0");
    ui->compressionStrategyEdit_2->setText("default");
    ui->debugEdit->setText("0");
    ui->derivativePidFactorEdit_2->setText("0.050000");
    ui->flexlmLicenseDirectoryEdit_2->setText("/etc/flume/license");
    ui->hashSpecEdit_2->setText("MD4");
    ui->initSpeedFactorEdit_2->setText("100");
    ui->integralPidFactorEdit_2->setText("0.000000");
    ui->localInterfaceIpEdit_2->setText("0.0.0.0");
    ui->logDirectoryEdit_2->setText("/var/log/flume");
    ui->measureIPDEdit_2->setText("false");
    ui->numericIdsEdit_2->setText("false");
    ui->pagePortDefaultEdit_2->setText("2317");
    ui->performFsyncsEdit_2->setText("false");
    ui->portsFileNameEdit_2->setText("/etc/flume/ports");
    ui->proportionalPidFactorEdit_2->setText("0.500000");
    ui->sshFileNameEdit_2->setText("ssh");
    ui->speedMinimumEdit_2->setText("0.000000");
    ui->runDirectoryEdit_2->setText("/var/run/flume");
    ui->remoteBinDirFromLocalEdit_2->setText("false");
    ui->summonTimeoutThresholdEdit_2->setText("0.000000");
    ui->speedMaximumEdit->setText("60.00000");
    ui->summonPortDefaultEdit_2->setText("22");
    ui->recurseEdit->setText("false");
    ui->synIntervalEdit_2->setText("100");
    ui->targetErrorBasisPointsEdit_2->setText("200");
    ui->tempDirectoryEdit_2->setText("/tmp");
    ui->timeoutThresholdEdit_2->setText("1");
    ui->uploadSpeedMaximumEdit->setText("10000.00");
    ui->verboseEdit->setText("false");
    ui->wholeFileEdit_2->setText("true");
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
    prefs->setValue(name + "/targetPassword", ui->targetPasswordEdit->text());
    prefs->setValue(name + "/targetDirectory", ui->targetDirectoryEdit->text());
    prefs->setValue(name + "/summonMethod", ui->summonMethodEdit->text());
    prefs->setValue(name + "/DF", ui->DFEdit_2->text());
    prefs->setValue(name + "/MTU", ui->MTUEdit_2->text());
    prefs->setValue(name + "/allowFileName", ui->allowFileNameEdit_2->text());
    prefs->setValue(name + "/checksumSpec", ui->checksumSpecEdit_2->text());
    prefs->setValue(name + "/compressionLevel", ui->compressionLevelEdit->text());
    prefs->setValue(name + "/compressionStrategy", ui->compressionStrategyEdit_2->text());
    prefs->setValue(name + "/debug", ui->debugEdit->text());
    prefs->setValue(name + "/derivativePIDfactor", ui->derivativePidFactorEdit_2->text());
    prefs->setValue(name + "/flexlmLicenseDirectory", ui->flexlmLicenseDirectoryEdit_2->text());
    prefs->setValue(name + "/hashSpec", ui->hashSpecEdit_2->text());
    prefs->setValue(name + "/initSpeedFactor", ui->initSpeedFactorEdit_2->text());
    prefs->setValue(name + "/integralPIDfactor", ui->integralPidFactorEdit_2->text());
    prefs->setValue(name + "/localInterfaceIp", ui->localInterfaceIpEdit_2->text());
    prefs->setValue(name + "/logDirectory", ui->logDirectoryEdit_2->text());
    prefs->setValue(name + "/measureIPD", ui->measureIPDEdit_2->text());
    prefs->setValue(name + "/numericIds", ui->numericIdsEdit_2->text());
    prefs->setValue(name + "/pagePortDefault", ui->pagePortDefaultEdit_2->text());
    prefs->setValue(name + "/performFsyncs", ui->performFsyncsEdit_2->text());
    prefs->setValue(name + "/portsFileName", ui->portsFileNameEdit_2->text());
    prefs->setValue(name + "/proportionalPIDfactor", ui->proportionalPidFactorEdit_2->text());
    prefs->setValue(name + "/sshFileName", ui->sshFileNameEdit_2->text());
    prefs->setValue(name + "/speedMinimum", ui->speedMinimumEdit_2->text());
    prefs->setValue(name + "/runDirectory", ui->runDirectoryEdit_2->text());
    prefs->setValue(name + "/remoteBinDirFromLocal", ui->remoteBinDirFromLocalEdit_2->text());
    prefs->setValue(name + "/summonTimeoutThreshold", ui->summonTimeoutThresholdEdit_2->text());
    prefs->setValue(name + "/speedMaximum", ui->speedMaximumEdit->text());
    prefs->setValue(name + "/summonPortDefault", ui->summonPortDefaultEdit_2->text());
    prefs->setValue(name + "/recurse", ui->recurseEdit->text());
    prefs->setValue(name + "/synInterval", ui->synIntervalEdit_2->text());
    prefs->setValue(name + "/targetErrorBasisPoints", ui->targetErrorBasisPointsEdit_2->text());
    prefs->setValue(name + "/tempDirectory", ui->tempDirectoryEdit_2->text());
    prefs->setValue(name + "/timeoutThreshold", ui->timeoutThresholdEdit_2->text());
    prefs->setValue(name + "/uploadSpeedMaximum", ui->uploadSpeedMaximumEdit->text());
    prefs->setValue(name + "/verbose", ui->verboseEdit->text());
    prefs->setValue(name + "/wholeFile", ui->wholeFileEdit_2->text());

    prefs->sync();
}
