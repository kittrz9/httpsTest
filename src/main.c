#include <stdio.h>
#include <stdlib.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include "https.h"

#include "ssl.h"

int main(int argc, char** argv) {
	SSL_library_init();

	SSL_CTX* ctx;
	SSL* ssl;

	// maybe using pointers to pointers to assign the pointer is dumb
	initSSL(&ctx, &ssl);

	connection c = connectToServer("crouton.net", 443);

	SSL_set_fd(ssl, c.socket);
	if(SSL_connect(ssl) == -1) {
		ERR_print_errors_fp(stderr);
		disconnect(c);
		return 1;
	}

	showCerts(ssl);

	char* response = httpsRequest(ssl, c, "GET", "/", "Content-Type: text/plaintext\r\n");
	if(response == NULL) { return 1; }
	printf("%s\n", response);

	free(response);

	disconnect(c);

	return 0;
}
