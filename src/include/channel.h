#ifndef _CHANNEL_H_
#define _CHANNEL_H_

#include <linkedlist.h>
#include <pthread.h>

struct channel_struct {
	list* channel_client_list; //linked list of users in this channel
	char* channel_name; //Name of room
	char* channel_motd; //Unused currently. History of msg previously sent to user
	pthread_mutex_t channel_mutex; //To avoid 2 threads editing user's channel list simultaneously

};

typedef struct channel_struct channel; 

#endif
