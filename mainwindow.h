/*
 * Copyright (C) 2015-2016 by Saratoga Data Systems, Inc.
 * All Rights Reserved.
 *
 * Author: Matthew Voss
 */
#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QSettings>
#include <QStandardPaths>
#include <QFileDialog>
#include <QStandardItemModel>
#include <QStandardItem>
#include <QtDebug>
#include <QObject>
#include <QMessageBox>
#include <QDateTime>
#include <QItemSelectionModel>
#include <QMimeData>

#include "progressdialog.h"
#include "serverdialog.h"
#include "configdialog.h"
#include "aboutdialog.h"

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    Ui::MainWindow *ui;
    QStandardItemModel *fileModel;
    QItemSelectionModel *selModel;
    void updateTargetList();
    void loadConfigFile(QString file);

protected:
    void dropEvent(QDropEvent* e);
    void dragEnterEvent(QDragEnterEvent* e);
    void dragLeaveEvent(QDragLeaveEvent* e);

public slots:
    void addFile();
    void removeFile();
    void sendAll();
    void pickTarget();
    void editTargetList();
    void editProxyOptions();
    void showAbout();
    void loadConfig();
    void ungrey(const QModelIndex &current, const QModelIndex &previous);
};

#endif // MAINWINDOW_H
