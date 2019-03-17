//#include<stdio.h>
#include"dyn_memory.c"
#include<stdio.h>

void main()
{
	int *pt;
	printf("\n\nbefore allocating\n\n");
	//printf("%d\t%d\t%d\t%d\n",pt[0],pt[1],pt[2],pt[3]);
	//uncomment above line to find out what happens before allocating memory block
	printf("\n\nallocatig\n\n");
	pt = (int*)malloc(4*sizeof(int));
	pt[0]=42;
	pt[1]=45;
	pt[2]=23;
	pt[3]=12;
	printf("%d\t%d\t%d\t%d\n",pt[0],pt[1],pt[2],pt[3]);
	pt = (int*)realloc(pt,2*sizeof(int));
	printf("\nreallocating to 2\n\n");
	printf("%d\t%d\t%d\t%d\n",pt[0],pt[1],pt[2],pt[3]);
	printf("\n\nfreeing memory\n\n");
	free(pt);
	printf("%d\t%d\t%d\t%d\n",pt[0],pt[1],pt[2],pt[3]);
	printf("%d\t%d\t%d\t%d\n",pt[0],pt[1],pt[2],pt[3]);
	printf("\n\ndone all process\n");


}
