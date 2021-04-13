/*
	==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   :Masoud Torkian
	ID     :159042191
	Email  :mtorkian@myseneca.ca
	Section:ZCC
*/
#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <time.h>
#include "accountTicketingUI.h"

// Displays a header for Summary of the accounts
void displayAccountSummaryHeader(void)
{
	printf("Acct# Acct.Type Birth\n");
	printf("----- --------- -----\n");
}

// Displays a header for Detailed records of the accounts
void displayAccountDetailHeader(void)
{
	printf("Acct# Acct.Type Birth Income      Country    Disp.Name       Login      Password\n");
	printf("----- --------- ----- ----------- ---------- --------------- ---------- --------\n");
}

// recieves an istnace of Account and Displays a summary of that account
void displayAccountSummaryRecord(const struct Account* account)
{
	if (account->accountType == 'A' )
	{
		printf("%05d %-9s %5d\n", account->accountNum, "AGENT", account->demographic.Byear);

	}
	else if (account->accountType == 'C')
	{
		printf("%05d %-9s %5d\n", account->accountNum, "CUSTOMER", account->demographic.Byear);
	}
}

// recieves an istnace of Account and Displays a Detailed records of that account 
void displayAccountDetailRecord(const struct Account* account)
{
	if (account->accountType == 'A')
	{
		printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s ", account->accountNum, "AGENT", account->demographic.Byear, account->demographic.HHincome, account->demographic.country, account->userlogin.name, account->userlogin.userLogin);

	}
	else if(account->accountType == 'C')
	{
		printf("%05d %-9s %5d $%10.2lf %-10s %-15s %-10s ", account->accountNum, "CUSTOMER", account->demographic.Byear, account->demographic.HHincome, account->demographic.country, account->userlogin.name, account->userlogin.userLogin);
	}
	int i;
	for (i = 0; i < 8; i++)
	{
		if (i % 2 == 0)
		{
			putchar(account->userlogin.password[i]);
		}
		else
		{
			putchar('*');
		}
	}
	printf("\n");
}

// Pause execution until user presses the enter key
void pauseExecution(void)
{
	printf("<< ENTER key to Continue... >>");
	clearStanadardInputBuffer();
	putchar('\n');
}

//Entry point to application logic and loop for menu
void applicationStartup(struct AccountTicketingData* accounts )
{
	int user;
	char exoption;
	do
	{
		//calling login menu and deciding if it is customer or Agent
		user = menuLogin(accounts->accounts, accounts->ACCOUNT_MAX_SIZE);
		if (user != -1 && user != -2)
		{
			printf("\n");
			if (accounts->accounts[user].accountType == 'A')
			{
				menuAgent(accounts, &accounts->accounts[user]);
				printf("\n");
			}
			else
			{
				menuCustomer(&accounts->accounts[user], accounts->tickets,accounts->TICKET_MAX_SIZE);
			}
		}
		if (user == -1) //in case of selecting exit option the return value would be -1
		{
			printf("Are you sure you want to exit? ([Y]es|[N]o): ");
			exoption = getCharOption("yYnN");
			if (exoption == 'n' || exoption == 'N')
			{
				user = 0;
				printf("\n");
			}
		}
	} while (user != -1);
	printf("\n==============================================\n");
	printf("Account Ticketing System - Terminated\n");
	printf("==============================================\n");
}

//Displays a Login Menu and returns account number of the user
int  menuLogin(const struct Account accounts[], int length)
{
	int selection, index =-2;
	
		printf("==============================================\n");
		printf("Account Ticketing System - Login\n");
		printf("==============================================\n");
		printf("1) Login to the system\n0) Exit application\n");
		printf("----------------------------------------------\n");
		printf("\nSelection: ");
		selection = getIntFromRange(0, 1);
		printf("\n");
		if (selection == 1)//if user wishes to login
		{
			int i = 0, flag;
			do
			{
				flag = loginProcess(&index, accounts, length); //if login process is successful returns 1 and and index value would change to the index of loged in user
				i++;
				if (flag == 0) printf("INVALID user login/password combination! [attempts remaining:%d]\n\n", 3 - i);
			} while (i < 3 && flag == 0);
			if (flag == 0)
			{
				printf("ERROR:  Login failed!\n\n");
				clearStanadardInputBuffer();
				pauseExecution();
			}
		}
		else
		{
			index = -1;
		}

	return index;
}

