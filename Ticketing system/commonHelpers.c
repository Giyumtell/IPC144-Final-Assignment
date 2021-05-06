/*
	==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   :Masoud Torkian
	Section:ZCC
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include <string.h>
#include <ctype.h>
#include"commonHelpers.h"

//Returns the current Year as an integer
int currentYear(void)
{
	time_t currentTime = time(NULL);
	return localtime(&currentTime)->tm_year + 1900;
}

void clearStanadardInputBuffer(void)
{
	while (getchar() != '\n')
	{
		; // On purpose: do nothing
	}
}


//Recieves an integer from input then returns it if there is no error or prompts until a correct input is entered
int getInteger(void)
{
	int error1,intg;
	char c;
	do
	{
		scanf("%d", &intg);
		c = getchar();
		error1 = c != '\n';
		if (error1)
		{
			clearStanadardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
	} while (error1);
	return intg;
}

//Recieves an integer greater than 0 from input then returns it if there is no error or prompts until a correct input is entered
int getPositiveInteger(void)
{
	int error1, error2, intg;
	char c;
	do
	{
		scanf("%d", &intg);
		c = getchar();
		error1 = c != '\n';
		error2 = intg < 1;
		if (error1)
		{
			clearStanadardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
		else if (error2)
		{
			printf("ERROR: Value must be a positive integer greater than zero: ");
		}
	} while (error1 || error2);
	return intg;
}

//recieves 2 integers as a ranges and prompts user to enter an integer between those range and then returns it
int getIntFromRange(int low, int up)
{
	int error1, error2, intg;
	char c;
	do
	{
		scanf("%d", &intg);
		c = getchar();
		error1 = c != '\n';
		error2 = (intg < low || intg > up);
		if (error1)
		{
			clearStanadardInputBuffer();
			printf("ERROR: Value must be an integer: ");
		}
		else if (error2)
		{
			printf("ERROR: Value must be between %d and %d inclusive: ", low, up);
		}
	} while (error1 || error2);
	return intg;
}

//Recieves a double from input then returns it if there is no error or prompts until a correct input is entered
double getDouble(void)
{
	int error1;
	double doub;
	char c;
	do
	{
		scanf("%lf", &doub);
		c = getchar();
		error1 = c != '\n';
		if (error1)
		{
			clearStanadardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
	} while (error1);
	return doub;
}

//Recieves a double greater than 0 from input then returns it if there is no error or prompts until a correct input is entered
double getPositiveDouble(void)
{
	int error1, error2;
	double doub;
	char c;
	do
	{
		scanf("%lf", &doub);
		c = getchar();
		error1 = c != '\n';
		error2 = doub < 1;
		if (error1)
		{
			clearStanadardInputBuffer();
			printf("ERROR: Value must be a double floating-point number: ");
		}
		else if (error2)
		{
			printf("ERROR: Value must be a positive double floating-point number: ");
		}
	} while (error1 || error2);
	return doub;
}

//recieves a series of character and prompts user to enter one of them as desired option
char getCharOption(const char option[])
{
	char c[31];
	int error1 = 1, i;
	do
	{
		scanf(" %s", c);

		for (i = 0; option[i]!='\0'; i++)
		{
			if (option[i] == c[0])
			{
				error1 = 0;
			}
		}
		for (i = 0; c[i] != '\0'; i++);
		if (i > 1)
		{
			error1 = 1;
		}
		if (error1 == 1)
		{
			printf("ERROR: Character must be one of [%s]: ",option);
		}
	} while (error1);
	return c[0];
}

// recieves 2 integers as a range then prompts user to input a string thats has the lenght between the range
void getCString(char C[], int min, int max)
{
	int i, j, error1;
	char Cstr[151] = {0};
	do
	{
		scanf(" %150[^\n]", Cstr);
		i = strlen(Cstr);
		error1 = (i<min || i>max);
		if (error1 && min == max)
		{
			printf("ERROR: String length must be exactly %d chars: ", max);
		}else if (i < min)
		{
			printf("ERROR: String length must be between %d and %d chars: ", min, max);
		}else if (i > max)
		{
			printf("ERROR: String length must be no more than %d chars: ", max);
		}
	} while (error1);
	for ( j = 0; j <= i; j++)
	{
		C[j] = Cstr[j];
	}
}

//recieves a string supposed to be a password and returns 0 if it meets the requirements otherwise returns 1
int ValidatePWD(char C[])
{
	//several conditions that needs to be met
	int i, errordigit = 0, errorUpper = 0, errorLower = 0, errorsymbol = 0, digitflag = 0, upperflag = 0, lowerflag = 0, symbolflag = 0;
		//this loop searchs for any of the conditions and counts the repeatation
		for ( i = 0; C[i] != '\0'; i++)
		{
			if (islower(C[i])) lowerflag++;
			if (isupper(C[i])) upperflag++;
			if (isdigit(C[i])) digitflag++;
			if (C[i] == '!' || C[i] == '@' || C[i] == '#' || C[i] == '$' || C[i] == '%' || C[i] == '^' || C[i] == '&' || C[i] == '*') symbolflag++;
		}
		errordigit  = (digitflag < 2);
		errorLower  = (lowerflag < 2);
		errorUpper  = (upperflag < 2);
		errorsymbol = (symbolflag < 2);
		if (errordigit || errorsymbol || errorUpper || errorLower)
		{
			printf("SECURITY: Password must contain 2 of each:\n");
			printf("          Digit: 0-9\n");
			printf("          UPPERCASE character\n");
			printf("          lowercase character\n");
			printf("          symbol character: !@#$%%^&*\n");
		}
		if (errordigit || errorsymbol || errorUpper || errorLower)
		{ 
			i = 1;
		}else
		{
			i = 0;
		}
		return i;
}
