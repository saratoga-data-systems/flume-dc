#-------------------------------------------------
# Copyright (C) 2015-2016 by Saratoga Data Systems, Inc.
# All Rights Reserved.
#
# Author: Matthew Voss
#-------------------------------------------------

#-------------------------------------------------
#
# Project created by QtCreator 2015-12-15T15:56:32
#
#-------------------------------------------------

CONFIG	 += static console
QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = "flume-dc"
TEMPLATE = app
win32: RC_ICONS += favicon.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    progressdialog.cpp \
    configdialog.cpp \
    serverdialog.cpp \
    flumesettings.cpp \
    aboutdialog.cpp \
    verifyprogress.cpp

HEADERS  += mainwindow.h \
    progressdialog.h \
    configdialog.h \
    serverdialog.h \
    flumesettings.h \
    aboutdialog.h \
    verifyprogress.h

FORMS    += mainwindow.ui \
    progressdialog.ui \
    configdialog.ui \
    serverdialog.ui \
    flumesettings.ui \
    aboutdialog.ui \
    verifyprogress.ui
