#include <logger.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void logger(const char* tag, const char* message, const char* logfile) {
	FILE* fp;

	if (logfile == NULL) {
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