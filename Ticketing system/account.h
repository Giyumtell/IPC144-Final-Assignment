/*==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   :Masoud Torkian
	Section:ZCC
*/
#ifndef ACCOUNT_H_
#define ACCOUNT_H_
#define _CRT_SECURE_NO_WARNINGS
struct Demographic
{
	int Byear;
	double HHincome;
	char country[31];
};
struct UserLogin
{
	char name[31];
	char userLogin[11];
	char password[9];
};
struct Account
{
	int accountNum;
	char accountType;
	struct UserLogin userlogin;
	struct Demographic demographic;
};

#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <string.h>
#include "commonHelpers.h"
#include "accountTicketingUI.h"

// recieves an instance of Account and fills the account data
void getAccount(struct Account*, int );

// recieves an instance of Account and fills the userLogin data
void getUserLogin(struct UserLogin* );

// recieves an instance of Accountand fills the demographic data
void getDemographic(struct Demographic* ); 

//Display's the update menu options for the account until the user wishes to exit
void updateAccount(struct Account*  );

//Display's the update menu options for the user login until the user wishes to exit
void updateUserLogin(struct UserLogin* );

//Display's a menu header title followed by 40 dashed characters on the next line,
void updateDemographic(struct Demographic* );

//Initiates the login process including authentication.
int  loginProcess(int*, const struct Account accounts[], int);

//Removes an account but not the user's account
void removeAccount(struct AccountTicketingData*, const struct Account*);

//this function loads Accounts from accounts.txt to our array
int loadAccounts(struct Account accounts[], int);

//this function saves the current state of accounts into accounts.txt
int saveAccounts(struct Account accounts[], int);

//This function archives the account that recieves as an argument in accounts_arc.txt
void archiveAccount(struct Account);

//This function displays the number of accounts archived in accounts_arc.txt
void archivedAccountStat();

//This function is responsible for adding a new account
void addNewAccount(struct AccountTicketingData* );
#endif // !ACCOUNT_H_