//Displays a Login Menu for Agents with extra options
void menuAgent(struct AccountTicketingData* data, const struct Account* userAccount)
{
	int option, i;
	do
	{
		printf("AGENT: %s (%d)\n", userAccount->userlogin.name, userAccount->accountNum);
		printf("==============================================\n");
		printf("Account Ticketing System - Agent Menu\n");
		printf("==============================================\n");
		printf(" 1) Add a new account\n");
		printf(" 2) Modify an existing account\n");
		printf(" 3) Remove an account\n");
		printf(" 4) List accounts: summary view\n");
		printf(" 5) List accounts: detailed view\n");
		printf("----------------------------------------------\n");
		printf(" 6) List new tickets\n");
		printf(" 7) List active tickets\n");
		printf(" 8) List closed tickets\n");
		printf(" 9) Manage a ticket\n");
		printf("10) Archive closed tickets\n");
		printf("----------------------------------------------\n");
		printf("11) View archived account statistics\n");
		printf("12) View archived tickets statistics\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n");
		printf("\nSelection: ");
		option = getIntFromRange(0, 12);
		if (option == 1)//Add a new account
		{
			addNewAccount(data);
			pauseExecution();
		}
		//===================================================
		if (option == 2)//Modify an existing account
		{
			int index;
			printf("\n");
			index = findAccountIndexByAcctNum(0, data->accounts, data->ACCOUNT_MAX_SIZE, 1);//finds and returns the account index otherwise returns -1
			if (index == -1)
			{
				printf("Invalid Account#!\n");
			}
			else
			{
				updateAccount(&data->accounts[index]);//modify the account with the index that we found
			}
			printf("\n");
		}
		//===================================================
		if (option == 3)//Remove an account
		{
			removeAccount(data, userAccount);
			printf("\n");
			pauseExecution();
		}
		//===================================================
		if (option == 4)//List accounts: summary view
		{
			displayAllAccountSummaryRecords(data->accounts, data->ACCOUNT_MAX_SIZE);
			printf("\n");
			pauseExecution();
		}
		//===================================================
		if (option == 5)//List accounts: detailed view
		{
			displayAllAccountDetailRecords(data->accounts, data->ACCOUNT_MAX_SIZE);
			printf("\n");
			pauseExecution();
		}
		//===================================================
		if (option == 6)//List new tickets
		{
			listNewTickets(data);
		}
		//===================================================
		if (option == 7)//List active tickets
		{
			listActiveTickets(data);
		}
		//===================================================
		if (option == 8)//List closed tickets
		{
			listClosedTickets(data);
		}
		//===================================================
		if (option == 9)//Manage a ticket
		{
			int targetTicket, error = 1, ind;
			printf("\nEnter ticket number: ");
			targetTicket = getInteger();
			printf("\n");
			//This loop finds the index of our targeted ticket number,will have an error if not
			for (i = 0; i < data->TICKET_MAX_SIZE; i++)
			{
				if (data->tickets[i].ticketNum == targetTicket)
				{
					error = 0;
					ind = i;
					i = data->TICKET_MAX_SIZE;//forcing loop to end after finding the index (optimize)
				}
			}
			if (error == 1)
			{
				printf("ERROR: Invalid ticket number\n");
			}
			else
			{
				modifyTicket(&data->tickets[ind], *userAccount);//modifying the ticket we targeted
			}
		}
		//===================================================
		if (option == 10)//Archive closed tickets
		{
			archiveClosedTickets(data->tickets, data->TICKET_MAX_SIZE);
			clearStanadardInputBuffer();
			pauseExecution();
		}
		//===================================================
		if (option == 11)//View archived account statistics
		{
			printf("\n");
			archivedAccountStat();
			pauseExecution();
		}
		//===================================================
		if (option == 12)//View archived tickets statistics
		{
			printf("\n");
			archivedTicketsStat();
			pauseExecution();
		}
		//===================================================
		if (option == 0)//Log Out
		{
			printf("\nSaving session modifications...\n");
			printf("   %d account saved.\n", saveAccounts(data->accounts, data->ACCOUNT_MAX_SIZE));
			printf("   %d tickets saved.\n", saveTickets(data->tickets, data->TICKET_MAX_SIZE));
			printf("### LOGGED OUT ###\n");
		}
		//===================================================
	} while (option != 0);
}

//responsible for Display and functions of the menu for customers
void menuCustomer(const struct Account* userAccount, struct Ticket ticket[], int length)
{
	int option;
	do
	{
		printf("CUSTOMER: %s (%d)\n", userAccount->userlogin.name, userAccount->accountNum);
		printf("==============================================\n");
		printf("Customer Main Menu\n");
		printf("==============================================\n");
		printf("1) View your account detail\n");
		printf("2) Create a new ticket\n");
		printf("3) Modify an active ticket\n");
		printf("4) List my tickets\n");
		printf("----------------------------------------------\n");
		printf("0) Logout\n");
		printf("\nSelection: ");
		option = getIntFromRange(0, 4);
		switch (option)
		{
		case 1://View your account detail
			printf("\n");
			displayAccountDetailHeader();
			displayAccountDetailRecord(userAccount);
			printf("\n");
			pauseExecution();
			break;
		case 2://Create a new ticket
			printf("\n");
			createNewTicket(ticket, *userAccount, length);
			pauseExecution();
			break;
		case 3://Modify an active ticket
			modifyActiveTicket(userAccount, ticket, length);
			pauseExecution();
			break;
		case 4://List my tickets
			printf("\n");
			listCustomerTickets(userAccount, ticket, length);
			break;
		case 0://Logout
			printf("\nSaving session modifications...\n");
			printf("   %d tickets saved.\n", saveTickets(ticket,length));
			printf("### LOGGED OUT ###\n\n");
			break;
		default:
			break;
		}
	} while (option != 0);

}

