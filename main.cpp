/******************************************************************************

Welcome to GDB Online.
  GDB online is an online compiler and debugger tool for C, C++, Python, PHP, Ruby, 
  C#, OCaml, VB, Perl, Swift, Prolog, Javascript, Pascal, COBOL, HTML, CSS, JS
  Code, Compile, Run and Debug online from anywhere in world.

*******************************************************************************/
/*
Digital Assignment 1
Bus Ticket Reservation + Cancellation System

Name: Bathina Jahnavi
Registration Number: 25BCE5418
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct Ticket
{
    int ticketID;
    char name[50];
    int route;
    int seat;
};

int ticketCounter = 1000;

void showRoutes()
{
    printf("\nAvailable Bus Routes:\n");
    printf("1. Chennai -> Bangalore (Fare: 500)\n");
    printf("2. Chennai -> Hyderabad (Fare: 700)\n");
    printf("3. Chennai -> Coimbatore (Fare: 400)\n");
}

void bookTicket()
{
    struct Ticket t;
    FILE *fp;

    fp = fopen("tickets.txt", "a");

    printf("Enter passenger name: ");
    scanf("%s", t.name);

    showRoutes();

    printf("Select route (1-3): ");
    scanf("%d", &t.route);

    printf("Enter seat number (1-10): ");
    scanf("%d", &t.seat);

    t.ticketID = ticketCounter++;

    fprintf(fp,"%d %s %d %d\n",t.ticketID,t.name,t.route,t.seat);

    fclose(fp);

    printf("\nTicket Booked Successfully\n");
    printf("Ticket ID: %d\n",t.ticketID);
}

void displaySeats()
{
    int route;

    showRoutes();

    printf("Enter route number: ");
    scanf("%d",&route);

    printf("Seats available from 1 to 10\n");
}

void searchTicket()
{
    int id,found=0;
    struct Ticket t;

    FILE *fp = fopen("tickets.txt","r");

    printf("Enter Ticket ID: ");
    scanf("%d",&id);

    while(fscanf(fp,"%d %s %d %d",&t.ticketID,t.name,&t.route,&t.seat)!=EOF)
    {
        if(t.ticketID==id)
        {
            printf("\nTicket Found\n");
            printf("Name: %s\n",t.name);
            printf("Route: %d\n",t.route);
            printf("Seat: %d\n",t.seat);
            found=1;
        }
    }

    if(found==0)
    printf("Ticket not found\n");

    fclose(fp);
}

void cancelTicket()
{
    int id,found=0;
    struct Ticket t;

    FILE *fp = fopen("tickets.txt","r");
    FILE *temp = fopen("temp.txt","w");

    printf("Enter Ticket ID to cancel: ");
    scanf("%d",&id);

    while(fscanf(fp,"%d %s %d %d",&t.ticketID,t.name,&t.route,&t.seat)!=EOF)
    {
        if(t.ticketID==id)
        {
            found=1;
            printf("Ticket cancelled successfully\n");
        }
        else
        {
            fprintf(temp,"%d %s %d %d\n",t.ticketID,t.name,t.route,t.seat);
        }
    }

    fclose(fp);
    fclose(temp);

    remove("tickets.txt");
    rename("temp.txt","tickets.txt");

    if(found==0)
    printf("Ticket ID not found\n");
}

void report()
{
    struct Ticket t;
    int r1=0,r2=0,r3=0;

    FILE *fp=fopen("tickets.txt","r");

    while(fscanf(fp,"%d %s %d %d",&t.ticketID,t.name,&t.route,&t.seat)!=EOF)
    {
        if(t.route==1) r1++;
        if(t.route==2) r2++;
        if(t.route==3) r3++;
    }

    printf("\nDaily Collection Report\n");

    printf("Route1 Tickets: %d Revenue: %d\n",r1,r1*500);
    printf("Route2 Tickets: %d Revenue: %d\n",r2,r2*700);
    printf("Route3 Tickets: %d Revenue: %d\n",r3,r3*400);

    fclose(fp);
}

int main()
{
    int choice;

    while(1)
    {
        printf("\n----- Bus Reservation System -----\n");

        printf("1. Book Ticket\n");
        printf("2. Display Seats\n");
        printf("3. Search Ticket\n");
        printf("4. Cancel Ticket\n");
        printf("5. Daily Report\n");
        printf("6. Exit\n");

        printf("Enter choice: ");
        scanf("%d",&choice);

        switch(choice)
        {
            case 1: bookTicket(); break;
            case 2: displaySeats(); break;
            case 3: searchTicket(); break;
            case 4: cancelTicket(); break;
            case 5: report(); break;
            case 6: exit(0);
            default: printf("Invalid choice\n");
        }
    }
}

