/*
	==================================================
	Assignment #2 Milestone #4
	==================================================
	Name   :Masoud Torkian
	ID     :159042191
	Email  :mtorkian@myseneca.ca
	Section:ZCC
*/
#ifndef TICKET_H_
#define TICKET_H_
#define MAX_MESSAGES 20
struct Message
{
	char accountType;
	char name[31];
	char MsgDetails[151];
};
struct Ticket
{
	int ticketNum;
	int accountNum;
	int ticketStatus;
	char subjectL[31];
	int MsgNum;
	struct Message message[MAX_MESSAGES];
};
#include <stdio.h>
#include "account.h"
#include "commonHelpers.h"
//this function is responsible for creating new ticket
void createNewTicket(struct Ticket tickets[], struct Account, int);

//this function is responsible for modifying a ticket with 2 seperate menu for Agents or Customers!
void modifyTicket(struct Ticket*, struct Account);

//this function is responsible for displaying new tickets
void listNewTickets(struct AccountTicketingData*);

//this function is responsible for displaying active tickets
void listActiveTickets(struct AccountTicketingData*);

//this function is responsible for displaying closed tickets
void listClosedTickets(struct AccountTicketingData*);

//this function is responsible for displaying tickets related to a customer
void listCustomerTickets(const struct Account*, struct Ticket ticket[], int);

//this function is responsible for modifying only active tickets designed for customers
void modifyActiveTicket(const struct Account* , struct Ticket ticket[], int);

//this function loads tickets from tickets.txt to our array
int loadTickets(struct Ticket tickets[], int);

//this function saves the current state of tickets into tickets.txt
int saveTickets(struct Ticket tickets[], int);

//This function archives the ticket that recieves as an argument in tickets_arc.txt
void archiveTicket(struct Ticket);

//This function archives every Closed ticket to ticket_arc.txt and deletes them from main array and displays the number of them
void archiveClosedTickets(struct Ticket tickets[], int);

//This function displays the number of tickets archived in tickets_arc.txt
void archivedTicketsStat();
#endif // !TICKET_H_