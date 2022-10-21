#ifndef HTTPS_H
#define HTTPS_H

#include <openssl/ssl.h>

#include "connection.h"

char* httpsRequest(SSL* ssl, connection c, char* method, char* path, char* headers);

#endif
