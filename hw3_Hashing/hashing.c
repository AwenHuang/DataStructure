#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define HASHSIZE 5000

int hashF1(char *string);
int hashF2(char *s);

int main()
{
		int act_num,i;
		int hashF1_num;
		char exit[] = "exit";
		char string[100];
		char *array[12];
		char *array_2[HASHSIZE];
		
		for(i=0;i<12;i++)
				array[i] = 0;
		/*for(i=0;i<HASHSIZE;i++)
				array_2[i] = 0;*/
		

		while(1)
		{
				printf("1.Excute Part one\n");
				printf("2.Excute Part two\n");

				scanf("%d",&act_num);

				if(act_num == 1)
				{
						fpurge(stdin);
						while(fgets(string,100,stdin))
						{
								string[strlen(string)-1] = '\0';
								
								if(strcmp(string,exit) == 0)
										break;

								hashF1_num = hashF1(string);
								
								while(array[hashF1_num] != 0)
										hashF1_num ++;
								
								array[hashF1_num] = (char *)malloc(sizeof(array[hashF1_num]));
							 	strcpy(array[hashF1_num],string);

								printf("%d %s\n",hashF1_num,array[hashF1_num]);								
						}						
				}
				else if(act_num == 2)
				{
						FILE *fp;
						char filename[100];
						char buf[100];
						//int num;
						int hashF2_num;
						int collision = 0;
						int data_num;
						float loadfactor,performance;

						scanf("%s",filename);
						
						fp = fopen(filename,"r");
					
						while(fgets(buf,100,fp) != NULL)
						{
								
								buf[strlen(buf)-1] = '\0';
							
								if(strcmp(buf,exit) == 0)
										break;

								//num = atoi(buf);

								hashF2_num = hashF2(buf);
								
								while(array_2[hashF2_num] != NULL)
								{
										collision ++;
										hashF2_num ++;
								}

								if(hashF2_num >=0 && hashF2_num <=4999)
								{
										array_2[hashF2_num] = (char *)malloc(sizeof(array_2[hashF2_num]));
										strcpy(array_2[hashF2_num],buf);
										//printf("%s\n",array_2[hashF2_num]);
										data_num ++;
								}
						}
						printf("%d\n",data_num);
						printf("%d\n",collision);

						loadfactor = data_num / HASHSIZE;
						performance = loadfactor / (collision + 1);

						printf("Performance = %.30f\n",performance);
				}
								
		}
		return 0;
}

int hashF1(char *string)
{
		int ascii = 0;
		int i;
		
		for(i=0;i<strlen(string);i++)
		{
				ascii = ascii + string[i];
				//printf("%d\n",ascii);
		}
		return ascii % 12;
}

int hashF2(char *s)
{
		int i,hv=0;

		for(i=0;i<strlen(s);i++)
				hv = (hv << 5) + s[i];
		if(hv < 0)
				hv = hv * (-1);
		return hv % HASHSIZE;
}









