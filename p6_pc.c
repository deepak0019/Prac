#include<omp.h>
#include<stdlib.h>
#include<stdio.h>


void fill_rand(int N, double *A)
{
  #pragma omp parallel for
  for(int i=0;i<N;i++){
  	A[i]=(double)rand()/RAND_MAX;
  }
}

double Sum_array(int N, double *A)
{
  double sum=0.0;
  
  #pragma omp parallel for reduction(+:sum)
  for(int i=0;i<N;i++){
  	sum+=A[i];
  }
  
  return sum;
}

int main()
{
  const int N=1000;
  

  double *A,sum,runtime;
  
  int numthreads, flag=0;
  
  A=(double*)malloc(N*sizeof(double));
  
  #pragma omp sections
  {
     #pragma omp section
     {
       fill_rand(N,A);
       #pragma omp flush
       flag=1;
       #pragma omp flush(flag)
     }
     
     #pragma omp section
     {
        #pragma omp flush(flag)
        while(flag!=1){
           #pragma omp flush(flag)
        }
        
        #pragma omp flush
        sum=Sum_array(N,A);
     }
  }
  
   printf("Sum of array elements: %f\n", sum);

    // Free dynamically allocated memory
    free(A);
    
    return 0;
}
