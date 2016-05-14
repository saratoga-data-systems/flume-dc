#include "ssh.h"
#include <QtCore/QtDebug>
#include <QtCore/QString>
#include <QtCore/QSettings>
#include <QtCore/QDirIterator>
#ifdef WIN32
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <iphlpapi.h>
#include <iostream>
#else
#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/select.h>
#include <unistd.h>
#include <arpa/inet.h>
#endif
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <errno.h>
#include <stdio.h>
#include <ctype.h>
#include <string>
#include <cstdlib>
#include <cstdio>
#ifdef WIN32
#include <io.h>
#include <direct.h>
#endif

int sock;
struct sockaddr_in sinc;
LIBSSH2_SESSION *session;
LIBSSH2_CHANNEL *channel;
extern const char* host;
extern QSettings *preferences;

void connectSSH(QString hostname)
{
	qDebug() << hostname << ": ssh connect";

#ifdef WIN32
    WSADATA WsaDat;
    WSAStartup(MAKEWORD(2,2),&WsaDat);
#endif

	libssh2_init(0);

	sock = socket(AF_INET, SOCK_STREAM, 0);

    sinc.sin_family = AF_INET;
    sinc.sin_port = htons(22);
    sinc.sin_addr.s_addr = inet_addr("50.247.74.3");

    connect(sock, (struct sockaddr*)(&sinc), sizeof(struct sockaddr_in));

	session = libssh2_session_init();

	libssh2_session_handshake(session, sock);

	const char* username = "ormris";
	const char* password = "d3h59w7w34";

	libssh2_userauth_password(session, username, password);
}

int sendTarSeg(const char *fpath)
{
	qDebug() << "compressing:" << fpath;
    int fd, len;

	char buff[1000];
	fd = open(fpath, O_RDONLY);
	len = read(fd, buff, sizeof(buff));
	qDebug() << "sending archive";
	while ( len > 0 ) {
		len = read(fd, buff, sizeof(buff));
	}
	close(fd);

	return 0;
}

void sendDirSSH(QString dir)
{

	qDebug() << "sending:" << dir;

	channel = libssh2_channel_open_session(session);

	char buf[1000];
	memset(buf, 0, sizeof(buf));

   #ifdef WIN32
    _snprintf(buf, sizeof(buf), "%s/remoteDest", host);
	const char* directory = strdup(preferences->value(buf, "/tmp").toString().toStdString().c_str());
    _snprintf(buf, sizeof(buf), "%s/localPort", host);
	const char* port = strdup(preferences->value(buf, "22").toString().toStdString().c_str());
    _snprintf(buf, sizeof(buf), "%s/proto", host);
	const char* protocol = strdup(preferences->value(buf, "ssh").toString().toStdString().c_str());
    _snprintf(buf, sizeof(buf), "%s/user", host);
	const char* username = strdup(preferences->value(buf, "nobody").toString().toStdString().c_str());
#else
    snprintf(buf, sizeof(buf), "%s/remoteDest", host);
    const char* directory = strdup(preferences->value(buf, "/tmp").toString().toStdString().c_str());
    snprintf(buf, sizeof(buf), "%s/localPort", host);
    const char* port = strdup(preferences->value(buf, "22").toString().toStdString().c_str());
    snprintf(buf, sizeof(buf), "%s/proto", host);
    const char* protocol = strdup(preferences->value(buf, "ssh").toString().toStdString().c_str());
    snprintf(buf, sizeof(buf), "%s/user", host);
    const char* username = strdup(preferences->value(buf, "nobody").toString().toStdString().c_str());
#endif

	char cmd[2000];
	memset(cmd, 0, sizeof(cmd));

	qDebug() << "directory: " << directory;
	qDebug() << "port: " << port;
	qDebug() << "protocol: " <<protocol;
    _snprintf(cmd, sizeof(cmd), "flume -summon %s:%s --remoteCmd 'tar -C %s -x' - %s@%s:-", protocol, port, directory, username, host);

	int rc = 0;
	qDebug() << "executing command: " << cmd;
	rc = libssh2_channel_exec(channel, cmd);


	QString aname;

	chdir(dir.toStdString().c_str());


	QDirIterator it(".", QDirIterator::Subdirectories);
	for (;it.hasNext(); it.next()) {
		if (it.fileInfo().isDir() || it.filePath() == "") {
			continue;
		}

		sendTarSeg(strdup(it.filePath().toStdString().c_str()));
	}


	int fd;
	fd = open("/tmp/out.tar", O_RDONLY);

	int len;
	qDebug() << "writing to channel";
	while ((len = read(fd, cmd, sizeof(cmd))) > 0) {
		libssh2_channel_write(channel, cmd, len);
		memset(cmd, 0, sizeof(cmd));
	}
	qDebug() << "writing to channel complete";

	libssh2_channel_send_eof(channel);

	do {
		memset(cmd, 0, sizeof(cmd));
		rc = libssh2_channel_read_stderr(channel, cmd, sizeof(cmd));
		qDebug() << "stderr:" << cmd;
		//rc = libssh2_channel_read_ex(channel, 0, cmd, sizeof(cmd));
		//qDebug() << cmd;
	} while (rc > 0);
	qDebug() << "rc:" << rc;

	libssh2_channel_close(channel);
}

void disconnectSSH()
{
	qDebug() << "disconnect";

	libssh2_channel_close(channel);

	libssh2_channel_free(channel);

	libssh2_session_disconnect(session, "Normal Shutdown, Thank you for playing");

	libssh2_session_free(session);

	libssh2_exit();

	close(sock);
}
