/*
   Implementation of memory barrier via binary semaphores
   taken from OS lecture: MARCH 22, 2018
 */

#include "barrier.h"

Barrier::Barrier() {
        printf("Constructor is constructing!! \n");
}

Barrier::Barrier(int init_) {
        init = init_;
        value = init;
        sem_init(&mutex, 0, 1);
        sem_init(&waitq, 0, 0);
        sem_init(&throttle, 0, 0);

}

void Barrier::wait() {
        sem_wait(&mutex);
        value--;

        if(value != 0) {
                printf("WAITING FOR THREADS. ---------\n");
                sem_post(&mutex);
                sem_wait(&waitq);
                sem_post(&throttle);
        }
        else{
                printf("THREADS COMPLETE. ----------- \n");
                for (int i = 0; i < init - 1; i++) {
                        sem_post(&waitq);
                        sem_wait(&throttle);
                }
                value = init;
                sem_post(&mutex);
        }
}
