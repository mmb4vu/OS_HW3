#include <iostream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
#include "thread.h"

// Given a list of N numbers
#define N 8

// Program will use N/2 threads to find the solution
#define N_THREADS N/2

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
int rounds = 0;
int maximum = 0;

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
        int i, start, end;
        threadArgs *args = (threadArgs*) arg;
        for (i = 0; i < 2; i++) {
                printf("Round: %d ----------------\n", i);
                start = (int)pow(2,i) * args->id;
                printf("Start value: %d\n", start );
                end = start + (int)pow(2,i);
                printf("End value: %d\n", end);
                if (start >= N) {
                        //    pthread_barrier_wait(&mybarrier);
                        break;
                }
                printf("Data pair: <%d , %d>\n", array[start], array[end]);
                int max2 = maxVal(array[start], array[end]);
                maximum = max2;
                printf("Pair Max: %i\n", max2 );
                array[start] = max2;
                printf("I: %i\n", i );
                printf("UPDATED ARRAY: \n" );
                printArray(array);
                printf("AH! WE'VE HIT A BARRIER! \n" );
                //    pthread_barrier_wait(&mybarrier);

        }
        rounds = i;
}

void printArray (int arr[]){
        int k;
        for (k = 0; k < N; k++) {
                printf("%d ", array[k]);
        }
        printf("\n");
}

// Driver Code
int main()
{
        printf("INITIAL ARRAY: \n" );
        printArray(array);
        pthread_t threads[N_THREADS];
        threadArgs tid[N_THREADS];
        pthread_barrier_init(&mybarrier, NULL, N_THREADS);

        // Creating threads
        printf("ENTERING CREATION LOOP -------------- \n");
        for (int i = 0; i < N; i+=2) {
                tid[i/2].id = i;
                printf("Creating threads -------------- \n");
                pthread_create(&threads[i], NULL, findMax, &tid[i/2]);
        }
        printf("EXITING CREATION LOOP -------------- \n");
        // joining threads i.e. waiting for all threads to complete
        printf("ENTERING JOIN LOOP -------------- \n");
        for (int i = 0; i < N_THREADS; i++) {
                printf("Joining threads --------------- \n");
                pthread_join(threads[i], NULL);
        }
        printf("EXITING JOIN LOOP -------------- \n");


        printf("DESTROYING BARRIER! \n" );
        //    pthread_barrier_destroy(&mybarrier);

        printf("MAX VALUE: %d\n", maximum);
        printf("TOTAL ROUNDS: %d\n", rounds+1);
        printf("FINAL ARRAY: \n" );
        printArray(array);
        return 0;
}
