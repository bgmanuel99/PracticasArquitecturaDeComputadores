#include <mpi.h>
#include <stdio.h>
#include <time.h>

void repetir(int argc, char** argv){
    
}

int main(int argc, char** argv){
    for(int i = 0; i < 2; i++){
        int buffer[1] = {1};
        int nproc=50;
        int myrank = 0;
        MPI_Status status;

        MPI_Init(&argc,&argv);
        MPI_Comm_size (MPI_COMM_WORLD, &nproc);
        MPI_Comm_rank (MPI_COMM_WORLD,&myrank);
        if(myrank == 0){
            if(buffer[2] != 0){
                MPI_Recv(buffer, 1, MPI_INT, 49, 50, MPI_COMM_WORLD,&status);
            }
            printf("I am master, sending the message: %d.\n", buffer[0]);
            MPI_Send(buffer, 1, MPI_INT, myrank+1, 50, MPI_COMM_WORLD);
        }else{
            MPI_Recv(buffer, 1, MPI_INT, myrank-1, 50, MPI_COMM_WORLD,&status);
            printf("I am the slave: %d, receiving the message: %d\n", myrank, buffer[0]);
            if(myrank != 49) MPI_Send(buffer, 1, MPI_INT, myrank+1, 50, MPI_COMM_WORLD);
        }
        MPI_Finalize();
    }
    
    return 0;
}