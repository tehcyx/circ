#include <channel.h>
#include <logger.h>

/*
 * Channels names are strings (beginning with a '&' or '#' character) of
 * length up to 200 characters.  Apart from the the requirement that the
 * first character being either '&' or '#'; the only restriction on a
 * channel name is that it may not contain any spaces (' '), a control G
 * (^G or ASCII 7), or a comma (',' which is used as a list item
 * separator by the protocol).
 */

static const char* LOBBY_NAME = "LOBBY"; //Name of lobby room
static list* channel_list = NULL; //List of all chat rooms. Static for C-style data encapsulation
static channel* LOBBY = NULL; //LOBBY

void channel_init() {

    if (channel_list == NULL) {
        channel_list = list_create((void(*)(void*))channel_free);
    }

    if (LOBBY == NULL) {
        LOBBY = channel_create(channel_list, (char*)LOBBY_NAME);
        list_add(channel_list, (void*)LOBBY);
    }
}


channel* channel_create(list* chan_list, char* chan_name) {
    channel* new_channel = (channel*)malloc(sizeof(channel));
    new_channel->client_list = list_create((void(*)(void*))client_free);
    new_channel->name = chan_name;
    new_channel->motd = NULL;
    pthread_mutex_init(&(new_channel->channel_mutex), NULL);

    return new_channel;
}

void channel_destroy(list* chan_list, channel* chan) {

}

void channel_set_motd(channel* chan, char* motd) {

}

void channel_client_join(channel* chan, client* cli) {
    list_add(chan->client_list, create_node(cli));
}

void channel_client_part(channel* chan, client* cli) {
    list_remove(chan->client_list, cli);
}

bool channel_exists(list* chan_list, channel* chan) {

    return NULL;
}

bool channel_name_exists(char* chan_name) {
	channel* tmp_chan;
	bool exists = false;
	node* iter = channel_list->head;

	while (iter != NULL) {
		tmp_chan = (channel*)iter->data;
		if (strcasecmp(tmp_chan->name, chan_name)==0) {
			exists = true;
			break;
		}
		iter=iter->next;
	}
	return exists;
}

void channel_free(channel* chan) {
    // log_debug("Cleaning out channel '%s'", chan->name);
    pthread_mutex_destroy(&(chan->channel_mutex));
    free(chan->name);
    free(chan->motd);
    free(chan);
}
