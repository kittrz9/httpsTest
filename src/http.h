// I forgot https was a thing and discord doesn't accept just plain http requests so this part is just kinda here, I don't really want to get rid of it since it might be useful in other projects
#ifndef HTTP_H
#define HTTP_H

#include "connection.h"

char* httpRequest(connection c, char* method, char* path, char* headers);

#endif
