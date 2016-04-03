#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000

typedef struct Tinfo
{
		int student_No;
		char Name[20];
		int Math_score;
		int Chinese_score;
}info;

info array[MAX];

int studentNo_comp(const void*,const void*);
int Math_comp(const void*,const void*);
int Chinese_comp(const void*,const void*);

int main(int argc,char *argv[])
{
		int n=0,N=0;
		int i,comd;
		char input[100];
		char *store[100];
		char *ptr;
		FILE *fp; 

		fp = fopen(argv[1],"r");

		while(1)
		{
				printf("--------------------\n1)sort by student No\n2)sort by Chinese score\n3)sort by Math score\n");
				scanf("%d",&comd);
				printf("\n");
				
				while(fgets(input,100,fp) != NULL)
				{
						ptr = strtok(input," \n\t");
						while(ptr != NULL)
						{
								store[n] = (char *)malloc(100);
								strcpy(store[n],ptr);
								n++;
								ptr = strtok(NULL," \n\t");
						}
						
						array[N].student_No = atoi(store[0]);
						strcpy(array[N].Name,store[1]);
						array[N].Math_score = atoi(store[2]);
						array[N].Chinese_score = atoi(store[3]);
						N++;
						n=0;
				}

				if(comd == 1)
				{
						qsort(array,N,sizeof(array[0]),studentNo_comp);
				}
				else if(comd == 2)
				{
						qsort(array,N,sizeof(array[0]),Math_comp);
				}
				else if(comd == 3)
				{
						qsort(array,N,sizeof(array[0]),Chinese_comp);
				}
				
				for(i=0;i<N;i++)
				{
						printf("%d %s %d %d\n",array[i].student_No,array[i].Name,array[i].Math_score,array[i].Chinese_score);
				}
				
		}
		return 0;
}

int studentNo_comp(const void *a,const void *b)
{
		return ((*(info*)a).student_No-(*(info*)b).student_No);
}
int Math_comp(const void *a,const void *b)
{
		return ((*(info*)a).Math_score-(*(info*)b).Math_score);
}
int Chinese_comp(const void *a,const void *b)
{
		return ((*(info*)a).Chinese_score-(*(info*)b).Chinese_score);
}

