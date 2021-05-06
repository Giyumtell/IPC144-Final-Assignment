/*
	==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   :Masoud Torkian
	Section:ZCC
*/
#define _CRT_SECURE_NO_WARNINGS
#include "account.h"

// recieves an instance of Account and fills the account data
void getAccount(struct Account* account, int biggest)
{

	account->accountNum = biggest + 1;
	printf("New Account Data (Account#:%d)\n----------------------------------------\n",account->accountNum);
	printf("Enter the account type (A=Agent | C=Customer): ");
	account->accountType = getCharOption("AC");
	printf("\n");
}

// recieves an instance of Account and fills the userLogin data
void getUserLogin(struct UserLogin* userlogin)
{
	int i, error, spacectr;
	printf("User Login Data Input\n----------------------------------------\n");
	do
	{
		spacectr = 0;
		printf("Enter user login (10 chars max): ");
		getCString(userlogin->userLogin, 1, 10);
		for ( i = 0; userlogin->userLogin[i] != '\0'; i++)
		{
			if(isspace(userlogin->userLogin[i])) spacectr++;
		}
		error = (spacectr != 0);
	if (error) printf("ERROR:  The user login must NOT contain whitespace characters.\n");
	}while (error);
	printf("Enter the display name (30 chars max): ");
	getCString(userlogin->name, 1, 30);
	do
	{
		printf("Enter the password (must be 8 chars in length): ");
		getCString(userlogin->password, 8, 8);
	} while (ValidatePWD(userlogin->password));
	printf("\n");
}

// recieves an instance of Account and fills the demographic data
void getDemographic(struct Demographic* demographic)
{
	int i;
	printf("Demographic Data Input\n");
	printf("----------------------------------------\n");
	printf("Enter birth year (current age must be between 18 and 110): ");
	demographic->Byear = getIntFromRange(currentYear() - 110, currentYear() - 18);
	printf("Enter the household Income: $");
	demographic->HHincome = getPositiveDouble();
	printf("Enter the country (30 chars max.): ");
	getCString(demographic->country, 1, 30);
	printf("\n");
	for ( i = 0; demographic->country[i] != '\0' ; i++)
	{
		demographic->country[i] = toupper(demographic->country[i]);
	}
}

//Display's the update menu options for the account until the user wishes to exit
void updateAccount(struct Account* account)
{
	int option;
	printf("\n");
	do
	{
		printf("Account: %d - Update Options\n", account->accountNum);
		printf("----------------------------------------\n");
		printf("1) Update account type (current value: %c)\n", account->accountType);
		printf("2) Login\n");
		printf("3) Demographics\n");
		printf("0) Done\n");
		printf("Selection: ");
		option = getIntFromRange(0, 3);
		switch (option)
		{
		case 1://Update account type
			putchar('\n');
			printf("Enter the account type (A=Agent | C=Customer): ");
			account->accountType = getCharOption("AC");
			break;
		case 2://Login info
			updateUserLogin(&account->userlogin);
			break;
		case 3://Demographics info
			updateDemographic(&account->demographic);
			printf("\n");
			break;
		default:
			break;
		}
	} while (option != 0);
}

//Display's the update menu options for the user login until the user wishes to exit
void updateUserLogin(struct UserLogin* userlogin)
{
	int option;
	do
	{
		printf("\nUser Login: %s - Update Options\n",userlogin->userLogin);
		printf("----------------------------------------\n");
		printf("1) Display name (current value: %s)\n", userlogin->name);
		printf("2) Password\n");
		printf("0) Done\n");
		printf("Selection: ");
		option = getIntFromRange(0, 2);
		switch (option)
		{
		case 1://update Display name
			putchar('\n');
			printf("Enter the display name (30 chars max): ");
			getCString(userlogin->name, 1, 30);
			break;
		case 2://update password
			putchar('\n');
			do//prompts user for password until it meets the validation
			{
			printf("Enter the password (must be 8 chars in length): ");
			getCString(userlogin->password, 8, 8);
			} while (ValidatePWD(userlogin->password));
			break;
		default:
			break;
		}
	} while (option != 0);
	printf("\n");
}

