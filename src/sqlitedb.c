#include <sqlitedb.h>
#include <stdio.h>
#include <sqlite3.h>


void init_db() {
	char *err_msg = 0;
	int rc = sqlite3_open("circ.db", &db);

	if (rc != SQLITE_OK) {

		fprintf(stderr, "Cannot open database: %s\n", sqlite3_errmsg(db));
		sqlite3_close(db);
	}

	char *sql = "DROP TABLE IF EXISTS circ_channels;" 
		"CREATE TABLE circ_channels(Id INTEGER PRIMARY KEY AUTOINCREMENT, Name VARCHAR(200), Mode VARCHAR(22), Motd VARCHAR(80), Owner INTEGER);";

	rc = sqlite3_exec(db, sql, 0, 0, &err_msg);

	if (rc != SQLITE_OK ) {

		fprintf(stderr, "SQL error: %s\n", err_msg);

		sqlite3_free(err_msg);        
		sqlite3_close(db);
	}

	printf("%s\n", "Table `circ_channels` created");

	sqlite3_close(db);
}



void teardown_db() {
	printf("Teardown %s\n", "");
}