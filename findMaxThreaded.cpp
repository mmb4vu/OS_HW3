/*
 *   Synchronization with Barriers
 *   CS4414: Operating Systems MP3
 *   Spring 2018
 *
 *   Melony Bennis, mmb4vu
 *
 *   findMaxThreaded.cpp - finds max of N sized array using threads
 *
 */


#include <iostream>
#include <sstream>
#include <stdlib.h>
#include <math.h>
#include <stdio.h>
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
        if (x >= y) tempMax = x;
        else tempMax = y;
        return tempMax;
}

void* findMax (void* arg){
        threadArgs *args = (threadArgs*) arg;
        int x = args->id;
        for (int i = 0; i < N_ROUNDS; i++) {
                int start = (int)pow(2,i) * x;
                int end = start + (int)pow(2,i);
                if (start >= N) {
                        bar.wait();
                        continue;
                }
                int maximum = maxVal(array[start], array[end]);
                array[start] = maximum;
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
}

int main() {

        // Getting user input and putting in array
        getUserInput();
        N_THREADS = N/2;
        N_ROUNDS = log_2(N);

        // Initializing barrier
        bar.init = N/2;
        bar.value = N/2;

        // Initializing threads
        pthread_t threads[N_THREADS];
        threadArgs tid[N_THREADS];

        // Creating threads
        createThreads(threads, tid);

        // joining threads i.e. waiting for all threads to complete
        joinThreads(threads);

        cout << array[0] << endl;

        return 0;
}
