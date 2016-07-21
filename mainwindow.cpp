/*
 * Copyright (C) 2015-2016 by Saratoga Data Systems, Inc.
 * All Rights Reserved.
 *
 * Author: Matthew Voss
 */
#include "mainwindow.h"
#include "ui_mainwindow.h"

QSettings *prefs;

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    qDebug() << "Flume DC 0.1";
    qDebug() << "(C) Saratoga Data 2013-2016 All Rights Reserved";

    QString appDataPath = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    prefs = new QSettings(appDataPath + "/flumeGuiConfig.ini", QSettings::IniFormat);

    if (prefs->value("proxyHostname").toString() == "") {
        prefs->setValue("proxyHostname", "127.0.0.1");
    }

    if (prefs->value("proxyUsername").toString() == "") {
        prefs->setValue("proxyUsername", "flumer");
    }

    if (prefs->value("proxyPassword").toString() == "") {
        prefs->setValue("proxyPassword", "flumer");
    }

    if (prefs->value("proxyPort").toString() == "") {
        prefs->setValue("proxyPort", "22");
    }

    fileModel = new QStandardItemModel;
    fileModel->setHorizontalHeaderLabels(QStringList() << "File" << "Status" << "Date");

    ui->setupUi(this);

    updateTargetList();

    ui->pushButton->setEnabled(false);

    ui->listView->setModel(fileModel);
    ui->listView->setEditTriggers(QAbstractItemView::NoEditTriggers);

    ui->listView->setDragEnabled(false);
    selModel = ui->listView->selectionModel();

    connect(ui->pushButton_2, SIGNAL(clicked()), this, SLOT(addFile()));
    connect(ui->actionChoose, SIGNAL(triggered()), this, SLOT(addFile()));
    connect(ui->actionQuit, SIGNAL(triggered()), this, SLOT(close()));
    connect(ui->actionSend, SIGNAL(triggered()), this, SLOT(sendAll()));
    connect(ui->actionAbout, SIGNAL(triggered()), this, SLOT(showAbout()));

    connect(ui->pushButton, SIGNAL(clicked()), this, SLOT(sendAll()));
    connect(ui->actionEdit_Target_List, &QAction::triggered, this, &MainWindow::editTargetList);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::editTargetList);
    connect(ui->removeButton, &QPushButton::clicked, this, &MainWindow::removeFile);
    connect(selModel, &QItemSelectionModel::currentChanged, this, &MainWindow::ungrey);
    connect(ui->actionLoad_Destinations, SIGNAL(triggered(bool)), this, SLOT(loadConfig()));

    setAcceptDrops(true);
}

MainWindow::~MainWindow()
{
    qDebug() << "bye";
    prefs->sync();

    delete ui;
}

void
MainWindow::dragEnterEvent(QDragEnterEvent* e)
{
    e->acceptProposedAction();
}

void
MainWindow::dragLeaveEvent(QDragLeaveEvent* e)
{
    e->accept();
}

void
MainWindow::dropEvent(QDropEvent* e)
{
    e->acceptProposedAction();

    const QMimeData* mime = e->mimeData();

    if (mime->hasUrls()) {
        qDebug() << "Drop event with URLS";
        QList<QUrl> urlList = mime->urls();

        // extract the local paths of the files
        for (int i = 0; i < urlList.size(); i++) {
            QFileInfo qi(urlList[i].toLocalFile());

            if (qi.isFile()) {
                QList<QStandardItem*> row;
                row.append(new QStandardItem(urlList[i].toLocalFile()));
                row.append(new QStandardItem("Ready"));
                fileModel->appendRow(row);
                ui->listView->resizeColumnToContents(0);
            }
        }
    }

}

void
MainWindow::ungrey(const QModelIndex & current, const QModelIndex & previous)
{
    ui->pushButton->setEnabled(true);
}

void
MainWindow::showAbout()
{
    AboutDialog ad;

    ad.exec();
}

void
MainWindow::editProxyOptions()
{
    ConfigDialog cd;

    cd.exec();
}