// search the array received in argument 2 for a match on a desired account number.
int  findAccountIndexByAcctNum(int targetAccNum, const struct Account accounts[], int length, int indicator)
{
	int index = -1, target, i;
	if (indicator == 0)// 0 means the case where we have the target account number as an argument
	{
		for (i = 0; i < length; i++)//this loop searches accounts array for the index of our target acc#
		{
			if (accounts[i].accountNum == targetAccNum)
			{
				index = i;
			}
		}
	}
	if (indicator == 1)// 1 means the case where we have to prompt user for target account number
	{
		printf("Enter the account#: ");//prompt user for target
		target = getPositiveInteger();
		for (i = 0; i < length; i++)//this loop searches accounts array for the index of our target acc#
		{
			if (accounts[i].accountNum == target)
			{
				index = i;
			}
		}
	}
	return index;//if we couldn't find a match this would be -1
}

//displays a summary view of all the valid account records (where the account number is greater than zero(0)
void displayAllAccountSummaryRecords(const struct Account accounts[], int length)
{
	int i;
	printf("\n");
	displayAccountSummaryHeader();
	for ( i = 0; i < length; i++)
	{
		if (accounts[i].accountNum != 0)
		{
			displayAccountSummaryRecord(&accounts[i]);
		}
	}
}

//displays a detailed view of all the valid account records(where the account number is greater than zero(0)
void displayAllAccountDetailRecords(const struct Account accounts[], int length)
{
	int i;
	printf("\n");
	displayAccountDetailHeader();
	for (i = 0; i < length; i++)
	{
		if (accounts[i].accountNum != 0)
		{
			displayAccountDetailRecord(&accounts[i]);
		}
	}
}

void displayTicketHeaderAgent(void)
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
	printf("Ticket Acct# Display Name    Status Subject                        Messages\n");
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}
void displayTicketFooterAgent(void)
{
	printf("------ ----- --------------- ------ ------------------------------ --------\n");
}
void displayTicketDataAgent(const struct Ticket* ticket)
{
	if (ticket->ticketStatus == 1)
	{
		printf("%06d %5d %-15s ACTIVE %-30s %5d\n", ticket->ticketNum, ticket->accountNum, ticket->message[0].name, ticket->subjectL, ticket->MsgNum);
	}
	else
	{
		printf("%06d %5d %-15s CLOSED %-30s %5d\n", ticket->ticketNum, ticket->accountNum, ticket->message[0].name, ticket->subjectL, ticket->MsgNum);
	}
}

void displayTicketHeaderCustomer(void)
{
	printf("------ ------ ------------------------------ --------\n");
	printf("Ticket Status Subject                        Messages\n");
	printf("------ ------ ------------------------------ --------\n");
}
void displayTicketFooterCustomer(void)
{
	printf("------ ------ ------------------------------ --------\n");
}
void displayTicketDataCustomer(const struct Ticket* ticket)
{
	if (ticket->ticketStatus == 1)
	{
		printf("%06d ACTIVE %-30s %5d\n", ticket->ticketNum, ticket->subjectL, ticket->MsgNum);
	}
	else
	{
		printf("%06d CLOSED %-30s %5d\n", ticket->ticketNum, ticket->subjectL, ticket->MsgNum);
	}
}

//Recieves a single Ticket as argument and displays it's messages
void displayMessageByTicket(struct Ticket ticket)
{
	int i, j;
	if (ticket.ticketStatus == 1)//prints the correct header
	{
		printf("================================================================================\n");
		printf("%06d (ACTIVE) Re: %s\n",ticket.ticketNum,ticket.subjectL);
		printf("================================================================================\n");

	}
	else
	{
		printf("================================================================================\n");
		printf("%06d (CLOSED) Re: %s\n", ticket.ticketNum, ticket.subjectL);
		printf("================================================================================\n");
	}
	for (i = 0, j = 1; i < ticket.MsgNum; i++, j++)//in this loop we print messages depend on account types
	{
		if (ticket.message[i].accountType == 'C')
		{
			printf("CUSTOMER (%s):\n", ticket.message[i].name);
			printf("   %s\n\n", ticket.message[i].MsgDetails);
		}
		if (ticket.message[i].accountType == 'A')
		{
			printf("AGENT (%s):\n", ticket.message[i].name);
			printf("   %s\n\n", ticket.message[i].MsgDetails);
		}
		if (j%5==0 && i+1 != ticket.MsgNum)
		{
			pauseExecution();
		}
	}
}
