#include <mpi.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

int main(int argc, char* argv[]) {
    int size, rank;
    
    MPI_Init(&argc, &argv);
    
    MPI_Comm_size(MPI_COMM_WORLD, &size);
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);

    int buffer[size*size];
    int matriz [size][size];

    int k = 1;
    for(int i = 0; i < size; i++){
        for(int j = 0; j < size; j++){
            matriz[i][j] = k;
            k++;
        }
    }

    int my_row[size];

    for(int i = 0; i < sizeof(matriz); i++){
        my_row[i] = matriz[i][rank];
    }
    
    MPI_Allgather(&my_row, size, MPI_INT, buffer, size, MPI_INT, MPI_COMM_WORLD);

    if(rank == 0){
        printf("Matriz transpuesta realizada con MPI: \n");
        for(int i = 0; i < (size*size); i++){
            if(i % size == 0){
                printf("\n");
            }
            printf("%d ",buffer[i]);
        }
    }
    printf("\n");

    MPI_Finalize();
 
    return 0;
}