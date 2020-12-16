#include <mpi.h>
#include <stdio.h>
#include <stdbool.h>

int main(int argc, char** argv){
    int size, rank, value=1, ring = 1, maxRing=3;
    MPI_Status status;
    bool notAlready = true;

    MPI_Init(&argc,&argv);

    MPI_Comm_size (MPI_COMM_WORLD, &size);
    MPI_Comm_rank (MPI_COMM_WORLD, &rank);

    if(rank == 0){
        scanf("%d", &value);
        scanf("%d", &maxRing);
    }

    for (int i = 0; i < maxRing; i++){
        if (rank == 0){
            if(i == maxRing){
                break;
            }

            MPI_Send(&value, 1, MPI_INT, 1, 0, MPI_COMM_WORLD);

            MPI_Recv(&value, 1, MPI_INT, size - 1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            printf("FINAL TOKEN %d\n", value);
        }else{
            MPI_Recv(&value, 1, MPI_INT, rank-1, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            printf("%d ha enviado %d al proceso %d\n", rank, value, (rank+1) % size); // modified

            MPI_Send(&value, 1, MPI_INT, (rank+1)%size, 0, MPI_COMM_WORLD); // modified
        }
    }

    MPI_Finalize();
    
    return 0;
}