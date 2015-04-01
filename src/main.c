#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sqlite3.h>

#include <sqlitedb.h>

/* Define port to use */
#ifndef CIRC_PORT
#define CIRC_PORT 6665
#endif

/**
 * Possible IRC commands include:
 *
 * KICK, MODE, INVITE, TOPIC, NAMES, WHO, WHOIS
 *
 */


int main(int argc, char **argv) {

	init_db();

	// logic
	// for(;;) {
	// 	// do stuff
	// }

	teardown_db();

	return 0;             /* ANSI C requires main to return int. */
}