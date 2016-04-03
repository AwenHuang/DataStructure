#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int graph[26][26];
void one_bfs(char filename[],char start[]);
void bfs(int v,int n);
void two_minicost(char filename[]);
int compare(const void*a,const void*b);
typedef struct Tdata
{
		int point1;
		int point2;
		int weight;
}data;

data array[100];

int main(int argc,char *argv[])
{
		//��argc�ӧP�_�Ӱ������
		if(argc == 4)
				one_bfs(argv[1],argv[3]);
		else if(argc == 3)
				two_minicost(argv[1]);
}

void one_bfs(char filename[],char start[])
{
		int i,j,edge,size=0;
		int mark[26]={0};
		char one,two;
		FILE *fp;
		fp = fopen(filename,"r");
		char input[5];
		fscanf(fp,"%d",&edge);
		for(i=0;i<26;i++) // ��l��
		{
				for(j=0;j<26;j++)
						graph[i][j] = 0;
		}
		while(fgets(input,5,fp)!=NULL)
		{
				
				if(strlen(input)>2)
				{
					mark[input[0]-65] = 1;//�O�����X���I
					mark[input[3]-65] = 1;
					graph[input[0]-65][input[3]-65] = 1; //�O���s�q
				}
		}
		for(i=0;i<26;i++)
				size = size + mark[i];//�`�@���X���I

		printf("0, %c",start[0]);
		bfs(start[0]-65,size);
}
int rec=1;
void bfs(int v,int n)
{
		char record[n];
		int i,k=0,r=0;
		while(k < n) // �p�G���]���U�ӳ��I
		{
				if(graph[v][k] == 1)
				{
						record[r++] = k;
						printf("%d, %c\n",rec,k+65);
						for(i=0;i<n;i++)
								graph[i][k] = 2;
				}
				k++;
		}
		rec++;//�O�����h
		for(i=0;i<r;i++)//�~�򩹤U��
				bfs(record[i],n);
}

void two_minicost(char filename[])
{
		int i,j,edge,size=0,times=0,n;
		int mark[26]={0};
		char input[100];
		FILE *fp;
		char *ptr,*store[3];
		fp = fopen(filename,"r");
		fscanf(fp,"%d",&edge);
	
		for(i=0;i<26;i++)
		{
				for(j=0;j<26;j++)
						graph[i][j] = 0; // ��l��
		}
		while(fgets(input,100,fp)!=NULL)
		{
				n=0;
				if(strlen(input)>2)
				{
					ptr = strtok(input,", "); // ��r�I�M�ťդ��α�
					while(ptr != NULL) 
					{
							store[n] = (char *)malloc(sizeof(ptr));
							strcpy(store[n],ptr);
							ptr = strtok(NULL,", ");
							n++;
					}
					mark[store[0][0]-65] = 1;
					mark[store[1][0]-65] = 1;
					graph[store[0][0]-65][store[1][0]-65] = atoi(store[2]);//�s�����V�� EX: A,B,3���� �u��A���@��}�C��B B���@�椣�|��A				
				}
		}
		for(i=0;i<26;i++)
				size = size + mark[i];
		for(i=0;i<size;i++)
		{
				for(j=0;j<size;j++)
						printf("%d ",graph[i][j]);
				printf("\n");
		}
		int count,sum=0,record,N=0;;
		int array[100];
		for(i=0;i<size;i++)
		{
				count = 0;
				for(j=0;j<size;j++){
						if(graph[j][i] != 0)
						{
								record = graph[j][i]; //���F���I������O���_��
								count++;
								if(count > 1) //���I���u�@���u�i�F
								{
										if(record > graph[j][i]) // �p�G�����O������p �N�л\�O��
												record = graph[j][i];
										else 
												graph[j][i] = 0;
								}
						}	
				}
				sum = sum + record;
		}
		for(i=0;i<size;i++)
		{
				for(j=0;j<size;j++)
				{
						if(graph[i][j] != 0)
						{
								array[N++].point1 = i;
								array[N++].point2 = j;
								array[N++].weight = graph[i][j];
						}
				}
		}
		qsort(array,N,sizeof(array[0]),compare);
		printf("%d\n",sum);
		for(i=0;i<N;i++)
				printf("%c, %c, %d\n",array[i].point1+65,array[i].point2+65,array[i].weight);
	
}
int compare(const void*a,const void*b)
{
		return ((*(data*)a).weight,(*(data*)b).weight);
}
		
		
				
				
						
								























