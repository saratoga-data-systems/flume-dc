/*
 * Copyright (C) 2015-2016 by Saratoga Data Systems, Inc.
 * All Rights Reserved.
 *
 * Author: Matthew Voss
 */
#include "serverdialog.h"
#include "ui_serverdialog.h"

extern QSettings *prefs;

ServerDialog::ServerDialog(QWidget *parent, int index) :
    QDialog(parent),
    ui(new Ui::ServerDialog)
{
    ui->setupUi(this);

    connect(ui->pushButton_2, &QPushButton::clicked, this, &ServerDialog::addTarget);

    QStringList servers = prefs->childGroups();
    qDebug() << "with tabs: " << servers;

    for (int i = 0; i < servers.size(); i++) {
        if (servers[i] != "General") {
            addTab(servers[i]);
        }
    }

    ui->tabWidget->setCurrentIndex(index);

    setWindowTitle("Edit Destination List");
}

void ServerDialog::verifyConfiguration()
{
    qDebug() << "Verifying";
    QStringList servers = prefs->childGroups();

    qDebug() << servers;

    for (int i = 0; i < servers.size(); i++) {
        if (servers[i] != "General") {
            VerifyProgress *vp = new VerifyProgress(NULL, servers[i]);
            connect(vp, &VerifyProgress::invalid, this, &ServerDialog::invalidate);

            vp->exec();
        }
    }
}

void ServerDialog::invalidate()
{
}

void ServerDialog::addTarget()
{
    bool ok = false;
    QString name;

    do {
        name = QInputDialog::getText(this,
                                     tr("Question"),
                                     tr("Please enter the a name for your destination."),
                                     QLineEdit::Normal, QString(), &ok);
    } while(name == "" && ok);

    if (ok) {
        addTab(name);
    }
}

void ServerDialog::removeTab(int tabIndex, QString name)
{
    qDebug() << "removing tab: " << tabIndex << "and settings group" << name;
    delete ui->tabWidget->widget(tabIndex);
    ui->tabWidget->removeTab(tabIndex);
    prefs->remove(name);
    prefs->sync();
}

void ServerDialog::addTab(QString name)
{
    FlumeSettings *flumeSettings = new FlumeSettings(this, name);
    int index = ui->tabWidget->addTab(flumeSettings, name);
    flumeSettings->tabIndex = index;
    connect(ui->buttonBox, &QDialogButtonBox::accepted, flumeSettings, &FlumeSettings::saveServer);
    connect(flumeSettings, &FlumeSettings::remove, this, &ServerDialog::removeTab);
}

ServerDialog::~ServerDialog()
{
    delete ui;
}
