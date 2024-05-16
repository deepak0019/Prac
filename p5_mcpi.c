#include<omp.h>
#include<stdio.h>
#include<stdlib.h>
#include<time.h>

#define NUM_THREADS 8

static int num_trials=100000;

int main()
{
   double x,y;
   int i;
   
   int pc=0,ps=0;
   
   #pragma omp parallel firstprivate(x,y,i) reduction(+:pc,ps) num_threads(NUM_THREADS)
   {
   	srand48((int)time(NULL));
   	
   	for(i=0;i<num_trials;i++)
   	{
   	   x=(double)drand48();
   	   y=(double)drand48();
   	   
   	   if(x*x+y*y <= 1) pc++;
   	   
   	   ps++;
   	}
   }
   
   double pi=4.0* ((double)pc/(double)ps);
   printf("%f",pi);

   return 0;
}
