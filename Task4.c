#include <stdio.h>
#include <unistd.h>
#include <omp.h>

void main()
{
	int x = 0, y = 0, z = 0;
	omp_set_num_threads(3);
	printf("\n\nInitial value for variable x = 0, y = 0 & z =0\n\n");
	
	#pragma omp parallel
	{
		#pragma omp single
		{	

			#pragma omp task shared(x)
			{
				sleep(5);
				x = 5;
				
				#pragma omp task shared(x)
				{
					x = x + 3;
				}
			}

			#pragma omp task shared(y)
            {        	
				sleep(5);
				y = 10;
			}		

		}
	}
		
	z = x + y;
	printf("\nCalculation Performance:\nx + y = z (here, x = 8, y = 10 so expected z = 18)\n\n");
	printf("The addition operation performed and answer to x + y is %d\n\n",z);
	
	#pragma omp taskwait	
	printf("\n\"Taskwait suspended this current task till all child task get complete. Here child tasks are Task 1: x=5, Task 2: y=10\"\n");
	z = x + y;
	printf("The addition operation performed and answer to x + y is %d\n\n",z);
}
