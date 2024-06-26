#include<omp.h>
#include<stdio.h>
#include<stdlib.h>

static long num_steps=100000;

double step;

#define NUM_THREADS 2

void main()
{
    int nthreads, sum[NUM_THREADS];
    step=1.0/(double)num_steps;
    omp_set_num_threads(NUM_THREADS);
    
   
    
    #pragma omp parallel
    {
    	int i,id, nthrds;
    	
    	double x;
    	
    	id=omp_get_thread_num();
    	nthrds=omp_get_num_threads();
    	
    	if(id==0)
    	{
    	   nthreads=nthrds;
    	}
    	
    	for(i =id, sum[id]=0; i < num_steps; i+=nthrds)
    	{
    	   x=(i+0.5)*step;
    	   sum[id]+= 4.0/(1.0+x*x);  
    	}
    }
    
    int i;
    double pi=0.0;
    
    for(i=0;i<nthreads;i++)
    	pi+=sum[i]*step;
    	
    printf("%f",pi);
    
}
