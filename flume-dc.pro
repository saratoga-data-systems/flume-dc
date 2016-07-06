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
LIBPATH += "C:\qt-everywhere-opensource-src-5.6.0\qtbase\lib"
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
    sshconfig.ui \
    sshprogress.ui \
    verifyprogress.ui

RESOURCES += \
    winicon.qrc
