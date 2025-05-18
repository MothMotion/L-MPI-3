#include "config.h"
#include "random.h"
#include "vec_oper.h"
#include "timer.h"

#include <time.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>

#include <mpi.h>

int main(int argc, char** argv) {
  srand(time(NULL));
  const uint32_t arr_size = ARRAY_SIZE;
  const uint32_t cycles   = CYCLES;

  arr_t *arr1 = malloc(arr_size * sizeof(arr_t)),
        *arr2 = malloc(arr_size * sizeof(arr_t)),
        *out  = malloc(arr_size * sizeof(arr_t));

  float sum_time = 0.0, dif_time = 0.0,
        mul_time = 0.0, div_time = 0.0;

  #ifndef SERIAL
  MPI_Init(&argc, &argv);
  int32_t rank, size;
  MPI_Comm_rank(MPI_COMM_WORLD, &rank);
  MPI_Comm_size(MPI_COMM_WORLD, &size);
  for(uint32_t i=0; i<cycles; ++i) {
    if(rank == 0)
      Randomize(arr1, arr_size, MIN_RAND, MAX_RAND);
    if(size == 1 || size >= 2 && rank == 1)
      Randomize(arr2, arr_size, MIN_RAND, MAX_RAND);
    MPI_Barrier(MPI_COMM_WORLD);

    MPI_TIME(Summ, sum_time, cycles, rank, arr1, arr2, out, arr_size);
    MPI_TIME(Diff, dif_time, cycles, rank, arr1, arr2, out, arr_size);
    MPI_TIME(Mult, mul_time, cycles, rank, arr1, arr2, out, arr_size);
    MPI_TIME(Div, div_time, cycles, rank, arr1, arr2, out, arr_size);
  }
  MPI_Finalize();
  if(rank == 0)
    printf("Parallel execution:\n\tSum:\t%f\n\tDif:\t%f\n\tMul:\t%f\n\tDiv:\t%f\n",
         sum_time, dif_time, mul_time, div_time);

  #else
  for(uint32_t i=0; i<cycles; ++i) {
    Randomize(arr1, arr_size, MIN_RAND, MAX_RAND);
    Randomize(arr2, arr_size, MIN_RAND, MAX_RAND);

    ADDTIME_COR(Summ, sum_time, cycles, arr1, arr2, out, arr_size);
    ADDTIME_COR(Diff, dif_time, cycles, arr1, arr2, out, arr_size);
    ADDTIME_COR(Mult, mul_time, cycles, arr1, arr2, out, arr_size);
    ADDTIME_COR(Div, div_time, cycles, arr1, arr2, out, arr_size);
  }

  printf("Serial execution:\n\tSum:\t%f\n\tDif:\t%f\n\tMul:\t%f\n\tDiv:\t%f\n",
         sum_time, dif_time, mul_time, div_time);

  #endif

  return 0;
}
