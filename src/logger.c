#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>
#include <logger.h>
#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include <stdarg.h>

const char* LOG_FILE = NULL;
uint8_t LOG_LEVEL = LOG_DEBUG;

void log_format(const char* tag, const char* message, va_list args) {
	// if (LOG_LEVEL)
	time_t now;
	time(&now);

	char* date = ctime(&now);
	*(date+24) = 0; // cut off the newline for nicer logs

	char log_entry[512];
	sprintf(log_entry, "%s [%s]",  date, tag);

	char msg[512];
	vsprintf(msg, message, args);
	va_end(args);

	FILE* fp;
	fp = fopen(LOG_FILE, "a");

	fprintf(fp, "%s: %s\n", log_entry, msg);

	fclose(fp);
}

void log_info(const char* message, ...) {
	va_list args;
	va_start(args, message);
	log_format("info", message, args);
	va_end(args);
}

void log_error(const char* message, ...) {
	va_list args;
	va_start(args, message);
	log_format("error", message, args);
	va_end(args);
}

void log_warn(const char* message, ...) {
	va_list args;
	va_start(args, message);
	log_format("warn", message, args);
	va_end(args);
}

void log_debug(const char* message, ...) {
	va_list args;
	va_start(args, message);
	log_format("debug", message, args);
	va_end(args);
}

void log_init(const char* file, const uint8_t level) {
	if (level == LOG_DEBUG || level == LOG_WARN || level == LOG_ERROR || level == LOG_INFO) {
		LOG_LEVEL = level;
	}

	FILE* fp;
	if (file == NULL) {
		ensure_path_exists("logs");
		LOG_FILE = "logs/log.txt";
	} else {
		LOG_FILE = file;
	}

	fp = fopen(LOG_FILE, "a");

	fclose(fp);
}

void ensure_path_exists(const char* path) {
	struct stat st = {0};

	if (stat(path, &st) == -1) {
	    mkdir(path, 0700);
	}
}
