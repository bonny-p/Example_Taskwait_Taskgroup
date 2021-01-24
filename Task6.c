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
		#pragma omp taskgroup
		{
			#pragma omp task shared(x)
			{
				printf("In Task 1, it  will wait for 10 seconds and assign x = 5\n");
				sleep(10);
				x = 5;
				printf("x = 5 assigned now in Task 1.\n");

				#pragma omp task shared(x)
				{
					printf("In Task #, wait for 3 seconds and assign x += 3\n");
					sleep(3);
					x = x + 3;
					printf("In Task #, x assigned x +=3\n");
				}
			}

			#pragma omp task shared(y)
            {        	
				printf("In Task 2, it will wait for 10 seconds and assign y = 10\n");
				sleep(10);
				y = 10;
				printf("y = 10 assigned now in Task 2.\n");
            }	
		}
		}
	}
			
	sleep(2);
	z = x + y;
	printf("\nCalculation Performance:\nx + y = z (here, x = 5, y = 10 so expected z = 15)\n\n");
	printf("The addition operation performed and answer to x + y is %d\n\n",z);
		
	#pragma omp taskwait	
	printf("\n\"Taskwait suspended this current task till all child task get complete. Here child tasks are Task 1: x=5, Task 2: y=10\"\n");
	z = x + y;
	printf("The addition operation performed and answer to x + y is %d\n\n",z);
}