#include <channel.h>
#include <commands.h>
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

const uint16_t MAX_PROMPT_SIZE = 100;
const uint16_t MSG_BUFFER_SIZE = 512;

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
    channel* chan = (channel*)malloc(sizeof(channel));
    chan->client_list = list_create((void(*)(void*))client_free);
    chan->name = chan_name;
    chan->motd = NULL;
    pthread_mutex_init(&(chan->channel_mutex), NULL);

    return chan;
}

void channel_destroy(list* chan_list, channel* chan) {

}

void channel_set_motd(channel* chan, char* motd) {

}

void channel_client_join(channel* chan, client* cli) {
    char prompt[MAX_PROMPT_SIZE]; 
	char msg_buffer[MSG_BUFFER_SIZE]; 

    sprintf(prompt, "%s @ %s>", cli->nick, LOBBY_NAME); 
    log_debug("Sending prompt to: %s @ %s>", cli->nick, LOBBY_NAME);
    client_set_prompt(cli, prompt);

    list_add(chan->client_list, create_node(cli));
    //TODO: we could set current room of the user here

    channel_print_raw_to_user(cli, (char*)JOIN_SUCCESS_CMD); 
	sprintf(msg_buffer, "+PRINT [Server]: Connected as user '%s'.\n[Server]: Now entering lobby.\n \n", cli->nick);
	channel_print_raw_to_user(cli, msg_buffer);
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

void channel_print_to_user(client* cli, char* msg) {
    char buffer[MSG_BUFFER_SIZE]; 
	sprintf(buffer, "%s %s", PRINT_CMD, msg); 
	int err = -1;

	pthread_mutex_lock(&(cli->client_sock_mutex)); 
	err = send(cli->client_sock, buffer, strlen(buffer) + 1, 0); 
	pthread_mutex_unlock(&(cli->client_sock_mutex)); 

	if (err < 0) {
		log_debug("Error in 'channel_print_to_user' function.\nError: %s\n", strerror(errno));
    } else if (err == 0) {
		log_debug("Error in 'channel_print_to_user': 0 bytes written.\nError: %s\n", strerror(errno));
	}
	
}

void channel_print_raw_to_user(client* cli, char* msg) {
	if (msg == NULL || strlen(msg) <=0) {
		log_debug("Error: NULL or 0-length message in channel_print_raw_to_user()\n");
		return;
	}

	int err = -1;

	pthread_mutex_lock(&(cli->client_sock_mutex)); // atomic
	err = send(cli->client_sock, msg, strlen(msg) + 1, 0);
	pthread_mutex_unlock(&(cli->client_sock_mutex));

	if (err < 0) {
		log_debug("Error sending in 'channel_print_raw_to_user' function.\nError: %s\n", strerror(errno));
    } else if (err == 0) {
		log_debug("Error sending in 'channel_print_raw_to_user': 0 bytes written.\nError: %s\n", strerror(errno));
    }
}

void channel_free(channel* chan) {
    log_debug("Cleaning out channel '%s'", chan->name);
    pthread_mutex_destroy(&(chan->channel_mutex));
    free(chan->name);
    free(chan->motd);
    free(chan);
}
