#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Given a list of N numbers
#define N 8

// Program will use N/2 threads to find the solution
#define N_THREADS N/2

using namespace std;

/* g++ -o sample sample.cpp barrier.cpp -lm -lpthread -lrt */

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
        //  int array[] = {111,222,3,671};
        //  int size = sizeof(array)/sizeof(array[0]); // change to 8000 for total possible numbers

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
                        if (start >= N) break;
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
