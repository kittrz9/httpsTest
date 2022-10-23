// https://aticleworld.com/ssl-server-client-using-openssl-in-c/

#include "ssl.h"

#include <openssl/err.h>

void initSSL(SSL_CTX** ctx, SSL** ssl) {
	SSL_METHOD* method;
	OpenSSL_add_all_algorithms();
	SSL_load_error_strings();
	method = TLS_client_method();
	*ctx = SSL_CTX_new(method);
	if(*ctx == NULL) {
		ERR_print_errors_fp(stderr);
		abort();
	}

	*ssl = SSL_new(*ctx);


	return;
}

void showCerts(SSL* ssl) {
	X509* cert;
	char* line;

	cert = SSL_get_peer_certificate(ssl);
	if(cert != NULL) {
		printf("\nserver certificates:\n");
		line = X509_NAME_oneline(X509_get_subject_name(cert), 0, 0);
		printf("subject: %s\n", line);
		free(line);
		line = X509_NAME_oneline(X509_get_issuer_name(cert), 0, 0);
		printf("issuer: %s\n", line);
		free(line);
		X509_free(cert);
	} else {
		printf("no client certificates configured\n");
	}
	printf("\n");
}
