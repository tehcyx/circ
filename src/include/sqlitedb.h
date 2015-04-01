#ifndef _SQLITEDB
#define _SQLITEDB

#include <sqlite3.h>

sqlite3 *db;
sqlite3_stmt *res;


void init_db();

void teardown_db();

#endif