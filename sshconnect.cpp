#include "sshconnect.h"
extern QSettings *prefs;
extern LIBSSH2_SESSION *session;
extern int sock;

SshConnect::SshConnect(QObject *parent, QString server, QString port) : QObject(parent)
{
    serverName = server;
    portNumber = port;
}

void
SshConnect::begin()
{
    emit started();
    qDebug() << "Connecting to " << serverName << ":" << portNumber;
    emit beat();

    qDebug() << "Starting SSH session with" << serverName;
    const char *hostname = strdup(serverName.toStdString().c_str());
    const char *port = strdup(portNumber.toStdString().c_str());

    WSADATA wsa;

    if (WSAStartup(MAKEWORD(2,2), &wsa) != 0) {
        QString msg = "Failed to initialize socket library. Error Code: ";
        msg += QString::number(WSAGetLastError());
        qDebug() << msg;
        emit error(msg);
        goto DONE;
    }

    struct addrinfo *result = NULL;
    struct addrinfo *ap = NULL;
    struct addrinfo hints;

    struct sockaddr_in *sockaddr_ipv4 = NULL;
    struct sockaddr_in6 *sockaddr_ipv6 = NULL;

    memset(&hints, 0, sizeof(hints));
    hints.ai_family = AF_UNSPEC;
    hints.ai_socktype = SOCK_STREAM;
    hints.ai_protocol = IPPROTO_TCP;

    if (getaddrinfo(hostname, port, &hints, &result) != 0) {
        qDebug() << "getaddrinfo failed with error";
        emit error("getaddrinfo failed with error");
        goto DONE;
    }

    for (ap = result; ap != NULL; ap = ap->ai_next) {
        switch (ap->ai_family) {
        case AF_INET:
            sockaddr_ipv4 = (struct sockaddr_in *) ap->ai_addr;
            qDebug() << "IPV4 Address:"  << inet_ntoa(sockaddr_ipv4->sin_addr);
            goto NEXT;
        case AF_INET6:
            sockaddr_ipv6 = (struct sockaddr_in6 *) ap->ai_addr;
            qDebug() << "IPV6 Address";
            goto NEXT;
        default:
            break;
        }
    }

    emit beat();

NEXT:

    qDebug() << "Connecting to " << hostname << ":" << port;

    if (sockaddr_ipv4 != NULL) {
        if ((sock = socket(AF_INET, SOCK_STREAM, 0)) == INVALID_SOCKET) {
            qDebug() << "Couldn't create socket: " << WSAGetLastError();
            emit error("Couldn't create socket");
            goto DONE;
        }

        if (::connect(sock, (struct sockaddr *) sockaddr_ipv4, sizeof(*sockaddr_ipv4)) != 0) {
            qDebug() << "Failed to connect to host: " << WSAGetLastError();
            emit error("Failed to connect to host");
            goto DONE;
        }
    } else if (sockaddr_ipv6 != NULL) {
        if ((sock = socket(AF_INET6, SOCK_STREAM, 0)) == INVALID_SOCKET) {
            qDebug() << "Couldn't create socket: " << WSAGetLastError();
            emit error("Couldn't create socket");
            goto DONE;
        }

        if (::connect(sock, (struct sockaddr *) sockaddr_ipv6, sizeof(*sockaddr_ipv6)) != 0) {
            qDebug() << "Failed to connect to host";
            emit error("Failed to connect to host");
            goto DONE;
        }
    } else {
        qDebug() << "Couldn't find host by that name";
        emit error("Couldn't find host by that name");
        goto DONE;
    }

    emit beat();

    libssh2_init(0);

    if ((session = libssh2_session_init()) == NULL) {
        qDebug() << "Couldn't allocate session";
        emit error("Couldn't allocate session");
        goto DONE;
    }

    if (libssh2_session_handshake(session, sock) != 0) {
        qDebug() << "SSH session handshake failed";
        emit error("SSH session handshake failed");
        goto DONE;
    }

    emit beat();

    const char *username = strdup(prefs->value("proxyUsername", "flumer").toString().toStdString().c_str());
    const char *password = strdup(prefs->value("proxyPassword", "flumer").toString().toStdString().c_str());

    qDebug() << "Logging in";
    qDebug() << "Username: " << username;

    if (libssh2_userauth_password(session, username, password) != 0) {
        qDebug() << "Authentication failed";
        emit error("Authentication failed");
        goto DONE;
    }

    emit beat();

    qDebug() << "Authentication complete";
DONE:
    emit beat();
    emit finished();
}
