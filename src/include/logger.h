#ifndef _LOGGER_H_
#define _LOGGER_H_

#define LOG_CRITICAL "CRITICAL"
#define LOG_ERROR "ERROR"
#define LOG_WARN "WARNING"
#define LOG_DEBUG "DEBUG"

void logger(const char* tag, const char* message, const char* logfile);
void ensurePathExists(const char* path);

#endif
