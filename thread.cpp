#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "thread.h"
#include "barrier.h"
#include <pthread.h>

using namespace std;


/*
   A maximum-finding binary reduction works much like a basketball tournament: pairs of items can be
   compared in parallel just like pairs of teams play each other in a game. The maximum item (or winner of the
   game) goes on to the next round. If there are N numbers (or N teams), the total number of rounds will be
   log2 N.

   For a given round, we will use individual threads (basketball courts) to execute the comparisons (play the
   games) concurrently. But we must wait until all of the comparisons for a given round have been made before
   we can re-use the threads (courts) to start the next. For this, you will need to implement a barrier primitive.
 */

int array[] = { 1, 5, 35, 34, 22, 14, 15, 18 };
int N =  8;
int N_THREADS = N/2;
int N_ROUNDS = log_2(N);

// Barrier bar(N_THREADS);
Barrier bar(N_THREADS);
pthread_barrier_t mybarrier;

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

void createThreads(){
}

void joinThreads(){
}

int getUserInput (int a) {
        return 0;
}
// Driver Code
int main()
{
        printf("INITIAL ARRAY: \n" );
        printArray(array);
        printf(" \n" );

        pthread_t threads[N_THREADS];
        threadArgs tid[N_THREADS];

        // Creating threads
        printf("ENTERING CREATION LOOP -------------- \n");
        for (int i = 0; i < N; i+=2) {
                tid[i/2].id = i;
                printf("Creating threads -------------- \n");
                pthread_create(&threads[i/2], NULL, findMax, &tid[i/2]);
        }
        printf("EXITING CREATION LOOP -------------- \n");

        // joining threads i.e. waiting for all threads to complete
        printf("ENTERING JOIN LOOP -------------- \n");
        for (int i = 0; i < N_THREADS; i++) {
                pthread_join(threads[i], NULL);
        }
        printf("EXITING JOIN LOOP -------------- \n");


        printf("MAX VALUE: %d\n", array[0]);
        return 0;
}
