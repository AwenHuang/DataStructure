#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#define MAX 1000


typedef struct polynomialList
{
		struct polynomialList *next;
		float coef;
		unsigned int exp;
}Poly;

Poly *polyA = NULL,*polyB = NULL,*polyC = NULL,*polyD = NULL;

Poly *insertIn(float coef,unsigned int exp,Poly *ptr);
void printList(Poly *head);
void attach(float coef,int exp,Poly **ptr);
Poly *polyadd(Poly *poly1,Poly *poly2); 
Poly *polymul(Poly *poly1,Poly *poly2);

int main(int argc,char *argv[])
{
		float coef_tmp;
		unsigned int exp_tmp;
		FILE *fp1,*fp2;

		fp1 = fopen(argv[1],"r");
		fp2 = fopen(argv[2],"r");

		while(fscanf(fp1,"%f %d", &coef_tmp, &exp_tmp) != EOF)
			polyA = insertIn(coef_tmp,exp_tmp,polyA);
			
		while(fscanf(fp2,"%f %d", &coef_tmp, &exp_tmp) != EOF)
			polyB = insertIn(coef_tmp,exp_tmp,polyB);

		polyC = polyadd(polyA, polyB);
		polyD = polymul(polyB,polyC);
		
		printf("A:");
		printList(polyA);
		
		printf("\nB:");
		printList(polyB);

		printf("\nC:");
		printList(polyC);

		printf("\nD:");
		printList(polyD);
		printf("\n");
		
		return 0;
}

void printList(Poly *head)
{
		
		Poly *ptr = head;
		while(ptr != NULL)
		{
				printf("%.1fx^%d ", ptr->coef, ptr->exp);
				ptr = ptr->next;
		}
}

Poly *insertIn(float coef, unsigned int exp, Poly *ptr)
{
		Poly *ptr2,*ptr3;
		
		Poly *head = ptr;
		
		ptr2 = ptr;
		ptr3 = ptr;
		
		Poly *temp = (Poly *)malloc(sizeof(Poly));
		temp->coef = coef;
		temp->exp = exp;
		temp->next = NULL;

		if(head == NULL)
		{
				head = temp;
				return head;
		}
		if(temp->exp > head->exp)
		{
				temp->next = head;
				head = temp;
		}
		else if(temp->exp < head->exp)
		{
				ptr2 = head;
				ptr3 = head->next;
				
				if(ptr3 == NULL)
				{
						ptr2->next = temp;
						return head;
				}
				while(ptr3 != NULL)
				{
						if(temp->exp > ptr3->exp)
						{
								ptr2->next = temp;
								temp->next = ptr3;
								return head;
						}
						else if(temp->exp < ptr3->exp)
						{
								ptr2 = ptr3;
								ptr3 = ptr3->next;
						}
						else // ptr3 & temp are same exp
						{
								ptr3->coef = ptr3->coef + temp->coef;
								return head;
						}
				}
				ptr2->next = temp;		
		}
		else // head & temp are same exp
				head->coef = head->coef + temp->coef;
		return head;
}

void attach(float coef,int exp,Poly **ptr)
{
		Poly *temp;
		temp = (Poly *)malloc(sizeof(Poly));
		temp->coef = coef;
		temp->exp = exp;
		temp->next = NULL;
		(*ptr)->next = temp;
		*ptr = temp;
}

Poly *polyadd(Poly *poly1,Poly *poly2)
{
		Poly *rear;
		int sum;
		rear = (Poly *)malloc(sizeof(Poly));
		polyC = rear;
       
       //both of them have value
		while(poly1 != NULL && poly2 != NULL)
		{
				if(poly1->exp > poly2->exp)
				{
						attach(poly1->coef,poly1->exp,&rear);
						poly1 = poly1->next;
				}
				else if(poly1->exp < poly2->exp)
				{
						attach(poly2->coef,poly2->exp,&rear);
						poly2 = poly2->next;
				}
				else // same
				{
						sum = poly1->coef + poly2->coef;
						if(sum)
								attach(sum,poly1->exp,&rear);
						poly1 = poly1->next;
						poly2 = poly2->next;
				}
		}
		while(poly1 != NULL || poly2 != NULL)
		{
				rear->next = (Poly *)malloc(sizeof(Poly));
				rear = rear->next;
				rear->next = NULL;

				if(poly1 != NULL)
				{
						rear->coef = poly1->coef;
						rear->exp = poly1->exp;
						poly1 = poly1->next;
				}
				if(poly2 != NULL)
				{
						rear->coef = poly2->coef;
						rear->exp = poly2->exp;
						poly2 = poly2->next;
				}
		}
		//因為先malloc rear 然後每次都加在他後面 所以第一個會是空的
		Poly *temp = polyC;
		polyC = polyC->next;
		free(temp);
						
		return polyC;		
}

Poly *polymul(Poly *poly1,Poly *poly2)
{
		Poly *ptr = poly1;
		Poly *ptr2 = poly2;

		for( ; ptr != NULL; ptr = ptr->next)
		{
				for(ptr2 = poly2; ptr2 != NULL; ptr2 = ptr2->next)
				{
						polyD = insertIn((ptr->coef) * (ptr2->coef), (ptr->exp) + (ptr2->exp), polyD);
				}

		}
		return polyD;
}



		

