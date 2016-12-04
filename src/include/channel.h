#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include "sys/socket.h"
#include "sys/types.h"
#include "netdb.h"
#include "errno.h"
#include <pthread.h>
#include <server.h>
#include <linkedlist.h>
#include <client.h>

typedef struct channel_struct {
	list* client_list; //linked list of users in this channel
	char* name; //Name of room
	char* motd; //Unused currently. History of msg previously sent to user
	pthread_mutex_t channel_mutex; //To avoid 2 threads editing user's channel list simultaneously
} channel;

static channel* LOBBY; //LOBBY

void channel_init();
channel* channel_create(list* chan_list, char* chan_name);
void channel_destroy(list* chan_list, channel* chan);
void channel_set_motd(channel* chan, char* motd);

void channel_client_join(channel* chan, client* cli);
void channel_client_part(channel* chan, client* cli);

void channel_listen_events(channel* chan, client* cli);
void channel_stop_events(channel* chan, client* cli);

bool channel_exists(list* chan_list, channel* chan);
bool channel_name_exists(char* chan_name);
void channel_free(channel* chan);

#endif
