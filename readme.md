### OpenMP
```
g++ open-mp.cpp -o sum2-openmp -fopenmp
```
```
./sum2-openmp
```

### MPI
```
mpicxx mpi.cpp -o sum2-mpi
```
```
mpirun -np 4 ./sum2-mpi
```