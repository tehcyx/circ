#ifndef _SQLITEDB_H_
#define _SQLITEDB_H_

#include <sqlite3.h>

sqlite3 *db;
sqlite3_stmt *res;

void init_db();

#endif