//Display's a menu header title followed by 40 dashed characters on the next line,
void updateDemographic(struct Demographic* demographic)
{
	int option, i;
	do
	{
		printf("\nDemographic Update Options\n");
		printf("----------------------------------------\n");
		printf("1) Household Income (current value: $%.2lf)\n", demographic->HHincome);
		printf("2) Country (current value: %s)\n", demographic->country);
		printf("0) Done\n");
		printf("Selection: ");
		option = getIntFromRange(0, 2);
		switch (option)
		{
		case 1://update Household Income
			putchar('\n');
			printf("Enter the household Income: $");
			demographic->HHincome = getPositiveDouble();
			break;
		case 2://update country
			putchar('\n');
			printf("Enter the country (30 chars max.): ");
			getCString(demographic->country, 1, 30);
			for (i = 0; demographic->country[i] != '\0'; i++)
			{
				demographic->country[i] = toupper(demographic->country[i]);
			}
			break;
		default:
			break;
		}
	} while (option != 0);
}

//Initiates the login process including authentication.
int loginProcess(int* index, const struct Account accounts[], int length)
{
	int useraccountindex, i, identifiers = 0;
	char enteredPWD[31], enteredlogin[31];
	useraccountindex = findAccountIndexByAcctNum(0, accounts, length, 1);
	printf("User Login    : ");
	getCString(enteredlogin, 1, 30);
	printf("Password      : ");
	getCString(enteredPWD, 1, 30);
	if (useraccountindex != -1)//check if all entered values match the database
	{
		identifiers++;
		if (strcmp(accounts[useraccountindex].userlogin.userLogin, enteredlogin) == 0) identifiers++;
		if (strcmp(accounts[useraccountindex].userlogin.password, enteredPWD) == 0) identifiers++;
	}
	if (identifiers == 3)//if all three matched
	{
		*index = useraccountindex;
		i = 1;
	}
	else
	{
		i = 0;
	}
	return i;
}

//Removes an account but not the user's account
void removeAccount(struct AccountTicketingData* data, const struct Account* userAccount)
{
	int index, i;
	printf("\n");
	index = findAccountIndexByAcctNum(0, data->accounts, data->ACCOUNT_MAX_SIZE, 1);//finding the target account index
	if (index == -1)
	{
		printf("\nInvalid Account#!\n");
	}
	else if (data->accounts[index].accountNum == userAccount->accountNum)//making sure we are not deleting user's account
	{
		printf("\nERROR: You can't remove your own account!\n");
	}
	else
	{
		char deloption;
		displayAccountDetailHeader();
		displayAccountDetailRecord(&data->accounts[index]);
		printf("\nAre you sure you want to remove this record? ([Y]es|[N]o): ");//making sure of deletion
		deloption = getCharOption("YN");
		if (deloption == 'Y')
		{
			for (i = 0; i < data->TICKET_MAX_SIZE; i++)//finding all related tickets.
			{
				if (data->tickets[i].accountNum == data->accounts[index].accountNum && data->tickets[i].ticketStatus == 1)//deleting active tickets
				{
					data->tickets[i].ticketNum = 0;
					data->tickets[i].MsgNum = 0;
					data->tickets[i].accountNum = 0;
				}
				else if (data->tickets[i].accountNum == data->accounts[index].accountNum && data->tickets[i].ticketStatus == 0)//deleting and archiving Closed tickets
				{
					archiveTicket(data->tickets[i]);
					data->tickets[i].ticketNum = 0;
					data->tickets[i].MsgNum = 0;
					data->tickets[i].accountNum = 0;
				}
			}
			archiveAccount(data->accounts[index]);//archiving the targeted account data
			data->accounts[index].accountNum = 0;//deleting the targeted account data
			printf("\n*** Account Removed! ***\n");
		}
		else
		{
			printf("\n*** No changes made! ***\n");
		}
		clearStanadardInputBuffer();
	}
}

