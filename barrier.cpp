/*
 *   Synchronization with Barriers
 *   CS4414: Operating Systems MP3
 *   Spring 2018
 *
 *   Melony Bennis, mmb4vu
 *
 *   barrier.cpp - implementation simple memory barrier
 *
 *   Compile: make
 *   Headers: barrier.h thread.h
 *   Executable: max
 *
 */

#include "barrier.h"

/* Constructor */
Barrier::Barrier() {
        init = 0;
        value = init;
        sem_init(&mutex, 0, 1);
        sem_init(&waitq, 0, 0);
        sem_init(&throttle, 0, 0);
}

/* Initializing barrier, and sets counting semaphore to use binary func. */
Barrier::Barrier(int init_) {
        init = init_;
        value = init;
        sem_init(&mutex, 0, 1);
        sem_init(&waitq, 0, 0);
        sem_init(&throttle, 0, 0);

}

/* implementation of pthread_wait() as discussed in class */
void Barrier::wait() {
        sem_wait(&mutex);
        value--;
        if(value != 0) {
                sem_post(&mutex);
                sem_wait(&waitq);
                sem_post(&throttle);
        }
        else{
                for (int i = 0; i < init - 1; i++) {
                        sem_post(&waitq);
                        sem_wait(&throttle);
                }
                value = init;
                sem_post(&mutex);
        }
}
