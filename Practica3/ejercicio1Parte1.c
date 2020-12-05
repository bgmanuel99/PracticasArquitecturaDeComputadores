#include <math.h>
#include <mpi.h> // Biblioteca de MPI
#include <stdlib.h>
#include <stdio.h>
#include <time.h>

int main(int argc, char *argv[]) {
    int rank, // Identificador de proceso
    size, // Numero de procesos
    valor; // Valor que sera modificado por el proceso 0 y pasado al resto de procesos
    MPI_Status status; 

    MPI_Init(&argc, &argv); // Inicializamos los procesos
    
    MPI_Comm_size(MPI_COMM_WORLD, &size); // Obtenemos el numero total de procesos
    MPI_Comm_rank(MPI_COMM_WORLD, &rank); // Obtenemos el valor de nuestro identificador
    
    srand(time(NULL));

    if (rank == 0) {
        valor = rand() % 4;
        valor *= valor;
        printf("[%d]: envio el dato: %d a [%d] \n", rank, valor, rank+1);
        MPI_Send(&valor, 1, MPI_INT, rank+1, 100, MPI_COMM_WORLD);
    }else{
        MPI_Recv(&valor, 1, MPI_INT, rank-1, 100, MPI_COMM_WORLD, &status);
        printf("[%d]: recibo el dato: %d de [%d] y lo envio a [%d] \n", rank, valor, rank-1, rank+1);
        if(rank < size-1) MPI_Send(&valor, 1, MPI_INT, rank+1, 100, MPI_COMM_WORLD);
    }

    MPI_Finalize();

    return 0;
} 