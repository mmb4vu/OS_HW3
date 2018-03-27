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
#include <iostream>
#include <sstream>
#include <math.h>
#include <ctime>

using namespace std;

/* Simple helper function to find the log base 2 of a given number */
int log_2 (int x){
        int result = -1;
        while (x) {
                result++;
                x = x >> 1;
        }
        return result;
}

/* Simple helper function which detemines the maximum of two integers */
int maxVal( int x, int y){
        int max;
        if (x > y) max = x;
        else max = y;
        return max;
}


int main()
{

        int size = 4096; // changed this value during testing
        int array[size];

        // inizialize array
        for (int i = 0; i < size; ++i)
                array[i] = i;

        // generate random numbers to fill array
        for (int i = size - 1; i > 0; --i) {
                // generate random index
                int w = rand()%i;
                // swap items
                int t =array[i];
                array[i] = array[w];
                array[w] = t;
        }

        clock_t begin = clock(); // for timing
        int i, j, k, max, start, end;
        int count = 0;

        printf("LOG_2(%d) is %d\n",size, log_2(size)); // verifying log value

        for (i = 0; i < log_2(size); i++) {
                printf("Round: %d ----------------\n", count);
                count++;
                for (j = 0; j < size; j+= 2) {
                        start = (int)pow(2,i) * j;
                        end = (int)start + (int)pow(2,i);
                        if (start >= size)
                                continue;
                        max = maxVal(array[start], array[end]);
                        array[start] = max;
                }

                for (k = 0; k < size; k++) {
                        printf("%d\n", array[k] );
                }

        }

        // final results
        printf("FINAL MAX: %d\n", max );
        printf("TOTAL ROUNDS: %d\n", count );

        // find time
        clock_t t_end = clock();
        double elapsed_secs = double(t_end - begin) / CLOCKS_PER_SEC;
        cout << (double)elapsed_secs << endl;

        return 0;
}
