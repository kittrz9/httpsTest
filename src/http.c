// a lot of this socket stuff is based off of this guide: https://beej.us/guide/bgnet/html//index.html

#include "http.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "connection.h"

#define MAX_REQUEST_LEN 4096
#define MAX_RESPONSE_LEN 4096
char* httpRequest(connection c, char* method, char* path, char* headers) {
	char* response = malloc(sizeof(char) * MAX_RESPONSE_LEN);
	char request[MAX_REQUEST_LEN];
	sprintf(request, "%s %s HTTP/1.1\r\nHost: %s\r\n%s\r\n", method, path, c.addr->ai_canonname, headers);
	printf("\nrequest: %s\n\n", request);
	if(send(c.socket, request, strlen(request), 0) < 0) {
		fprintf(stderr, "could not send request\n");
		return NULL;
	}

	if(recv(c.socket, response, MAX_REQUEST_LEN, 0) < 0) {
		fprintf(stderr, "failed to recieve response\n");
		return NULL;
	}

	return response;
}
