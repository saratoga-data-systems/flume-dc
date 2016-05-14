#include <QtCore/QFileSystemWatcher>
#include <QtCore/QString>
#include "libssh2.h"

void connectSSH(QString hostname);
void sendDirSSH(QString dir);
void disconnectSSH();
