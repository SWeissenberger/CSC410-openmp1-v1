

//create threads
//if a thread's id is odd, have it return the factorial of its id
//if a thread's id is even, have it return a sum

#include <omp.h>
#include <pthread.h>
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#define NUMT 9
#define THREADS NUMT - 1

int output[NUMT];

int main() {
  
  int thisid;
  int finalsum = 0;
  
  #pragma omp parallel for num_threads(THREADS)
  for (long i = 1; i < NUMT; i++) {

    if ((i % 2) != 0) {
      #pragma omp critical
      thisid = omp_get_thread_num() + 1;
      int fact = 1;
      for (long j = thisid; j > 1; j--) 
      {
        fact = fact * j;
      }

      #pragma omp critical
      output[i] = fact;

      #pragma omp critical
      printf("Thread: %i, Factorial: %i\n", omp_get_thread_num() + 1, fact);
      finalsum = finalsum + fact;
    }

    else if ((i % 2) == 0) {
      #pragma omp critical
      thisid = omp_get_thread_num() + 1;
      int sum = 0;
      for (long j = thisid; j > 0; j--) {
        sum = sum + j;
      }
      
      #pragma omp critical
      output[i] = sum;
      
      #pragma omp critical
      printf("Thread: %i, Sum: %i\n", omp_get_thread_num() + 1, sum);
      finalsum = finalsum + sum;
    }
  }

  for (int i = 1; i < NUMT; i++) {
    printf("Thread %i val: %i\n", i, output[i]);
  }

  printf("Sum of thread outputs: %i\n", finalsum);

  return 0;
}
