#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
#define swap(x,y) {char t; t = x; x=y; y=t;}
char heap[MAX];
char heap_sort_result[MAX]; 

void quick_sort(char array[],int left,int right);
int insert_max_heap(char c);
void heap_sort(int N);
void merge_sort(int N,char array[]);
void merge(int l_max,int r_max,char left[],char right[],char array[]);

int main()
{
		int i,k,N;
		
		char input[MAX];
		char store[MAX];
		char store2[MAX];
		heap[0] = 0;

		fgets(input,MAX,stdin);
		N = strlen(input)-1; // let '/n' go away 
		input[N] = '\0';

		/* do mergesort */
		strcpy(store,input);
		merge_sort(N,store);
		printf("merge sort:%s\n",store);

		/* do qicksort */
		strcpy(store2,input);
		quick_sort(store2,0,N-1);
		printf("quick sort:%s\n",store2);

		/* do heapsort */
	    for(i=0;i<N;i++)
			heap[0] = insert_max_heap(input[i]);
		heap_sort(heap[0]);

		printf("heap sort:");
		for(i=N-1;i>=0;i--) // �q�᭱�}�l�L
				printf("%c",heap_sort_result[i]);

		printf("\n");
		
		return 0;
}

/* ���ΰ}�C�̤ܳp���q,�M����O�s�b��Ӥ��P�}�C�� */
void merge_sort(int N,char array[])
{
		if(N <= 1) // �w�g�O�̤psize
				return;
		int x,y,i,j;

		x = N/2;
		y = N - x;
	
		char left[x-1],right[y-1]; //�ŧi��Ӱ}�C,�õ����諸�j�p

		// ���}�C����Ƥ��O�v�@�s�b��}�C��
		for(i=0;i<x;i++) 
				left[i] = array[i];
		for(i=0;i<y;i++)
				right[i] = array[x + i];

		merge_sort(x,left); // �b�索�䪺�}�C�~�����
		merge_sort(y,right); // �b��k�䪺�}�C�~�����
		merge(x,y,left,right,array); // �X�֨�}�C
}

/* ��ӳQ���Χ����}�C���ۤ���A�o�X���G */
void merge(int l_max,int r_max,char left[],char right[],char array[])
{
		int i,j,k;
		i = j = k = 0;
		while(i < l_max && j < r_max) 
		{
				if(left[i] < right[j]) 
						array[k++] = left[i++];
					
				else if(left[i] > right[j])
						array[k++] = right[j++];
		}
		 
		//�̫ᦳ�i��O����Υk�䦳�Ѿl �N������J�}�C���᭱(�Ѿl���Ʀr�O����L����j��

		while(i < l_max )
				array[k++] = left[i++];

		while(j < r_max)
				array[k++] = right[j++];
}
int insert_max_heap(char c)
{
		int i;
		if(heap[0] == 0) // no character
		{
				heap[1] = c;
				heap[0]++;
		}
		else
		{
				heap[0]++;
				for(i=heap[0];i!=1;i=i/2)
				{
						if(c > heap[i/2]) // bigger than father
								heap[i] = heap[i/2]; // father move down
						else // no bigger than father
								break;
				}
				heap[i] = c;
		}
		return heap[0];
}

int j=0;
void heap_sort(int N)
{
		
		int i;
		char max;
		max = heap[1];   // store heap[1] to max
		heap_sort_result[j++] = max;  // store max to array
	
		heap[1] = heap[N];  // ��heap[1]��s��heap�}�C���̫�@�Ӧr��
		heap[N] = '\0';   // �M���heap�}�C�̫�@�Ӧr���ܦ��r�굲��
		N = N - 1; // heap�}�C�����״��1
	
		heap[0] = 0; // �k�s

		for(i=1;i<=N;i++) // ��ѤU��heap�}�C�A���@��maxheap
			heap[0] = insert_max_heap(heap[i]);
		
		// ���򪺧@heapsort
		while(heap[0] != 0)
			heap_sort(heap[0]); // �@������heap�}�C�S���r������
		
}

void quick_sort(char array[],int left,int right)
{
		int N = strlen(array);
		if(left < right) // ��ܰ}�C�ܤ֦���ӼƦr�H�W
		{
				int i = left; 
				int j = right + 1; // ���F--j,�G��+1
				while(1)
				{
						// �q���V�k��,������j��array[0]���r��
						while(i+1 < N && array[++i] < array[left]);
						// �q�k�V����,������p��array[0]���r��
						while(j-1 > -1 && array[--j] > array[left]);
						if(i >= j)
								break;
						// �p�Gi<j ����ܤj���r���b���b����A�p���b���b�k��A�洫�r����m
						swap(array[i], array[j]);
				}

				//��array�̥��䪺�r���Mj����m�@�洫
				swap(array[left], array[j]);

				quick_sort(array, left, j-1); // �索��i�滼�j
				quick_sort(array, j+1, right); // ��k��i�滼�j
		}
}
