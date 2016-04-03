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
		for(i=N-1;i>=0;i--) // 從後面開始印
				printf("%c",heap_sort_result[i]);

		printf("\n");
		
		return 0;
}

/* 分割陣列至最小片段,然後分別存在兩個不同陣列中 */
void merge_sort(int N,char array[])
{
		if(N <= 1) // 已經是最小size
				return;
		int x,y,i,j;

		x = N/2;
		y = N - x;
	
		char left[x-1],right[y-1]; //宣告兩個陣列,並給予對的大小

		// 把原陣列的資料分別逐一存在兩陣列中
		for(i=0;i<x;i++) 
				left[i] = array[i];
		for(i=0;i<y;i++)
				right[i] = array[x + i];

		merge_sort(x,left); // 在對左邊的陣列繼續分割
		merge_sort(y,right); // 在對右邊的陣列繼續分割
		merge(x,y,left,right,array); // 合併兩陣列
}

/* 兩個被分割完的陣列互相比較，得出結果 */
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
		 
		//最後有可能是左邊或右邊有剩餘 就直接放入陣列的後面(剩餘的數字是比較過後較大的

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
	
		heap[1] = heap[N];  // 把heap[1]改存成heap陣列的最後一個字母
		heap[N] = '\0';   // 然後把heap陣列最後一個字母變成字串結尾
		N = N - 1; // heap陣列的長度減少1
	
		heap[0] = 0; // 歸零

		for(i=1;i<=N;i++) // 把剩下的heap陣列再做一次maxheap
			heap[0] = insert_max_heap(heap[i]);
		
		// 持續的作heapsort
		while(heap[0] != 0)
			heap_sort(heap[0]); // 一直做到heap陣列沒有字母為止
		
}

void quick_sort(char array[],int left,int right)
{
		int N = strlen(array);
		if(left < right) // 表示陣列至少有兩個數字以上
		{
				int i = left; 
				int j = right + 1; // 為了--j,故先+1
				while(1)
				{
						// 從左向右找,直到找到大於array[0]的字母
						while(i+1 < N && array[++i] < array[left]);
						// 從右向左找,直到找到小於array[0]的字母
						while(j-1 > -1 && array[--j] > array[left]);
						if(i >= j)
								break;
						// 如果i<j →表示大的字母在中軸左邊，小的在中軸右邊，交換字母位置
						swap(array[i], array[j]);
				}

				//把array最左邊的字母和j的位置作交換
				swap(array[left], array[j]);

				quick_sort(array, left, j-1); // 對左邊進行遞迴
				quick_sort(array, j+1, right); // 對右邊進行遞迴
		}
}
