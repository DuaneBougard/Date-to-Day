/*
 * To change this license header, choose License Headers in Project Properties.
 * To change this template file, choose Tools | Templates
 * and open the template in the editor.
 */
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <string.h>
#include "DateToDay_Interface.h"

/*
the method below is to check whether the year was a leap year or not. We need to know this so that we can know
how much days february is suppose to have.		
*/
int isLeap(int year){
	/*
	we assume that it is not a leap year and so set leap to 0. if we proceed and find that it is a leap year, we
	then set leap to 1
	*/
	int leap=0;
	/*
	if the given year is divisible by 4, divisible by 100 and divisible by 400, then it is a leap year, we then set
	leap to 1. If the year is not divisible by all the above, it means that it is not a leap year and we leave leap
	as 0.
	*/
	if (year>1){
		if(year%4 == 0){
		if(year%100 ==0){
			if(year%400 == 0){
				leap=1;
			}

		}else{
				leap=1;
		}
	}
	}else{
		fprintf(stderr, "Input not valid");
	}

	return leap;
}

int errorCheck(int month, int day, int year){
	/*
	we assume that the date is valid and so set the error to 0 meaning that it's false. We then proceed to 
	check the date and once we find something wrong with the date we set the error to 1 meaning that there 
	is something wrong (true)
	*/
	int error=0;
	/*
	we first check whether the given year was a leap year or not. we do that by sending the year to the method
	isLeap(). We then proceed once we have found that it is not a leap year (isLeap() == 0)
	*/
	if (isLeap(year) == 0){
		/*
		below we check whether the month is a month that has 31 days
		*/
		if(month==13 || month==3 || month==5 || month==7 ||month==8 ||month==10 ||month==12 ){
			/*
			if it is a month that has 31 days then we check that the day does not exceed the amount of days
			that the month has. in this case 31.
			if days does exceed 31, then we have an error (true) and we set error to 1
			*/
			if (day > 31|| day < 1){
				error=1;
			}
		}
		/*
		below we check whether the month is a month that has 30 days
		*/
		if (month==4 || month==6 || month==9 || month==11 ){
			/*
			if it is a month that has 30 days then we check that the day does not exceed the amount of days
			that the month has. in this case 30.
			if days does exceed 30, then we have an error (true) and we set error to 1
			*/
			if (day > 30 || day < 1){
				error=1;
			}
		}
		/*
		if the month is february and it's not a leap year then it should have 28 days
		*/
		if (month==14){
			/*
			If the day exceeds 28 then we have an error and we set error to true, i.e. 1
			*/
			if (day > 28 || day < 1){
				error=1;
			}
		}

	}
	/*
	if it is a leap year , isLeap() != 0, we then proceed with the else. We check the months 
	having 30 and 31 days the same way as above. the only difference is if it is the month of
	february.
	*/
	else{
		if(month==13 || month==3 || month==5 || month==7 ||month==8 ||month==10 ||month==12 ){
		if (day > 31 || day < 1){
			   error=1;
					}
				}
		if (month==4 || month==6 || month==9 || month==11 ){
			if (day > 30 || day < 1){
				error=1;
					}
				}
		if (month==14){
			/*
			if the month is february then the days cannot exceed 29 (as it's a leap year). If the day
			does exceed 29, then it is invalid and there's an error so we set error to 1 (true)
			*/
			if (day > 29 || day < 1){
				error=1;
					}
				}

	}
	return error;
 }

/*
this is the final method that will print out the day depending on the number that it received
*/
int intToDay(int day){
	//printf("%d\n",day);
	if(day == 0){
		printf("Sat");
	}if(day == 1){
		printf("Sun");
	}if(day == 2){
		printf("Mon");
	}if(day==3){
		printf("Tue");
	}if(day ==4){
		printf("Wed");
	}if(day==5){
		printf("Thu");
	}if(day==6){
		printf("Fri");
	}
}

