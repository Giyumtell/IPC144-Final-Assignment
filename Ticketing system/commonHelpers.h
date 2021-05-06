/*
	==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   :Masoud Torkian
	Section:ZCC
*/
#ifndef COMMON_HELPERS_H_
#define COMMON_HELPERS_H_

#define _CRT_SECURE_NO_WARNINGS
//Returns the current Year as an integer
int currentYear(void); 

void clearStanadardInputBuffer(void);

//Recieves an integer from input then returns it if there is no error or prompts until a correct input is entered
int getInteger(void); 

//Recieves an integer greater than 0 from input then returns it if there is no error or prompts until a correct input is entered
int getPositiveInteger(void);

//recieves 2 integers as a ranges and prompts user to enter an integer between those range and then returns it
int getIntFromRange(int, int); 

//Recieves a double from input then returns it if there is no error or prompts until a correct input is entered
double getDouble(void);

//Recieves a double greater than 0 from input then returns it if there is no error or prompts until a correct input is entered
double getPositiveDouble(void);

//recieves a series of character and prompts user to enter one of them as desired option
char getCharOption(const char option[]);

// recieves 2 integers as a range then prompts user to input a string thats has the lenght between the range
void getCString(char C[], int, int);

//recieves a string supposed to be a password and returns 0 if it meets the requirements otherwise returns 1
int ValidatePWD(char C[]);
#endif // !COMMON_HELPERS_H_
