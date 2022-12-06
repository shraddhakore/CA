#include<stdio.h>
#include<mpi.h>
#include<math.h>
#include<stdlib.h>

int main(int argc, char **argv){
	int i,count=0,mycount,iterations = 1000;
	double x,y,z,pi;
	int nprocs,rank;
	MPI_Status status;
	
	MPI_Init(&argc,&argv);
	MPI_Comm_size(MPI_COMM_WORLD, &nprocs);
	MPI_Comm_rank(MPI_COMM_WORLD, &rank);
	
	mycount =0;
	for(int i=0;i<iterations;i++){
	
		x = (double)rand()/RAND_MAX;
		y = (double)rand()/RAND_MAX;
		
		
		z = x*x + y*y;
		if(z<=1)
		{
			mycount++;
			
		}
	}
	
	//MPI_Reduce(&mycount,&count,1,MPI_FLOAT,MPI_SUM,0,MPI_COMM_WORLD);
	if(rank!=0){
	
	MPI_Send(&mycount,1,MPI_INT,0,0,MPI_COMM_WORLD);
	
	}		
	if(rank==0){
		for(int i=1; i<nprocs; i++){
		
		MPI_Recv(&mycount,1,MPI_INT,i,0,MPI_COMM_WORLD,&status);
		
		count+=mycount;
		
		}
		count+=mycount;	
		pi = (double)4*count/(nprocs*iterations);
		printf("PI value is %lf after iterations = %d",pi,nprocs*iterations);
	}
	
	
	
	//MPI_Finalize();
	//printf("Hello from process %d of group %d",rank,nprocs);


	MPI_Finalize();
	return 0;
}
