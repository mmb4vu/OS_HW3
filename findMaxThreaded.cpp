#include <iostream>
#include <sstream>
#include <fstream>
#include <string>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include <string.h>
#include <pthread.h>

#include "findMaxThreaded.h"
#include "barrier.h"
using namespace std;

int N = 0;
int N_THREADS = 0;
int N_ROUNDS = 0;

Barrier bar;
int array[8192];

int log_2 (int x){
        int result = -1;
        while (x) {
                result++;
                x = x >> 1;
        }
        return result;
}

int maxVal( int x, int y){
        int tempMax;
        if (x > y) tempMax = x;
        else tempMax = y;
        return tempMax;
}

void* findMax (void* arg){
        threadArgs *args = (threadArgs*) arg;
        int x = args->id;
        printf("X: %d\n", x);
        for (int i = 0; i < N_ROUNDS; i++) {
                printf("Round: %d ----------------\n", i);
                int start = (int)pow(2,i) * x;
                printf("Start value: %d\n", start );
                int end = start + (int)pow(2,i);
                printf("End value: %d\n", end);
                if (start >= N) {
                        bar.wait();
                        continue;
                }
                printf("Data pair: <%d , %d>\n", array[start], array[end]);
                int maximum = maxVal(array[start], array[end]);
                printf("Pair Max: %i\n", maximum );
                array[start] = maximum;
                printf("UPDATED ARRAY: \n" );
                printArray(array);
                printf("AH! WE'VE HIT A BARRIER! \n" );
                bar.wait();
        }
        return NULL;
}

void printArray (int arr[]){
        int k;
        for (k = 0; k < N; k++) {
                printf("%d ", array[k]);
        }
        printf("\n");
}

void createThreads(pthread_t *threads, threadArgs *tid){
        for (int i = 0; i < N; i+=2) {
                tid[i/2].id = i;
                pthread_create(&threads[i/2], NULL, findMax, &tid[i/2]);
        }
}

void joinThreads(pthread_t *threads){
        for (int i = 0; i < N_THREADS; i++)
                pthread_join(threads[i], NULL);

}

void getUserInput () {
        std::string getInput;
        while (true) {
                std:: getline(std::cin, getInput);
                if (getInput.empty()) break;
                stringstream convert(getInput);
                convert >> array[N];
                N++;
        }
        printf("The value of N is: %d\n", N);
}

// Driver Code
int main()
{

        getUserInput();
        N_THREADS = N/2;
        N_ROUNDS = log_2(N);

        printf("INITIAL ARRAY: \n" );
        printArray(array);
        printf(" \n" );

        bar.init = N/2;
        bar.value = N/2;

        pthread_t threads[N_THREADS];
        threadArgs tid[N_THREADS];

        // Creating threads
        printf("ENTERING CREATION LOOP -------------- \n");
        createThreads(threads, tid);
        printf("EXITING CREATION LOOP -------------- \n");

        // joining threads i.e. waiting for all threads to complete
        printf("ENTERING JOIN LOOP -------------- \n");
        joinThreads(threads);
        printf("EXITING JOIN LOOP -------------- \n");

        printf("MAX VALUE: %d\n", array[0]);

        return 0;
}
