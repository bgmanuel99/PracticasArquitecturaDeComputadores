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

    int *buffer = NULL;
    int localData;

    if (rank == 0) {
        buffer = malloc(size * sizeof(int));

        for(int i = 0; i < size; i++){
            buffer[i] = rank;
        }

        printf("El proceso %d contiene los datos: ", rank);
        for(int i = 0; i < size; i++){
            printf("%d, ", buffer[i]);
        }
        printf("\n");
    }

    MPI_Scatter(buffer, 1, MPI_INT, &localData, 1, MPI_INT, 0, MPI_COMM_WORLD);

    printf("El proceso %d contiene el dato %d\n", rank, localData);
    localData += rank;
    printf("El proceso %d despues de sumar su indice al dato contiene ahora el dato %d\n", rank, localData);

    MPI_Gather(&localData, 1, MPI_INT, buffer, 1, MPI_INT, 0, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Despues de los procesos de scatter y gather ahora el proceso %d contiene los datos: ", rank);
        for(int i = 0; i < size; i++){
            printf("%d, ", buffer[i]);
        }
        printf("\n");

        free(buffer);
    }

    MPI_Finalize();

    return 0;
} 