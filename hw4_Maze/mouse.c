#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define ROAD '0'
#define PASS '2'
#define DEADEND '3'
#define Xsize 15
#define Ysize 15

typedef struct TNode
{
		int x;
		int y;
		struct TNode *next;
}point;

typedef struct stack
{
		int count;
		point *stack;
}Stack;

Stack head; //head of stack

point *creatnode(int x,int y);
void push(point *temp);
point *pop(void);

int main(void)
{
		FILE *fp;
		char map[Ysize][Xsize]; // maze map
		int cur_x,cur_y; // current point X Y
		int i,j;
		point *node;
		point *ptr;
		point *result = NULL;

		
		fp = fopen("maze","r");

		if(!fp)
		{
				printf("File not exit!\n");
				return 0;
		}

        // read map 
	
        for(i=0;i<Ysize;i++)
		{
				char c;
				for(j=0;j<Xsize;j++)
				{
						fscanf(fp,"%c",&map[i][j]);
						printf("%c",map[i][j]);
				}
				printf("\n");
				fscanf(fp,"%c",&c);
		}

		fclose(fp);

        // set initial value
		head.count = 0;
		head.stack = NULL;

		cur_x = 0;
		cur_y = 0;

        // run map 
		while((cur_x != Xsize-1)||(cur_y != Ysize-1))
		{
				map[cur_y][cur_x] = PASS; // make path
				if((map[cur_y][cur_x+1] == ROAD) && (cur_x+1 < Xsize)) // right
				{
						node = creatnode(cur_x,cur_y);
						push(node);
						cur_x ++;
				}
				else if((map[cur_y+1][cur_x] == ROAD) && (cur_y+1 < Ysize)) // down
				{
						node = creatnode(cur_x,cur_y);
						push(node);
						cur_y ++;
				}
				else if((map[cur_y-1][cur_x] == ROAD) && (cur_y-1 >= 0)) // up
				{
						node = creatnode(cur_x,cur_y);
						push(node);
						cur_y --;
				}
				else if((map[cur_y][cur_x-1] == ROAD) && (cur_x-1 >= 0)) // left
				{
						node = creatnode(cur_x,cur_y);
						push(node);
						cur_x --;
				}
				else // No ROAD can run
				{
						map[cur_y][cur_x] = DEADEND;
						node = pop();
						cur_x = node->x;
						cur_y = node->y;
						free(node);
				}
		}
	
		
		node = creatnode(cur_x,cur_y);//push last point
		push(node);


		// inverse stack
		for(node = head.stack;node != NULL;)
		{
				ptr = node; 
				node = node->next;
				ptr->next = result;
				result = ptr;
		}

        
	    // put x,y to result
		fp = fopen("result.txt","w");
		for(node = result;node != NULL;node = node->next)
				fprintf(fp,"%d,%d\n",node->x,node->y);

		fclose(fp);

		return 0;
}

// creat new node
point *creatnode(int x,int y)
{
		point *newnode;

		newnode = (point *)malloc(sizeof(point));
		newnode->x = x;
		newnode->y = y;
		newnode->next = NULL;

		return newnode;
}

// push new node to stack
void push(point *temp)
{
		head.count++;
		temp->next = head.stack;
		head.stack = temp;
}

//pop a node from stack
point *pop(void)
{
		point *temp;

		temp = head.stack;
		head.stack = temp->next;
		temp->next = NULL;
		head.count--;

		return temp;
}




	

