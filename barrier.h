#ifndef BARRIER_H
#define BARRIER_H

#include <semaphore.h>
#include <unistd.h>
#include <stdio.h>


class Barrier {

public:

int init;
int value;
sem_t mutex;      // ensures mutual exclusion
sem_t waitq;      // ensures bounded waiting
sem_t throttle;   // guard against permanent wait



Barrier();
Barrier(int init);
void wait();

};

#endif
