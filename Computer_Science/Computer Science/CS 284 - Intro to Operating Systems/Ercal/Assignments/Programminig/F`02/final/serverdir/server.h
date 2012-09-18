
#ifndef SERVER_H
#define SERVER_H

#include <pthread.h>

#define MAX_CLIENTS		10

extern pthread_mutex_t clientMutex;
extern pthread_mutex_t mapMutex;
extern pthread_mutex_t houseMutex;
extern pthread_mutex_t updateMutex;

#endif

