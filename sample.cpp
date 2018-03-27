#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>
#include <time.h>
#include <ctime>
#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "findMaxThreaded.h"
#include "barrier.h"

#define THREAD_COUNT 4

using namespace std;

pthread_barrier_t mybarrier;
Barrier bar;

void* threadFn(void *id_ptr) {
        int thread_id = *(int*)id_ptr;
        int wait_sec = 1 + rand() % 5;
        printf("thread %d: Wait for %d seconds.\n", thread_id, wait_sec);
        sleep(wait_sec);
        printf("thread %d: I'm ready...\n", thread_id);

        //pthread_barrier_wait(&mybarrier);
        bar.wait();

        printf("thread %d: going!\n", thread_id);
        return NULL;
}


int main() {

        clock_t begin = clock();

        int i;
        pthread_t ids[THREAD_COUNT];
        int short_ids[THREAD_COUNT];

        srand(time(NULL));
        bar.init = THREAD_COUNT+1;
        bar.value = THREAD_COUNT+1;
        //  pthread_barrier_init(&mybarrier, NULL, THREAD_COUNT + 1);

        for (i=0; i < THREAD_COUNT; i++) {
                short_ids[i] = i;
                pthread_create(&ids[i], NULL, threadFn, &short_ids[i]);
        }

        printf("main() is ready.\n");

        //  pthread_barrier_wait(&mybarrier);
        bar.wait();

        printf("main() is going!\n");

        for (i=0; i < THREAD_COUNT; i++) {
                pthread_join(ids[i], NULL);
        }

        //  pthread_barrier_destroy(&mybarrier);

        clock_t t_end = clock();
        double elapsed_secs = double(t_end - begin) / CLOCKS_PER_SEC;
        cout << (double)elapsed_secs << endl;

        return 0;
}
