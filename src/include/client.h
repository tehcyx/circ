#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <stdbool.h>

void client_connect();
char* client_read_socket(int socket, char* buffer, bool* err);

#endif