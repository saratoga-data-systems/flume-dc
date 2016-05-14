#include "verifyconfig.h"


extern LIBSSH2_SESSION *session;
extern LIBSSH2_CHANNEL *channel;
extern int sock;
extern QSettings *prefs;

VerifyConfig::VerifyConfig(QObject *parent) : QObject(parent)
{
}
