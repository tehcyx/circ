#ifndef _UTILS_H_
#define _UTILS_H_

#include <pthread.h>

pthread_mutex_t users_mutex;
pthread_mutex_t channels_mutex;
pthread_mutex_t sock_mutex;

void mutexes_init();

#endif
