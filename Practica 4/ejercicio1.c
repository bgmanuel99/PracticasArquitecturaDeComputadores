#include <stdio.h>
#include <stdlib.h>
#include <mpi.h>
 
int matriz[4][4]={


    {1,2,3,4},
    {5,6,7,8},
    {9,10,11,12},
    {13,14,15,16}
};

int main(int argc, char* argv[])
{
    MPI_Init(&argc, &argv);
 
    // Get number of processes and check that 3 processes are used
    int size;
    MPI_Comm_size(MPI_COMM_WORLD, &size);
 
    // Get my rank
    int my_rank;
    MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);

    int my_row[4];
    // Define my value
    int i;
        for(i = 0; i < 4; i++ ){
        my_row[i] = matriz[i][my_rank];
        //printf("%d ,", my_row[i]);
    }

 
    int buffer[16];
    MPI_Allgather(&my_row, 4, MPI_INT, buffer, 4, MPI_INT, MPI_COMM_WORLD);
    MPI_Allgather(&my_row, 4, MPI_INT, buffer, 4, MPI_INT, MPI_COMM_WORLD);
    MPI_Allgather(&my_row, 4, MPI_INT, buffer, 4, MPI_INT, MPI_COMM_WORLD);
    MPI_Allgather(&my_row, 4, MPI_INT, buffer, 4, MPI_INT, MPI_COMM_WORLD);
 

    if(my_rank==0){
        int j=0;
        for(j; j < 16; j++){
            printf("%d ",buffer[j]);
            if(j==3||j==7||j==11){
                printf("\n");
            }
        }
        printf("\n");
        
    }
    MPI_Finalize();
 
    return EXIT_SUCCESS; 
}