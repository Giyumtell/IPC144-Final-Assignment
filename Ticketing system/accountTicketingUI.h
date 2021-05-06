/*
	==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   :Masoud Torkian
	Section:ZCC
*/
#ifndef ACCOUNT_TICKETING_UI_H_
#define ACCOUNT_TICKETING_UI_H_
#define _CRT_SECURE_NO_WARNINGS

struct AccountTicketingData
{
	struct Account* accounts; // array of accounts
	const int ACCOUNT_MAX_SIZE; // maximum elements for account array
	struct Ticket* tickets; // array of tickets
	const int TICKET_MAX_SIZE; // maximum elements for ticket array
};
#include <stdio.h>
#include "account.h"
#include "commonHelpers.h"
#include "ticket.h"

//This Block is responsible for displaying Ticket data for Agents
void displayTicketHeaderAgent(void);
void displayTicketFooterAgent(void);
void displayTicketDataAgent(const struct Ticket*);
//

//This Block is responsible for displaying Ticket data for Customers
void displayTicketHeaderCustomer(void);
void displayTicketFooterCustomer(void);
void displayTicketDataCustomer(const struct Ticket*);
//

//Recieves a single Ticket as argument and displays it's messages
void displayMessageByTicket(struct Ticket);

// Displays a header for Summary of the accounts
void displayAccountSummaryHeader(void);

// Displays a header for Detailed records of the accounts
void displayAccountDetailHeader(void);

// recieves an istnace of Account and Displays a summary of that account
void displayAccountSummaryRecord(const struct Account*);

// recieves an istnace of Account and Displays  Detailed records of that account 
void displayAccountDetailRecord(const struct Account*);

//Entry point to application logic and loop for menu
void applicationStartup(struct AccountTicketingData*);

//Displays a Login Menu and returns account number of the user
int  menuLogin(const struct Account accounts[], int);

//Displays a Login Menu for Agents with extra options
void menuAgent(struct AccountTicketingData*, const struct Account*);

//responsible for Display and functions of the menu for customers
void menuCustomer(const struct Account*, struct Ticket ticket[],int);

// search the array received in second argument for a match on a desired account number.
int  findAccountIndexByAcctNum(int, const struct Account accounts[], int, int);

//displays a summary view of all the valid account records (where the account number is greater than zero(0)
void displayAllAccountSummaryRecords(const struct Account accounts[], int);

//displays a detailed view of all the valid account records(where the account number is greater than zero(0)
void displayAllAccountDetailRecords(const struct Account accounts[], int); 

// Pause execution until user enters the enter key
void pauseExecution(void);


#endif // !ACCOUNT_TICKETING_UI_H_
