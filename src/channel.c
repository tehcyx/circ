#include <channel.h>

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
static channel* LOBBY = NULL; //LOBBY chat_room object