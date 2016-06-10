#-------------------------------------------------
#
# Project created by QtCreator 2015-12-15T15:56:32
#
#-------------------------------------------------

CONFIG	 += static console
QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = flume_dc
TEMPLATE = app
INCLUDEPATH += "C:\Users\ormris\Documents\libssh2\include"
LIBPATH += "C:\Users\ormris\Documents\libssh2\src\Debug"
LIBPATH += "C:\Users\ormris\Documents\openssl\OpenSSL_1_0_1h-install-msvc1800-64-\lib"
LIBPATH += "C:\Users\ormris\Documents\qt-everywhere-opensource-src-5.6.0\qtbase\lib"
LIBS += ws2_32.lib libeay32.lib ssleay32.lib libssh2.lib Crypt32.lib
win32: RC_ICONS += favicon.ico

SOURCES += main.cpp\
        mainwindow.cpp \
    progressdialog.cpp \
    configdialog.cpp \
    serverdialog.cpp \
    flumesettings.cpp \
    aboutdialog.cpp \
    configtransfer.cpp \
    filetransfer.cpp \
    sshconnect.cpp \
    sshconfig.cpp \
    sshprogress.cpp \
    sendkey.cpp \
    verifyprogress.cpp

HEADERS  += mainwindow.h \
    progressdialog.h \
    configdialog.h \
    serverdialog.h \
    flumesettings.h \
    aboutdialog.h \
    configtransfer.h \
    filetransfer.h \
    sshconnect.h \
    sshconfig.h \
    sshprogress.h \
    sendkey.h \
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
