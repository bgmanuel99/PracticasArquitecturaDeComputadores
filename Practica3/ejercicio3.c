#include <math.h>
#include <mpi.h> // Biblioteca de MPI
#include <stdlib.h>
#include <stdio.h>

int main(int argc, char *argv[]) {
    int rank, // Identificador de proceso
    size; // Numero de procesos

    MPI_Init(&argc, &argv); // Inicializamos los procesos

    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero total de procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador

    int localData[2];
    int resultSum[2];
    int resultProd[2];

    for(int i = 0; i < 2; i++){
        localData[i] = rank+1;
    }

    MPI_Reduce(localData, resultSum, 2, MPI_INT, MPI_SUM, 0, MPI_COMM_WORLD);
    MPI_Reduce(localData, resultProd, 2, MPI_INT, MPI_PROD, 0, MPI_COMM_WORLD);

    MPI_Barrier(MPI_COMM_WORLD);

    if(rank == 0){
        printf("El resultado de la suma de los arrays es: %d, %d.\n", resultSum[0], resultSum[1]);
        printf("El resultado del producto de los arrays es: %d, %d.\n", resultProd[0], resultProd[1]);
    }

    MPI_Finalize();

    return 0;
} 