void
MainWindow::loadConfigFile(QString file)
{
    QSettings loader(file, QSettings::IniFormat);
    qDebug() << "Loading configuration...";
    foreach(const QString &group, loader.childGroups()) {
        loader.beginGroup(group);

        qDebug() << "[" << group << "]";

        foreach(const QString &key, loader.childKeys()) {
            qDebug() << key;
            prefs->setValue(group + "/" + key, loader.value(key, "hello").toString());
        }

        loader.endGroup();
    }
    qDebug() << "Configuration complete.";
}


void
MainWindow::updateTargetList()
{
    QStringList servers = prefs->childGroups();

    ui->comboBox->clear();

    for (int i = 0; i < servers.size(); i++) {
        if (servers[i] != "General") {
            ui->comboBox->addItem(servers[i]);
        }
    }
}

void
MainWindow::loadConfig()
{
    QString documentPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Add File"), documentPath, tr("*.ini"));

    for (int i = 0; i < files.length(); i++) {
        qDebug() << "Loading custom configuration file: " << files.at(i);
        loadConfigFile(files.at(i));
    }
    updateTargetList();
}


void
MainWindow::addFile()
{
    QString documentPath = QStandardPaths::writableLocation(QStandardPaths::DocumentsLocation);
    QStringList files = QFileDialog::getOpenFileNames(this, tr("Add File"), documentPath, tr("*"));

    qDebug() << "Loading files: " << files;
    for (int i = 0; i < files.size(); i++) {
           QList<QStandardItem*> row;
           row.append(new QStandardItem(files[i]));
           row.append(new QStandardItem("Ready"));
           fileModel->appendRow(row);
    }

    ui->listView->resizeColumnToContents(0);
}

void
MainWindow::removeFile()
{
    QModelIndexList indexes = ui->listView->selectionModel()->selectedRows();
    if (indexes.isEmpty()) {
        return;
    }

    QMessageBox ask;

    ask.setWindowTitle("Flume");
    ask.setText("Are you sure you want to remove this file?");
    ask.setStandardButtons(QMessageBox::Yes | QMessageBox::No);
    ask.setDefaultButton(QMessageBox::No);

    if (ask.exec() != QMessageBox::No) {
        while (!indexes.isEmpty())
        {
         fileModel->removeRows(indexes.last().row(), 1);
         indexes.removeLast();
        }
    }

    if (indexes.isEmpty()) {
        ui->pushButton->setEnabled(false);
    }
}

void
MainWindow::sendAll()
{
    if (!QFile::exists("C:\\bin\\flume.exe")) {
        QMessageBox msg;
        msg.setText("Please install Flume, then retry the transfer.");
        msg.setWindowTitle("Flume DC Error");
        msg.exec();
        return;
    }
    QStringList files;

    files.append(fileModel->itemFromIndex(ui->listView->selectionModel()->selectedIndexes()[0])->text());

    if (files.size() < 1) {
        QMessageBox qm;
        qm.setText("Please select the file you wish to transfer.");
        qm.setWindowTitle("Alert");
        qm.exec();

        return;
    }

    if (ui->comboBox->currentText() == "") {
        QMessageBox qm;
        qm.setText("Please add to the destination list.");
        qm.setWindowTitle("Alert");
        qm.exec();

        return;
    }

    qDebug() << "Sending files: " << files;

    ProgressDialog pd(this, ui->comboBox->currentText(), files[0]);

    pd.exec();

    qDebug() << "Transfer attempt complete.";

    QDateTime dt(QDateTime::currentDateTime().toUTC());
    fileModel->setData(ui->listView->selectionModel()->selectedIndexes()[2], QVariant(dt.toString("yyyy-MM-dd hh:mm Z")));
    if (pd.returnValue() >= 200) {
        fileModel->setData(ui->listView->selectionModel()->selectedIndexes()[1], QVariant("FAILED"));
    } else {
        fileModel->setData(ui->listView->selectionModel()->selectedIndexes()[1], QVariant("SUCCEEDED"));
    }

    ui->listView->resizeColumnToContents(1);
}

void
MainWindow::editTargetList()
{
    qDebug() << "Config Dialog Launched";

    ServerDialog sd(NULL, ui->comboBox->currentIndex());

    sd.exec();

    updateTargetList();
}

void
MainWindow::pickTarget()
{
}
