// Copyright (c) 2019-20 Kritik Agarwal

#include<time.h>
#include<stdio.h>
#include<stdlib.h>
#include<string.h>

void show_record();
void reset_score();
void edit_score(float , char []);

int main()
{
	int countr=0,r,r1,count=0,i,n,score=0;
     	char choice,ch,answer;
     	char playername[20];
     	time_t t;
     	time(&t);
     	mainhome:
     	system("clear");
     	printf("\n\t\t________________________________________");
     	printf("\n\t\t\t		WELCOME ");
     	printf("\n\t\t\t		  TO ");
     	printf("\n\t\t\t	       QUIZ GAME ");
     	printf("\n\t\t________________________________________");
     	printf("\n\t\t--> Press S to start the game");
     	printf("\n\t\t--> Press V to view the highest score");
     	printf("\n\t\t--> Press R to reset score");
     	printf("\n\t\t--> Press Q to quit");
     	printf("\n\t\t________________________________________\n\n");
     	for(i=0;i<80;i++)
		printf("*");
     	printf("\nCurrent date and time : %s",ctime(&t));
     	for(i=0;i<80;i++)
		printf("*");
     	scanf("%c",&choice);
     	if(choice=='V')
	{
		show_record();
		goto mainhome;
	}
    	else if (choice=='R')
	{
		reset_score();
		goto mainhome;
	}
   	else if (choice=='Q')
		exit(1);
    	else if(choice=='S')
    	{
     		system("clear");
    		printf("\n\n\n\n\n\n\n\n\n\n\t\tEnter your name:");
    		scanf("%s",playername);
    		system("clear");
    		printf("\n ------------------  Welcome %s to C Program Quiz Game --------------------------",playername);
    		printf("\n\n Here are some tips you might wanna know before playing:");
    		printf("\n -------------------------------------------------------------------------");
    		printf("\n >> There are 2 rounds in this Quiz Game,WARMUP ROUND & CHALLENGE ROUND");
    		printf("\n >> In warmup round you will be asked total 3 questions to test your");
    		printf("\n    general knowledge. You are eligible to play the game if you give atleast 2");
    		printf("\n    right answers, otherwise you can't proceed further to the Challenge Round.");
    		printf("\n >> Your game starts with CHALLENGE ROUND. In this round you will be asked a");
    		printf("\n    total of 10 questions. Each right answer will be awarded 5 point");
    		printf("\n >> You will be given 4 options and you have to press A, B ,C or D for the");
    		printf("\n    right option.");
    		printf("\n >> You will be asked questions continuously, till right answers are given");
    		printf("\n >> No negative marking for wrong answers!");
    		printf("\n\n\t!!!!!!!!!!!!! ALL THE BEST !!!!!!!!!!!!!");
    		printf("\n\n\tPress Y  to start the game! (or) Press any other key to return to the main menu!");
    		scanf("%s",&ch);
    		if(ch=='Y')
	    		goto home;
    		else
		{
            		goto mainhome;
            		system("clear");
		}
     		home:
     		system("clear");
     		count=0;
     		for(i=1;i<=3;i++)
     		{
    			system("clear");
     			r1=i;
     			switch(r1)
			{
				case 1:
					printf("\n\nWhich is valid C expression?");
					printf("\n\nA) int my_num=100,000;\t\tB) int my_num=100000;\n\nC) int my num=1000;\t\tD) int $my_num=10000;");
					scanf("%s",&answer);
					if(answer=='B')
					{
			    			printf("\n\nCorrect!!!");
			    			count++; 
			    			system("clear");
						break;
					}
					else
					{
		           			printf("\n\nWrong!!! The correct answer is B.");          
		           			system("clear");
						break;
					}
        			case 2:
					printf("\n\n\nWhich among the following is NOT a logical or relational operator?");
					printf("\n\nA) !=\t\tB) ==\n\nC) ||\t\tD) =");
					scanf("%s",&answer);
					if(answer=='D')
					{
			    			printf("\n\nCorrect!!!");
			    			count++;
       			    			system("clear");   
			    			break;
					}
		       			else
		       			{
			    			printf("\n\nWrong!!! The correct answer is D.");		       
		            			system("clear");   
			    			break;
		       			}
        			case 3:
					printf("\n\n\nWhich animal laughs like human being?");
					printf("\n\nA.Polar Bear\t\tB.Hyena\n\nC.Donkey\t\tD.Chimpanzee");
					scanf("%s",&answer);
					if(answer=='B')
					{
						printf("\n\nCorrect!!!");
						count++;			
				 		system("clear");     
			    			break;
					}
					else
		        		{
						printf("\n\nWrong!!! The correct answer is B.Hyena");		       
	 				        system("clear");   
						break;
					}
	   			}
			}
			if(count>=2)
				goto test;
			else
			{
				system("clear");
				printf("\n\nSORRY YOU ARE NOT ELIGIBLE TO PLAY THIS GAME, BETTER LUCK NEXT TIME");
				goto mainhome;
			}
     			test:
     			system("clear");
     			printf("\n\n\t*** CONGRATULATION %s you are eligible to play the Game ***",playername);
     			printf("\n\n\n\n\t!Press any key to Start the Game!");
     			scanf("%s",&answer);
			goto game;
			game:
     			countr=0;
     			for(i=1;i<=10;i++)
     			{
				system("clear");
     				r=i;
     				switch(r)
				{
					case 1:
						printf("\n\nWhat is the National Game of England?");
						printf("\n\nA.Football\t\tB.Basketball\n\nC.Cricket\t\tD.Baseball");
						scanf("%s",&answer);
						if(answer=='C')
						{
							printf("\n\nCorrect!!!");
							countr++;
			 				system("clear");   
			    				break;
						}
						else
		       				{
							printf("\n\nWrong!!! The correct answer is C.Cricket");
		       					system("clear");   
			    				break;
						}
					case 2:
						printf("\n\n\nStudy of Earthquake is called............,");
						printf("\n\nA.Seismology\t\tB.Cosmology\n\nC.Orology\t\tD.Etimology");
						scanf("%s",&answer);
						if(answer=='A')
						{
							printf("\n\nCorrect!!!");
							countr++;
			 				system("clear");   
			    				break;
						}
						else
		       				{
							printf("\n\nWrong!!! The correct answer is A.Seismology");
		       					system("clear");   
			    				break;
		       				}
        				case 3:
						printf("\n\n\nAmong the top 10 highest peaks in the world, how many lie in Nepal? ");
						printf("\n\nA.6\t\tB.7\n\nC.8\t\tD.9");
						scanf("%s",&answer);
						if(answer=='C')
						{
							printf("\n\nCorrect!!!");
							countr++;
			 				system("clear");   
			    				break;
						}
						else
		       				{
							printf("\n\nWrong!!! The correct answer is C.8");
		       					system("clear");   
			    				break;
						}
        				case 4:
						printf("\n\n\nThe Laws of Electromagnetic Induction were given by?");
						printf("\n\nA.Faraday\t\tB.Tesla\n\nC.Maxwell\t\tD.Coulomb");
  						scanf("%s",&answer);
						if(answer=='A')
						{
							printf("\n\nCorrect!!!");
							countr++;
			 				system("clear");   
			    				break;
						}
						else
		       				{
                					printf("\n\nWrong!!! The correct answer is A.Faraday");
		       					system("clear");   
			    				break;
		       				}
        				case 5:
						printf("\n\n\nIn what unit is electric power measured?");
						printf("\n\nA.Coulomb\t\tB.Watt\n\nC.Power\t\tD.Units");
						scanf("%s",&answer);
						if(answer=='B')
						{
							printf("\n\nCorrect!!!");
							countr++; 
							system("clear");   
			    				break;
						}
						else
		       				{
		           				printf("\n\nWrong!!! The correct answer is B.Power");
		       					system("clear");   
			    				break;
		       				}
					case 6:
						printf("\n\n\nWhich element is found in Vitamin B12?");
						printf("\n\nA.Zinc\t\tB.Cobalt\n\nC.Calcium\t\tD.Iron");
						scanf("%s",&answer);
						if(answer=='B')
						{
							printf("\n\nCorrect!!!");
							countr++;
			 				system("clear");   
			    				break;
						}
						else
		       				{
							printf("\n\nWrong!!! The correct answer is B.Cobalt");
		       					system("clear");   
			    				break;
						}

        				case 7:
						printf("\n\n\nWhat is the National Name of Japan?");
						printf("\n\nA.Polska\t\tB.Hellas\n\nC.Drukyul\t\tD.Nippon");
						scanf("%s",&answer);
						if(answer=='D')
						{
							printf("\n\nCorrect!!!");
							countr++;
			 				system("clear");   
			    				break;
						}
						else
		       				{
							printf("\n\nWrong!!! The correct answer is D.Nippon");
		       					system("clear");   
			    				break;
						}
        				case 8:
						printf("\n\n\nHow many times a piece of paper can be folded at the most?");
						printf("\n\nA.6\t\tB.7\n\nC.8\t\tD.Depends on the size of paper");
						scanf("%s",&answer);
						if(answer=='B')
						{
							printf("\n\nCorrect!!!");countr++; 
							system("clear");   
			    				break;
						}
						else
		       				{
							printf("\n\nWrong!!! The correct answer is B.7");
		       					system("clear");   
			    				break;
						}
        				case 9:
						printf("\n\n\nWhat is the capital of Denmark?");
						printf("\n\nA.Copenhagen\t\tB.Helsinki\n\nC.Ajax\t\tD.Galatasaray");
						scanf("%s",&answer);
						if(answer=='A')
						{
							printf("\n\nCorrect!!!");
							countr++; 
			 				system("clear");     
			    				break;
						}
						else
		       				{
							printf("\n\nWrong!!! The correct answer is A.Copenhagen");
		       					system("clear");   
			    				break;
						}
        				case 10:
						printf("\n\n\nWhich is the longest River in the world?");
						printf("\n\nA.Nile\t\tB.Koshi\n\nC.Ganga\t\tD.Amazon");
						scanf("%s",&answer);
						if(answer=='A')
						{
							printf("\n\nCorrect!!!");countr++; 
							system("clear");   
			    				break;
						}
						else
		       				{
							printf("\n\nWrong!!! The correct answer is A.Nile"); 
							system("clear");     
			    				break;
						}
				}
			}
	}
	score:
    		system("clear");
		score=countr;
		printf("\n\n\t\t************************ GAME OVER *****************************");
		printf("\n\t You scored %d",score);
		goto mainhome;
}

void show_record()
{
	system("clear");
	char name[20];
	int scr;
	FILE *f;
	f=fopen("score.txt","r");
	fscanf(f,"%s %d",name,&scr);
	printf("\n\n\t\t*************************************************************");
	printf("\n\n\t\t %s has secured the Highest Score %d",name,scr);
	printf("\n\n\t\t*************************************************************");
	fclose(f);
}

void reset_score()
{
	system("clear");
    	int sc;
	char nm[20];
	FILE *f;
	f=fopen("score.txt","r+");
	fscanf(f,"%s %d",nm,&sc);
	sc=0;
	fprintf(f,"%s -- %d",nm,sc);
    	fclose(f);
}

void edit_score(float score, char plnm[20])
{
	system("clear");
	int sc;
	char nm[20];
	FILE *f;
	f=fopen("score.txt","r");
	fscanf(f,"%s %d",nm,&sc);
	if(score>=sc)
	{ 
		sc=score;
		fclose(f);
	    	f=fopen("score.txt","w");
	    	fprintf(f,"%s\t%d",plnm,sc);
	}
	fclose(f);
}
