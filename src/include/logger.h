#ifndef _LOGGER_H_
#define _LOGGER_H_

#define LOG_ERROR 20
#define LOG_WARN 15
#define LOG_INFO 10
#define LOG_DEBUG 5

#include <stdarg.h>
#include <stdint.h>

const char* LOG_FILE;
uint8_t LOG_LEVEL;

void log_init(const char* file, const uint8_t level);
void log_debug(const char* message, ...);
void log_error(const char* message, ...);
void log_format(const char* tag, const char* message, va_list args);
void log_info(const char* message, ...);

void ensure_path_exists(const char* path);

#endif
