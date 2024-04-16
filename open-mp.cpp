#include <math.h>
#include <iostream>
#include <stdio.h>
#include <omp.h>
#include <chrono>

using namespace std::chrono;

inline const char * const BoolToString(bool b)
{
  return b ? "true" : "false";
}

int main(int nargs, char* args[])
{
    int numprocs, proc_rank;
    int counts = 500000;
    int tag = 1;
    int procNum = 6;
    std::cout << procNum << std::endl;

    int a[counts];

    for (int i = 0; i < counts - 2; i++) {
        a[i] = 1;
    }
    a[counts - 2] = 100;
    a[counts - 1] = 500;


    int q = 600;
    bool f = false;

    auto start = steady_clock::now();
	for (int i = 0; i < counts; i++) {
        int leftover = q - a[i];
        for (int j = 0; j < counts; j++) {
            if (a[j] == leftover) {
                f = true;
            }
        }
    }
	auto end = steady_clock::now();


	printf("\nTime elapsed (Sequential): %7.4f", (double)duration_cast<microseconds>(end - start).count() / 1000000.0);
	printf("\n-------\n");


    int part = counts / procNum;
	double startPar = omp_get_wtime();
	#pragma omp parallel for shared(a)
    for (int i = 0; i < procNum; i++) {
        int maxInd = (i + 1) * part;
        for (int j = 0; j < counts; j++) {
            int leftover = q - a[j];
            for (int k = i * part; k < maxInd; k++) {
                if (leftover == a[k]) {
                    f = true;
                }
            }
        }
    }

	double endPar = omp_get_wtime();
    printf("Time elapsed (OpenMP): %7.4f\n", endPar - startPar);


    return 0;
}