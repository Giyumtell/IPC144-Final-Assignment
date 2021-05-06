/*
	==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   :Masoud Torkian
	Section:ZCC
*/
#define _CRT_SECURE_NO_WARNINGS
#include "ticket.h"

//this function is responsible for creating new ticket
void createNewTicket(struct Ticket tickets[], struct Account useraccount , int lenght)
{
	int freeindex = -1, biggest = 0, i;
	for (i = 0; i < lenght; i++)//this loop finds free index in tickets array
	{
		if (tickets[i].ticketNum == 0)
		{
			freeindex = i;
			i = lenght;//forcing loop to end after first free index we found and optimizing
		}
	}
	for (i = 0; i < lenght; i++)//finding the biggest ticket# so we can generate a new one for new ticket
	{
		if (tickets[i].ticketNum > biggest)
		{
			biggest = tickets[i].ticketNum;
		}
	}
	if (freeindex == -1)//if free index value doesnt change it means we found no empty spot in the array
	{
		printf("ERROR: Ticket listing is FULL, call ITS Support!\n");
		putchar('\n');
	}
	else//now that we found a empty spot and the new ticket number we populate it
	{
		tickets[freeindex].ticketNum = biggest + 1;
		tickets[freeindex].accountNum = useraccount.accountNum;
		tickets[freeindex].ticketStatus = 1;
		printf("New Ticket (Ticket#:%06d)", tickets[freeindex].ticketNum);
		printf("\n----------------------------------------\n");
		printf("Enter the ticket SUBJECT (30 chars. maximum): ");
		getCString(tickets[freeindex].subjectL, 1, 30);
		printf("\n");
		strcpy(tickets[freeindex].message[0].name, useraccount.userlogin.name);
		tickets[freeindex].message[0].accountType= useraccount.accountType;
		printf("Enter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
		getCString(tickets[freeindex].message[0].MsgDetails, 1, 150);
		tickets[freeindex].MsgNum++;
		printf("\n*** New ticket created! ***\n\n");
		clearStanadardInputBuffer();
	}
}

//this function is responsible for modifying a ticket with 2 seperate menu for Agents or Customers!
void modifyTicket(struct Ticket* ticket , struct Account useraccount)
{
	int option;
	char delop;
	do
	{
		if (useraccount.accountType == 'C')//if the user accessing this function is a Customer
		{
			printf("----------------------------------------\n");
			printf("Ticket %06d - Update Options\n", ticket->ticketNum);
			printf("----------------------------------------\n");
			printf("Status  : ACTIVE\n");
			printf("Subject : %s\n", ticket->subjectL);
			printf("----------------------------------------\n");
			printf("1) Modify the subject\n");
			printf("2) Add a message\n");
			printf("3) Close ticket\n");
			printf("0) Done\n");
			printf("Selection: ");
			option = getIntFromRange(0, 3);
			switch (option)
			{
			case 1://Modify the subject
				printf("\nEnter the revised ticket SUBJECT (30 chars. maximum): ");
				getCString(ticket->subjectL, 1, 30); //prompting for new subject
				printf("\n");
				break;
			case 2://Add a message
				if (ticket->MsgNum < MAX_MESSAGES)//chech if the tickets has empty spot for new message
				{
					//populating the new message
					strcpy(ticket->message[ticket->MsgNum].name, useraccount.userlogin.name);
					ticket->message[ticket->MsgNum].accountType = useraccount.accountType;
					printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
					getCString(ticket->message[ticket->MsgNum].MsgDetails, 1, 150);
					ticket->MsgNum++;
					printf("\n");
				}
				else
				{
					printf("\nERROR: Message limit has been reached, call ITS Support!\n\n");
				}
				break;
			case 3://Close ticket
				printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");
				delop = getCharOption("YN");
				if (delop == 'Y')//if user is sure on removing
				{
					if (ticket->MsgNum < 20)//if there is spot for a closing message
					{
						printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");//prompting for closing message
						delop = getCharOption("YN");
						if (delop == 'Y')
						{
							strcpy(ticket->message[ticket->MsgNum].name, useraccount.userlogin.name);
							ticket->message[ticket->MsgNum].accountType = useraccount.accountType;
							printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
							getCString(ticket->message[ticket->MsgNum].MsgDetails, 1, 150);
							ticket->MsgNum++;
							ticket->ticketStatus = 0;
							printf("\n*** Ticket closed! ***\n");
							option = 0;
						}
						else
						{
							ticket->ticketStatus = 0;
							option = 0;
							printf("\n*** Ticket closed! ***\n");
						}
					}
					else
					{
						ticket->ticketStatus = 0;
						option = 0;
						printf("\n*** Ticket closed! ***\n");
					}
				}
				clearStanadardInputBuffer();
				break;
			default:
				break;
			}
		}
		else if (useraccount.accountType == 'A')//if the user accessing this function is an Agent
		{
			printf("----------------------------------------\n");
			printf("Ticket %06d - Update Options\n", ticket->ticketNum);
			printf("----------------------------------------\n");
			if (ticket->ticketStatus == 1)
			{
				printf("Status  : ACTIVE\n");
			}
			else
			{
				printf("Status  : CLOSED\n");
			}
			printf("Subject : %s\n", ticket->subjectL);
			printf("Acct#   : %d\n", ticket->accountNum);
			printf("Customer: %s\n", ticket->message[0].name);
			printf("----------------------------------------\n");
			printf("1) Add a message\n");
			printf("2) Close ticket\n");
			printf("3) Re-open ticket\n");
			printf("0) Done\n");
			printf("Selection: ");
			option = getIntFromRange(0, 3);
			switch (option)
			{
			case 1://Add a message
				if (ticket->ticketStatus == 0)//check if the message is not closed
				{
					printf("\nERROR: Ticket is closed - new messages are not permitted.\n\n");
				}
				else
				{
					if (ticket->MsgNum < MAX_MESSAGES)//checking if there is spot for new message
					{
						strcpy(ticket->message[ticket->MsgNum].name, useraccount.userlogin.name);
						ticket->message[ticket->MsgNum].accountType = useraccount.accountType;
						printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
						getCString(ticket->message[ticket->MsgNum].MsgDetails, 1, 150);
						ticket->MsgNum++;
						printf("\n");
					}
					else
					{
						printf("\nERROR: Message limit has been reached, call ITS Support!\n\n");
					}
				}
				break;
			case 2://Close ticket
				if (ticket->ticketStatus == 0)//checking if ticket is already closed
				{
					printf("\nERROR: Ticket is already closed!\n\n");
				}
				else
				{
					printf("\nAre you sure you CLOSE this ticket? ([Y]es|[N]o): ");//making sure of closing the ticket
					delop = getCharOption("YN");
					if (delop == 'Y')
					{
						if (ticket->MsgNum < 20)//checking if there is empty space for a closing message
						{
							printf("\nDo you want to leave a closing message? ([Y]es|[N]o): ");
							delop = getCharOption("YN");
							if (delop == 'Y')//saving the closing message if user wants to
							{
								strcpy(ticket->message[ticket->MsgNum].name, useraccount.userlogin.name);
								ticket->message[ticket->MsgNum].accountType = useraccount.accountType;
								printf("\nEnter the ticket message details (150 chars. maximum). Press the ENTER key to submit:\n");
								getCString(ticket->message[ticket->MsgNum].MsgDetails, 1, 150);
								ticket->MsgNum++;
								ticket->ticketStatus = 0;
								printf("\n*** Ticket closed! ***\n\n");
							}
							else
							{
								ticket->ticketStatus = 0;
								printf("\n*** Ticket closed! ***\n\n");
							}
						}
						else
						{
							ticket->ticketStatus = 0;
							printf("\n*** Ticket closed! ***\n\n");
						}
					}
				break;
			case 3://Re-open ticket
				if (ticket->ticketStatus == 1)//checking if the ticket is already in active state
				{
					printf("\nERROR: Ticket is already active!\n\n");
				}
				else
				{
					printf("\nAre you sure you RE-OPEN this closed ticket? ([Y]es|[N]o): ");//making sure of reactivating the ticket
					delop = getCharOption("YN");
					if (delop == 'Y')
					{
						ticket->ticketStatus = 1;
						printf("\n*** Ticket re-opened! ***\n\n");
					}
					else
					{
						printf("\n");
					}
				clearStanadardInputBuffer();
				}
				break;
			case 0://Done
				printf("\n");
				break;
			default:
				break;
				}
			}
		}
	} while (option != 0);
}

//this function is responsible for displaying new tickets
void listNewTickets(struct AccountTicketingData* data)
{
	int TckNum = 0, resultTckNum[50], i, z = 0;
	printf("\n");
	do
	{
		displayTicketHeaderAgent();
		for (i = 0; i < data->TICKET_MAX_SIZE; i++)//this loop displays every ticket that is not deleted and has only one message
		{

			if (data->tickets[i].accountNum != 0 && data->tickets[i].ticketStatus == 1 && data->tickets[i].MsgNum == 1)
			{
				displayTicketDataAgent(&data->tickets[i]);
				resultTckNum[z] = data->tickets[i].ticketNum;//saving the result of our search to later choose from
				z++;
			}

		}
		if (z == 0)//if there is no new ticket
		{
			printf("There is no New Ticket\n");
			displayTicketFooterAgent();
			printf("\n");
			pauseExecution();
		}
		else
		{
			displayTicketFooterAgent();
		}
		if (z > 0)//if there are new tickets
		{
			printf("\nEnter the ticket number to view the messages or\n0 to return to previous menu: ");
			do
			{
				TckNum = getInteger();
				if (TckNum < 0)//checking the input
				{
					printf("ERROR: Value must be positive or zero: ");
				}
			} while (TckNum < 0);
			printf("\n");
			if (TckNum != 0)
			{
				int flag = 0;
				for (i = 0; i < z; i++)//cheking if the selected ticket is among the results
				{
					if (resultTckNum[i] == TckNum)
					{
						flag++;
						i = z;
					}
				}
				if (flag == 0)
				{
					printf("ERROR: Invalid ticket number - you may only access your own tickets.\n\n");
					pauseExecution();
				}
				else//displaying the messages if choice is correct
				{
					for (i = 0; i < data->TICKET_MAX_SIZE; i++)
					{
						if (data->tickets[i].ticketNum == TckNum)
						{
							displayMessageByTicket(data->tickets[i]);
						}
					}
					pauseExecution();
				}

			}
		}
	} while (TckNum != 0);
}

//this function is responsible for displaying active tickets
void listActiveTickets(struct AccountTicketingData* data)
{
	int TckNum = 0, resultTckNum[50], i, z = 0;
	printf("\n");
	do
	{
		displayTicketHeaderAgent();
		for (i = 0; i < data->TICKET_MAX_SIZE; i++)//finding every ticket that is not deleted and is an active status
		{
			if (data->tickets[i].accountNum != 0 && data->tickets[i].ticketStatus == 1)
			{
				displayTicketDataAgent(&data->tickets[i]);//displaying them
				resultTckNum[z] = data->tickets[i].ticketNum;//saving the result of search so we can choose from later
				z++;
			}
		}
		if (z == 0)//if there is no new ticket
		{
			printf("There is no Active Ticket\n");
			displayTicketFooterAgent();
			printf("\n");
			pauseExecution();
		}
		else
		{
			displayTicketFooterAgent();
		}
		if (z > 0)//if there are Active tickets
		{
			printf("\nEnter the ticket number to view the messages or\n0 to return to previous menu: ");
			do
			{
				TckNum = getInteger();
				if (TckNum < 0)//getting a correct input
				{
					printf("ERROR: Value must be positive or zero: ");
				}
			} while (TckNum < 0);
			printf("\n");
			if (TckNum != 0)
			{
				int flag = 0;
				for (i = 0; i < z; i++)//checking if it is chosen from the result
				{
					if (resultTckNum[i] == TckNum)
					{
						flag++;
						i = z;
					}
				}
				if (flag == 0)
				{
					printf("ERROR: Invalid ticket number - you may only access your own tickets.\n\n");
					pauseExecution();
				}
				else
				{//displaying the messages if everything is correct
					for (i = 0; i < data->TICKET_MAX_SIZE; i++)
					{
						if (data->tickets[i].ticketNum == TckNum)
						{
							displayMessageByTicket(data->tickets[i]);
						}
					}
					pauseExecution();
				}

			}
		}
	} while (TckNum != 0);
}

//this function is responsible for displaying closed tickets
void listClosedTickets(struct AccountTicketingData* data)
{
	int TckNum = 0, resultTckNum[50], i, z = 0;
	printf("\n");
	do//looping until recieving 0
	{
		displayTicketHeaderAgent();
		for (i = 0; i < data->TICKET_MAX_SIZE; i++)//finding tickets that are not deleted and are in Closed state
		{
			if (data->tickets[i].accountNum != 0 && data->tickets[i].ticketStatus == 0)
			{
				displayTicketDataAgent(&data->tickets[i]);//displaying them
				resultTckNum[z] = data->tickets[i].ticketNum;//saving our search result for later selection
				z++;
			}
		}
		if (z == 0)//if there is no Closed ticket
		{
			printf("There is no Closed Ticket\n");
			displayTicketFooterAgent();
			printf("\n");
			pauseExecution();
		}
		else
		{
			displayTicketFooterAgent();
		}
		if (z > 0)//if there are Closed tickets
		{
			printf("\nEnter the ticket number to view the messages or\n0 to return to previous menu: ");
			do
			{
				TckNum = getInteger();//prompting user to select a ticket
				if (TckNum < 0)
				{
					printf("ERROR: Value must be positive or zero: ");
				}
			} while (TckNum < 0);
			printf("\n");
			if (TckNum != 0)//if we have a ticket selected
			{
				int flag = 0;
				for (i = 0; i < z; i++)//loop searches results for a match
				{
					if (resultTckNum[i] == TckNum)
					{
						flag++;
						i = z;
					}
				}
				if (flag == 0)//if we dont find a match in search resluts
				{
					printf("ERROR: Invalid ticket number - you may only access your own tickets.\n\n");
				}
				else//displaying the messages if we find a match
				{
					for (i = 0; i < data->TICKET_MAX_SIZE; i++)
					{
						if (data->tickets[i].ticketNum == TckNum)
						{
							displayMessageByTicket(data->tickets[i]);
						}
					}
				}
				pauseExecution();
			}
		}
	} while (TckNum != 0);
}

//this function is responsible for displaying tickets related to the customer
void listCustomerTickets(const struct Account* userAccount, struct Ticket ticket[], int length)
{
	int i, TckNum = 0, resultTckNum[50], z = 0;
	do
	{
		displayTicketHeaderCustomer();
		for (i = 0; i < length; i++)//this loop finds tickets related to the customer and displays them
		{
			if (userAccount->accountNum == ticket[i].accountNum)
			{
				displayTicketDataCustomer(&ticket[i]);
				resultTckNum[z] = ticket[i].ticketNum;//saving the search result for later use
				z++;
			}
		}
		if (z == 0)//if the customer has no tickets
		{
			printf("There is no Ticket\n");
			displayTicketFooterCustomer();
			printf("\n");
			pauseExecution();
		}
		else
		{
			displayTicketFooterCustomer();
		}
		if (z > 0)//if the Customer has tickets
		{
			printf("\nEnter the ticket number to view the messages or\n0 to return to previous menu: ");
			do//prompts user to choose a ticket
			{
				TckNum = getInteger();
				if (TckNum < 0)
				{
					printf("ERROR: Value must be positive or zero: ");
				}
			} while (TckNum < 0);
			printf("\n");
			if (TckNum != 0)//check if customer chose a ticket or not
			{
				int flag = 0;
				for (i = 0; i < z; i++)//checking if the chosen number has a match in results
				{
					if (resultTckNum[i] == TckNum)
					{
						flag++;
						i = z;
					}
				}
				if (flag == 0)//if no match were found
				{
					printf("ERROR: Invalid ticket number - you may only access your own tickets.\n\n");
					pauseExecution();
				}
				else//if we find a match, displays the messages
				{
					for (i = 0; i < length; i++)
					{
						if (ticket[i].ticketNum == TckNum)
						{
							displayMessageByTicket(ticket[i]);
						}
					}
					pauseExecution();
				}

			}
		}
	} while (TckNum != 0);
}

//this function is responsible for modifying only active tickets designed for customers
void modifyActiveTicket(const struct Account* userAccount, struct Ticket ticket[], int length)
{
	int resultTckNum[50], z = 0, i, targetTicket, error1 = 1, error2 = 0;;
	printf("\nEnter ticket number: ");
	targetTicket = getInteger();
	printf("\n");
	for (i = 0; i < length; i++)//this loop finds tickets related to the customer
	{
		if (ticket[i].accountNum == userAccount->accountNum)
		{
			resultTckNum[z] = ticket[i].ticketNum;
			z++;
		}
	}
	for (i = 0; i < z; i++)//this loop tries to confirm if the chosen ticket has a match in result
	{
		if (resultTckNum[i] == targetTicket)
		{
			error1 = 0;
			i = z;
		}
	}
	for (i = 0; i < length; i++)//this loop finds the index of the targeted ticket in the array
	{
		if (ticket[i].ticketNum == targetTicket)
		{
			z = i;
			i = length;
		}
	}
	error2 = (ticket[z].ticketStatus == 0);//check if the ticket is closed
	if (error1)
	{
		printf("ERROR: Invalid ticket number - you may only modify your own ticket.\n\n");
	}
	else if (error2)
	{
		printf("ERROR: Ticket is closed - changes are not permitted.\n\n");
	}
	else//if there is no error we modify the ticket
	{
		modifyTicket(&ticket[z], *userAccount);
		printf("\n");
	}
}

//this function loads tickets from tickets.txt to our array
int loadTickets(struct Ticket tickets[], int length)
{
	int i = 0, j;
	FILE* fp = NULL;
	fp = fopen("tickets.txt", "r");//opennig file for read
	if (fp != NULL)
	{
		while (i < length && fscanf(fp, "%d|%d|%d|%30[^|]|%d|", &tickets[i].ticketNum, &tickets[i].accountNum, &tickets[i].ticketStatus, tickets[i].subjectL, &tickets[i].MsgNum) == 5)
		{	//this loop populates the ticket array until message member
			for ( j = 0; j < tickets[i].MsgNum; j++)//this loop records the messages from file tht are related to our current ticket
			{
				fscanf(fp, "%c|%30[^|]|%150[^|]|", &tickets[i].message[j].accountType, tickets[i].message[j].name, tickets[i].message[j].MsgDetails);
			}
			fscanf(fp, "\n");
			i++;

		}
		fclose(fp);
	}
	else
	{
		printf("Failed to open file\n");
	}
	return i;
}

//this function saves the current state of tickets into tickets.txt
int saveTickets(struct Ticket tickets[], int length)
{
	int i = 0, j, counter = 0;
	FILE* fp = NULL;
	fp = fopen("tickets.txt", "w");// opennig file for writing
	if (fp != NULL)
	{
		while (i < length)
		{//this loop saves tickets to file 
			if (tickets[i].accountNum != 0)//check if the ticket is not deleted/empty
			{
				//saving until message member
				fprintf(fp, "%d|%d|%d|%s|%d|", tickets[i].ticketNum, tickets[i].accountNum, tickets[i].ticketStatus, tickets[i].subjectL, tickets[i].MsgNum);
				for (j = 0; j < tickets[i].MsgNum; j++)//this loop saves the messages
				{
					fprintf(fp, "%c|%s|%s|", tickets[i].message[j].accountType, tickets[i].message[j].name, tickets[i].message[j].MsgDetails);
				}
				fprintf(fp, "\n");
				counter++;
			}
			i++;

		}
		fclose(fp);
	}
	else
	{
		printf("Failed to save tickets\n");
	}
	return counter;
}

//This function archives the ticket that recieves as an argument in tickets_arc.txt
void archiveTicket(struct Ticket ticket)
{
	int i = 0;
	FILE* fp = NULL;
	fp = fopen("tickets_arc.txt", "a");//open/creates file for appending
	if (fp != NULL)
	{
		fprintf(fp, "%d|%d|%d|%s|%d|", ticket.ticketNum, ticket.accountNum, ticket.ticketStatus, ticket.subjectL, ticket.MsgNum);//appends ticket data to file untill message member
		for (i = 0; i < ticket.MsgNum; i++)//this loop appends message data to file
		{
			fprintf(fp, "%c|%s|%s|", ticket.message[i].accountType, ticket.message[i].name, ticket.message[i].MsgDetails);
		}
		fprintf(fp, "\n");
		fclose(fp);
	}
	else
	{
		printf("Failed to archive the ticket\n");
	}
}

//This function archives every Closed ticket to ticket_arc.txt and deletes them from main array and displays the number of them
void archiveClosedTickets(struct Ticket tickets[], int length)
{
	int i, j = 0;
	char o;
	printf("\nAre you sure? This action cannot be reversed. ([Y]es|[N]o): ");
	o = getCharOption("YN");
	if (o == 'Y')
	{
		for (i = 0; i < length; i++)//this loop finds every closed ticket that is not already deleted and archives them
		{
			if (tickets[i].ticketStatus == 0 && tickets[i].accountNum != 0)
			{
				archiveTicket(tickets[i]);
				tickets[i].ticketNum = 0;
				tickets[i].MsgNum = 0;
				tickets[i].accountNum = 0;
				j++;
			}
		}
		printf("\n*** %d tickets archived ***\n\n", j);
	}
	else
	{
		printf("\n");
	}
}

//This function displays the number of tickets archived in tickets_arc.txt
void archivedTicketsStat()
{
	int i = 0, j = 0, dumpi;
	char c,dump[151];
	FILE* fp = NULL;
	fp = fopen("tickets_arc.txt", "r");
	if (fp != NULL)
	{
		while (fscanf(fp, "%d|%d|%d|%30[^|]|%d|", &dumpi, &dumpi, &dumpi, dump, &dumpi) == 5)//finding number of messages in each line
		{
			j += dumpi;//summing the number of messages in archive
			for (c = fgetc(fp); c != '\n'; c = fgetc(fp));//finding new line which represents a ticket
			i++;//counting for each new line
		}
		fclose(fp);
	}
	printf("There are %d ticket(s) and a total of %d message(s) archived.\n\n", i, j);
	
}
