#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000
int find;
typedef struct Tstore
{
		int num;
		struct Tstore *left;
		struct Tstore *right;
}store;

store *addtree(store *p, int num);
store *deltree(store *p, int num);
void print_tree(store *p);
void search(store *p, int num);
void print_level(store *p, int level);
int insert_max_heap(int heap[],int num);
void heap_down(int heap[],int N);
void swap(int *a,int *b);
int high;

int main()
{
		printf("(B)inary Search Tree.\n");
		printf("(H)eap.\n");
		char n, menu, menu_B, menu_H;
		int num, i, maxhigh = 0;
		int heap[MAX];
		heap[0] = 0;
		store *root = NULL;
		
		scanf("%c",&menu);
		scanf("%c",&n); // get \n

		while(menu == 'B' || menu == 'b')
		{
				printf("(I)nsert a number.\n");
				printf("(D)elete a number.\n");
				printf("(S)earch a number.\n");
				printf("(P)rint in infix & level order.\n");
				scanf("%c",&menu_B);
				scanf("%c",&n); // get \n
				if(menu_B == 'I' || menu_B == 'i')
				{
						printf("Enter a number : ");
						scanf("%d",&num);
						scanf("%c",&n); // get \n
						high = 0;
						root = addtree(root,num);
						if(high > maxhigh)
								maxhigh = high;
				}
				else if(menu_B == 'd' || menu_B == 'D')
				{
						printf("Enter a number to delete : ");
						scanf("%d",&num);
						scanf("%c",&n);
						find = 0;
						search(root,num);
						if(find == 1)
								root = deltree(root,num);
						else if(find == 0)
								printf("Number not found\n\n");
				}
				else if(menu_B == 'S' || menu_B =='s')
				{
						printf("Enter the element to search : ");
						scanf("%d",&num);
						scanf("%c",&n);
						printf("%d\n",num);
						find = 0;
						search(root,num);
						if(find == 1)
								printf("BINGO! Number is found.\n\n");
						else if(find == 0)
								printf("SORRY. Number not found.\n\n");
				}
				else if(menu_B == 'P' || menu_B == 'p')
				{
						printf("The tree in infix order : ");
						print_tree(root);
						printf("\nThe tree in level order : ");
						for(i=0;i<maxhigh;i++)
								print_level(root,i);
						printf("\n");
				}				
		}
		while(menu == 'H' || menu == 'h')
		{
				printf("(I)nsert a number.\n");
				printf("(D)elete the max number.\n");
				printf("(P)rint the heap queue.\n");
				scanf("%c",&menu_H);
				scanf("%c",&n); // get \n

				if(menu_H == 'I' || menu_H == 'i')
				{
						printf("Enter a number : ");
						scanf("%d",&num);
						scanf("%c",&n); // get \n
						heap[0] = insert_max_heap(heap,num);
				}
				else if(menu_H == 'd' || menu_H == 'D')
				{
						if(heap[0] == 0)
								printf("The heap is empty\n");
						else
						{
								rewind(stdin);
								int i;
								heap_down(heap,heap[0]);
								printf("After delete the max : ");
								heap[0]--;
								for(i=0;i<=heap[0];i++)
										printf("%d ",heap[i]);
								printf("\n");
						}
						
				}

				else if(menu_H == 'P' || menu_H == 'p')
				{
						int i;
						printf("The data in the heap queue : ");
						for(i=1;i<=heap[0];i++)
								printf("%d ",heap[i]);
						printf("\n");
				}
		}


		return 0;
}


store *addtree(store *p, int num)
{
		if(p == NULL)
		{
				high++;
				p = (store *)malloc(sizeof(store));
				p->num = num;
				p->left = p->right = NULL;
				return p;
		}
		else if(num == p->num)
				return p;
		else if(num > p->num)
		{
				high++;
				p->right = addtree(p->right,num);
		}
		else
		{
				high++;
				p->left = addtree(p->left,num);
		}
		return p;
}

void search(store *p, int num)
{
		if(p == NULL)
				return;
		else if(p->num == num)
		{
				find = 1;
				return;
		}
		else if(p->num > num)
		{
				if(p->left == NULL)
						return;
				else
						search(p->left, num);
		}
		else
		{
				if(p->right == NULL)
						return;
				else
						search(p->right, num);
		}
		return;
}

void print_tree(store *p)
{
		if(p != NULL)
		{
				print_tree(p->left);
				printf("%d ", p->num);
				print_tree(p->right);
		}
		return;
}

store *deltree(store *p, int num)
{
		if(num == p->num) 
		{
				if(p->left == NULL && p->right == NULL) // 都沒有子樹
						p = NULL;
				else if(p->left == NULL && p->right != NULL) //只有右子樹
				{
						p->num = p->right->num;
						p->left = p->right->left;
						p->right = p->right->right;
				}
				else if(p->right == NULL && p->left != NULL) //只有左子樹
				{
						p->num = p->left->num;
						p->right = p->left->right;
						p->left = p->left->left;
				}
				else //兩子樹都有
				{
						store *temp = p->left;
						while(temp->right != NULL)
								temp = temp->right;
						p->num = temp->num;
						if(temp->left == NULL)
								temp = NULL;
						else
						{
								temp->num = temp->left->num;
								temp->right = temp->left->right;
								temp->left = temp->left->left;
						}
				}
		}
		else if(p->num > num) //一直往左子樹找,直到符合
				p->left = deltree(p->left, num);
		else //一直往右子樹找,直到符合
				p->right = deltree(p->right, num);
		return p;
}

void print_level(store *p,int level)
{
		if(p == NULL)
				return;
		else if(level == 0)
				printf("%d ",p->num);
		else
		{
				print_level(p->left, level-1);
				print_level(p->right, level -1);
		}
		return;
}

int insert_max_heap(int heap[],int num)
{
		int i;
		if(heap[0] == 0) // no num
		{
				heap[1] = num;
				heap[0]++;
		}
		else
		{
				heap[0]++;
				for(i=heap[0]; i!=1; i=i/2)
				{
						if(num > heap[i/2]) // bigger than father
								heap[i] = heap[i/2]; // father move down
						else // no bigger than father
								break;
				}
				heap[i] = num;
		}
		return heap[0];
}
void  heap_down(int heap[],int N)
{
		int i,temp,finished;
		finished = 0;
		heap[1] = heap[N];
		temp = heap[1];
		N=N-1;
		i=1;
		while( i <= N && finished == 0)
		{
				if(heap[i*2] > heap[i*2+1] && heap[i*2]>heap[i])
				{
						heap[i] = heap[i*2];
						heap[i*2] = temp;
						i=i*2;
				}
				else if(heap[i*2+1] > heap[i*2] && heap[i*2+1]>heap[i])
				{
						heap[i] = heap[i*2+1];
						heap[i*2+1] = temp;
						i=i*2+1;
				}
				else
						break;
		}
}
void swap(int* a,int *b)
{
		int temp = *a;
		*a = *b;
		*b = temp;
}
