#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <logger.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void logger(const char* tag, const char* message, const char* logfile) {
	FILE* fp;

	if (logfile == NULL) {
		ensurePathExists("logs");

		fp = fopen("logs/log.txt", "a");
	} else {
		fp = fopen(logfile, "a");
	}

	time_t now;
	time(&now);

	char* date = ctime(&now);
	*(date+24) = 0; // cut off the newline for nicer logs
	fprintf(fp, "%s [%s]: %s\n", date, tag, message);

	fclose(fp);
}

void ensurePathExists(const char* path) {
	struct stat st = {0};

	if (stat(path, &st) == -1) {
	    mkdir(path, 0700);
	}
}
