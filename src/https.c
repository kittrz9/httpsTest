#include "https.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <openssl/ssl.h>
#include <openssl/err.h>

#include "connection.h"

#include "ssl.h"

// most of this is copied from http.c
#define MAX_REQUEST_LEN 4096
#define MAX_RESPONSE_LEN 4096

char* httpsRequest(SSL* ssl, connection c, char* method, char* path, char* headers) {
	char* response = malloc(sizeof(char) * MAX_RESPONSE_LEN);

	char request[MAX_REQUEST_LEN];
	sprintf(request, "%s %s HTTP/1.1\r\nHost: %s\r\n%s\r\n", method, path, c.addr->ai_canonname, headers);
	printf("\n- REQUEST - \n%s\n\n", request);

	if(SSL_write(ssl, request, strlen(request)) < 1) {
		ERR_print_errors_fp(stderr);
		return NULL;
	}

	int responseLength = SSL_read(ssl, response, sizeof(char) * MAX_RESPONSE_LEN);
	if(responseLength < 1) {
		ERR_print_errors_fp(stderr);
		return NULL;
	}
	response[responseLength] = '\0';

	return response;
}