//this function loads Accounts from accounts.txt to our array
int loadAccounts(struct Account accounts[], int length)
{
	int i = 0;
	FILE* fp = NULL;
	fp = fopen("accounts.txt", "r");//openning file for read
	if (fp != NULL)
	{
		//loading each line to an account
		while (i < length && fscanf(fp, "%d~%c~%30[^~]~%30[^~]~%30[^~]~%d~%lf~%30[^\n]", &accounts[i].accountNum, &accounts[i].accountType, accounts[i].userlogin.name, accounts[i].userlogin.userLogin, accounts[i].userlogin.password, &accounts[i].demographic.Byear, &accounts[i].demographic.HHincome, accounts[i].demographic.country) == 8)
		{
			i++;//counting the number of loaded accounts
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
	return i;
}

//this function saves the current state of accounts into accounts.txt
int saveAccounts(struct Account accounts[], int length)
{
	int i = 0, counter = 0;
	FILE* fp = NULL;
	fp = fopen("accounts.txt", "w");//openning file for write
	if (fp !=NULL)
	{
		for (i = 0; i < length ; i++)//itterating through the array of accounts
		{
			if (accounts[i].accountNum != 0)//finding those that are not deleted
			{
				//saving each account in a line
				fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n", accounts[i].accountNum, accounts[i].accountType, accounts[i].userlogin.name, accounts[i].userlogin.userLogin, accounts[i].userlogin.password, accounts[i].demographic.Byear, accounts[i].demographic.HHincome, accounts[i].demographic.country);
				counter++;//counting number of accounts saved.
			}
		}
		fclose(fp);
	}
	else
	{
		printf("Failed to save accounts\n");
	}
	return counter;
}

//This function archives the account that recieves as an argument in accounts_arc.txt
void archiveAccount(struct Account account)
{
	FILE* fp = NULL;
	fp = fopen("accounts_arc.txt", "a");//open/create file for appending
	if (fp != NULL)
	{
		//appending recieved account to file in a line
		fprintf(fp, "%d~%c~%s~%s~%s~%d~%lf~%s\n", account.accountNum, account.accountType, account.userlogin.name, account.userlogin.userLogin, account.userlogin.password, account.demographic.Byear, account.demographic.HHincome, account.demographic.country);
		fclose(fp);
	}
	else
	{
		printf("Failed to archive the account\n");
	}
}

//This function displays the number of accounts archived in accounts_arc.txt
void archivedAccountStat()
{
	int i = 0;
	char c;
	FILE* fp = NULL;
	fp = fopen("accounts_arc.txt", "r");//opennig file for read
	if (fp != NULL)
	{
		for ( c = fgetc(fp); c != EOF; c = fgetc(fp))//counting the number of lines which represents one account each
		{
			if (c == '\n')
			{
				i++;
			}
		}
		fclose(fp);
	}
	printf("There are %d account(s) currently archived.\n\n", i);//displaying number of archived accounts
}

//This function is responsible for adding a new account
void addNewAccount(struct AccountTicketingData* data)
{
	int freeindex = -1, i, biggest = 0;
	for (i = 0; i < data->ACCOUNT_MAX_SIZE; i++)//this loop finds first empty splace in the account array
	{
		if (data->accounts[i].accountNum == 0)
		{
			freeindex = i;
			i = data->ACCOUNT_MAX_SIZE;
		}
	}
	for (i = 0; i < data->ACCOUNT_MAX_SIZE; i++)//this loop finds the biggest current Acc#
	{
		if (data->accounts[i].accountNum > biggest)
		{
			biggest = data->accounts[i].accountNum;
		}
	}
	if (freeindex == -1)//in case of no free spot
	{
		printf("\nERROR: Account listing is FULL, call ITS Support!\n\n");
	}
	else//in case of finding free spot
	{
		printf("\n");
		getAccount(&data->accounts[freeindex], biggest);
		getUserLogin(&data->accounts[freeindex].userlogin);
		getDemographic(&data->accounts[freeindex].demographic);
		printf("*** New account added! ***\n\n");
		clearStanadardInputBuffer();
	}
}
