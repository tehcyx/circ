#ifndef _CLIENT_H_
#define _CLIENT_H_

#include <stdbool.h>
#include <linkedlist.h>
#include <pthread.h>

typedef struct client_struct {
	char* nick;
	pthread_t client_thread; //Each user has its own thread
	int client_sock;
	pthread_mutex_t client_sock_mutex;
} client;

list* client_list; //List of all clients.

char* client_util_read_args(char* cmd, char* args);

void client_connect(client_info* new_client);

char* client_read_socket(int socket, char* buffer, bool* err);
char* client_read_connect_cmd(char* cmd, char* args);
char* client_read_connect_pass(char* cmd, char* args, bool* pass);
char* client_read_recipient(char* cmd, char* args);

//bool client_nick_change(char* new_nick, char* old_nick, int client_sock, pthread_t client_thread);
void client_set_prompt(client* cli, char* prompt);
bool client_nick_exists(char* nick);

void client_list_init(); //create empty list of users
void client_init(char* nick, int client_sock, pthread_t client_thread); //Creates a new user object, adds it to the list all_users and adds him to the lobby

void client_free(client* u); //Free data associated with a user u
void client_remove(client* u); //removes user from all_users list, current chat room, then frees user

#endif
