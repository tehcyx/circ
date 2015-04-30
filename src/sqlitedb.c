#include <sqlitedb.h>
#include <stdio.h>
#include <sqlite3.h>
#include <unistd.h>


void init_db() {

	char* db_file = "circ.db";

	if( access( db_file, F_OK ) != -1 ) {
		// file exists, no need to run init
	} else {
		// file doesn't exist
		char* err_msg = 0;
		int rc = sqlite3_open(db_file, &db);

		if (rc != SQLITE_OK) {

			fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
			sqlite3_close(db);
		}

		printf("%s\n", "Setting up necessary tables.");

		char* sql = "DROP TABLE IF EXISTS circ_channels;" 
			"CREATE TABLE circ_channels(Id INTEGER PRIMARY KEY AUTOINCREMENT, Name VARCHAR(200), Mode VARCHAR(22), Motd VARCHAR(80), Owner INTEGER);";

		rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

		if (rc != SQLITE_OK ) {

			fprintf(stderr, "SQL error: %s\n", err_msg);

			sqlite3_free(err_msg);        
			sqlite3_close(db);

			remove(db_file);

			return;
		}

		printf("%s\n", "Table `circ_channels` created");

		sql = "DROP TABLE IF EXISTS circ_users;" 
			"CREATE TABLE circ_users(Id INTEGER PRIMARY KEY AUTOINCREMENT, Name VARCHAR(200), Password VARCHAR(200));";

		if (rc != SQLITE_OK ) {

			fprintf(stderr, "SQL error: %s\n", err_msg);

			sqlite3_free(err_msg);        
			sqlite3_close(db);

			remove(db_file);

			return;
		}

		printf("%s\n", "Table `circ_users` created");

		sqlite3_close(db);
	}
}