#ifndef __THREAD_H__
#define __THREAD_H__

#include <stdint.h>
#include <pthread.h>

typedef struct threadArgs {
        int id; // thread ID
} threadArgs;

int log_2 (int x);
int maxVal( int x, int y);
void* findMax (void* arg);
void printArray (int arr[]);
void createThreads(pthread_t *threads, threadArgs *tid);
void joinThreads(pthread_t *threads);
void getUserInput ();

#endif
