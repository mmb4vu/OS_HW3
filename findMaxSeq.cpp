/*
 *   Synchronization with Barriers
 *   CS4414: Operating Systems MP3
 *   Spring 2018
 *
 *   Melony Bennis, mmb4vu
 *
 *   findMaxSeq.cpp - finds max of N sized array sequentially
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Given a list of N numbers
#define N 8

// Program will use N/2 threads to find the solution
#define N_THREADS N/2

using namespace std;

int array[] = { 1, 5, 35, 34, 22, 14, 15, 18 };
int rounds = 0;
int maximum = 0;


int log_2 (int x){
        int result = -1;
        while (x) {
                result++;
                x = x >> 1;
        }
        return result;
}

int maxVal( int x, int y){
        int max;
        if (x > y) max = x;
        else max = y;
        return max;
}


int main()
{

        int i, j, k, max, start, end;
        int count = 0;

        printf("LOG_2(%d) is %d\n", N, log_2(N));
        printf("BEGINNING ROUNDS---------------\n");

        for (i = 0; i < log_2(N); i++) {
                printf("Round: %d ----------------\n", count);
                count++;
                for (j = 0; j < N; j+= 2) {
                        start = (int)pow(2,i) * j;
                        end = (int)start + (int)pow(2,i);
                        if (start >= N) continue;
                        printf("Data pair: <%d , %d>\n", array[start], array[end]);
                        max = maxVal(array[start], array[end]);
                        printf("Pair Max: %i\n", max );
                        array[start] = max;
                }

                for (k = 0; k < N; k++) {
                        printf("%d\n", array[k] );
                }

        }

        printf("FINAL MAX: %d\n", max );
        printf("TOTAL ROUNDS: %d\n", count );

        return 0;
}
