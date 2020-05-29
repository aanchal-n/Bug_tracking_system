#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "backend.h"
int main()
{
    /*file is called in a+ because we either want to add entries, change existing entries or display entries.
    We print a welcome message and initialise a flag value. 
    If the user wants to terminate execution of programe and enters Y to exit, flag value gets incremented and while loop breaks*/
    FILE *fptr=fopen("bug_tracker.txt","a+");
    printf("Welcome to my bug tracking system \n");
    for (int dummy=0;dummy<=10;dummy++)
    {
        printf("~");
    }
    printf("\n");
    int flag=0;
    /*we create an instance new of structure bug to store all details inputted by user while filing the bug. 
    we then print the menu and based on the user's input we call specific functions present in server1.c*/
    while (flag==0)
    {
        struct bug new;
        printf("menu \n");
        int choice;
        printf("enter 1 to file a new bug \n");
        printf("enter 2 to update an existing bug based on id\n");
        printf("enter 3 to search for a bug\n");
        printf("enter 4 to print details of a bug based on bug id \n");
        scanf("%d",&choice);
        fflush(stdin);
        switch(choice)
        {
            case 1:new_bug(&new,fptr);
                break;
            case 2:update_bug(fptr);
                break;
            case 3:search_bug(fptr);
                break;
            case 4:display_bug(fptr);
                break;
            default: printf("wrong choice \n");
        }
        fflush(stdin);
        /*after executong the function we ask the user if they want to continue with another operation or terminate.
        if user wants to terminate, flag=1 and while loop terminates*/
        char terminate;
        printf("Do you want to exit? Y/N \n");
        scanf("%c",&terminate);
        if (terminate=='Y' || terminate=='y')
        {
            flag=1;
        }
        fflush(stdin);
    }
    fclose(fptr);
    return 0;
}