/*
the method below is the actual algorithm that determines the day. the algorithm is based on zellers congruence.
Zellerâ€™s congruence is an algorithm devised by Christian Zeller to calculate the day of the week for any date.
*/
int dayAlgorithm(int month, int day, int year){
	

	//below we compensate for jan and feb being 13 and 14
	if (month>12){
		year--;
	}
	//printf("%d\n",month);	

	int Day = day; 
	int Mo = month+1;
	int YrMod = year%100;
	int YrDiv = year/100;
	int calc1= (13*Mo);calc1=calc1/5;
	
	calc1=calc1+day;
	calc1=calc1+YrMod;
	calc1=calc1+(YrMod/4);
	calc1=calc1+(YrDiv/4);
	
	int DayInt=calc1+(5*YrDiv);
	
	DayInt = DayInt%7;
	
	/*
	we send DayInt to the method intToDay which then interprets the integer/number as the
	appropriate day
	*/
	intToDay(DayInt);
}


/*
each month is allocated a number. These numbers are based upon Zellers Congruence (in fact the algorithm is as well)
March starts at 3 with January and February being 13 and 14 respectively as a leap year would affect these two months
and they are therefore counted as part of the previous year.
*/
//enum months{Mar=3, Apr, May, Jun, Jul, Aug, Sep, Oct, Nov, Dec, Jan, Feb};

/*
a boolean is created with 0 being false and 1 being true. this is used to check whether there is an error in
the input or not
*/
typedef int Boolean;
Boolean error=0;

int main(int argc, char *argv[]){

	   int moNum=0;
		

	   /*Check whether the appropriate amount of inputs are given, being prac1, followed by the date*/
		if(argc !=4)
		{
			fprintf(stderr,"Input not valid");
			exit(0);
		}

		char* month=(argv[1]);

		if(strlen(month) != 3){
			fprintf(stderr, "Input not valid");
			exit(0);
		}
		
	  /*below we check that the year has 4 as its length and that the year has no letter in it. I.e. if the year
	  is less than 1800, we know that the year (in this case) contains no letters*/
		if(strlen(argv[3]) != 4){
			fprintf(stderr, "Input not valid");
			exit(0);
		}else{
			int yr=atoi(argv[3]);
			if(yr<1800){
				fprintf(stderr, "Input not valid");
				exit(0);
			}
		}


		/*below we check what month it is and also whether it is a valid month. we then assign
		the appropriate number to the month and print an error if it is invalid*/
		if(strcmp(month,"Mar")==0){
			moNum=3;
		}else if(strcmp(month,"Apr")==0){
			moNum=4;
		}else if(strcmp(month,"May")==0){
			moNum=5;
		}else if(strcmp(month,"Jun")==0){
			moNum=6;
		}else if(strcmp(month,"Jul")==0){
			moNum=7;
		}else if(strcmp(month,"Aug")==0){
			moNum=8;
		}else if(strcmp(month,"Sep")==0){
			moNum=9;
		}else if(strcmp(month,"Oct")==0){
			moNum=10;
		}else if(strcmp(month,"Nov")==0){
			moNum=11;
		}else if(strcmp(month,"Dec")==0){
			moNum=12;
		}else if(strcmp(month,"Jan")==0){
			moNum=13;
		}else if(strcmp(month,"Feb")==0){
			moNum=14;
		}else{
			fprintf(stderr, "Input not valid");
			exit(0);
		}


		/*
		we send the date to a function errorCheck that checks whether the date is valid, meaning that the day is valid.  			depending 
		on whether it's a leap year or not. the result is then stored in the boolean and depending on whther this error 		is true or 
		false, we then either print an error for invalid input or we proceed and calculate the day.
		*/
		error=errorCheck(moNum, atoi(argv[2]), atoi(argv[3]));// send month day year

		if (error==1){
		fprintf(stderr, "Input not valid");
		exit(0);
		}else{
		dayAlgorithm(moNum, atoi(argv[2]), atoi(argv[3]));
		}


}


