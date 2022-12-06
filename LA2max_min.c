#include<stdio.h>
#include<mpi.h>
#include <limits.h>
int main(int argc, char** argv)
{
 int my_rank;
 int array[10];
 //printf("Enter 10 number");
 
 MPI_Status status;
 MPI_Init(&argc, &argv);
 MPI_Comm_rank(MPI_COMM_WORLD, &my_rank);
 if (my_rank==0){
 for(int i=0;i<10;i++){
     //cin>>array[i]; 
     array[i]=10-i;
     //scanf("%d",&array[i]);
 }
   MPI_Send(&array,10,MPI_INT,1,10,MPI_COMM_WORLD);
   MPI_Send(&array,10,MPI_INT,2,20,MPI_COMM_WORLD);
   MPI_Send(&array,10,MPI_INT,3,30,MPI_COMM_WORLD);
   MPI_Bcast(&array,10,MPI_INT,0,MPI_COMM_WORLD);

   int a[2];
   int b[2];
   int c[2];
   MPI_Recv(&a,2,MPI_INT,1,10,MPI_COMM_WORLD, &status);
   MPI_Recv(&b,2,MPI_INT,2,20,MPI_COMM_WORLD, &status);
   MPI_Recv(&c,2,MPI_INT,3,30,MPI_COMM_WORLD, &status);
     int m[6]={a[0],b[0],c[0],a[1],b[1],c[1]};
     int min=INT_MAX,max=INT_MIN;
     for(int i=0;i<6;i++){
         if(max<m[i]){
          max=m[i];
        }
        if(min>m[i]){
           min=m[i];
        }  
     }
     //cout<<max<<" "<<min<<endl;
     printf("max= %d,min= %d",max,min);
 }
 else if(my_rank == 1){
   MPI_Recv(&array,10,MPI_INT,0,10,MPI_COMM_WORLD, &status);
    int min=INT_MAX,max=INT_MIN;
    for(int i=0;i<4;i++){
        if(max<array[i]){
          max=array[i];
        }
        if(min>array[i]){
           min=array[i];
        }  
    }
    int a[]={max,min};
    MPI_Send(&a,2,MPI_INT,0,10,MPI_COMM_WORLD);
 }
 else if(my_rank == 2)
 {
 MPI_Recv(&array,10,MPI_INT,0,20,MPI_COMM_WORLD, &status);
  //MPI_Recv(&array,4,MPI_INT,0,10,MPI_COMM_WORLD, &status);
    int min=INT_MAX,max=INT_MIN;
    for(int i=4;i<7;i++){
        if(max<array[i]){
          max=array[i];
        }
        if(min>array[i]){
           min=array[i];
        }  
    }
    int b[]={max,min};
    MPI_Send(&b,2,MPI_INT,0,20,MPI_COMM_WORLD);
  
 }
 else if(my_rank == 3)
 {
 MPI_Recv(&array,10,MPI_INT,0,30,MPI_COMM_WORLD, &status);
 // MPI_Recv(&array,4,MPI_INT,0,10,MPI_COMM_WORLD, &status);
    int min=INT_MAX,max=INT_MIN;
    for(int i=7;i<10;i++){
        if(max<array[i]){
          max=array[i];
        }
        if(min>array[i]){
           min=array[i];
        }  
    }
    int c[]={max,min};
    MPI_Send(&c,2,MPI_INT,0,30,MPI_COMM_WORLD);
 
 }
 MPI_Finalize();
 return 0;
}
