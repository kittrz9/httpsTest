#ifndef SSL_H
#define SSL_H

#include <openssl/ssl.h>

void initSSL(SSL_CTX** ctx, SSL** ssl);

void showCerts(SSL* ssl);

#endif
