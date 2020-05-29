#include <stdio.h>
#include <string.h>
#include "backend.h"
#include <stdlib.h>
/* we take a ptr to the struct so as to impact at the memory location and the file pointer to open it.
First we test if filepointer is NULL, if it's we exit the function and display a message.
If not, we proceed with finding the id based on the last id in the file.
If it's an empty file, id is 1.
Next we prompt user to input all necessary details and store them in a structure. 
We then write this stucture into the bug_tracker.txt file*/
int new_bug(struct bug *new, FILE *fileptr)
{
    //below code is used to test if fileptr is null, if null
    if(!fileptr)
    {
        printf("Error opening file \n");
        exit(0);
    }
    //structure used for iteration to extract last inputted id
    struct bug temp;
    //we take the pointer to the start of the file just to avoid discrepancies
    fseek(fileptr,0,SEEK_END);
    //below chunk of code is used to assign bug id. If file is empty, id is 1. Else id is 1+last id in file
    int last_id=0;
    if (ftell(fileptr)==0)
    {
        new->id=1;
    }
    else
    {
        /*we use a seperate file pointer to avoid discrepancies with respect to location.
        we iterate over the file using fread() so as to obtain the last bug id.
        The new id is that of the last id+1*/
        FILE *f=fopen("bug_tracker.txt","r+");
        while(fread(&temp,sizeof(struct bug),1,f))
        {
            last_id=temp.id;
        }
        new->id=(last_id+=1);
        fclose(f);
    }
    //print and fgets statements to collect and store respective data. flushing stdin to avoid any discrepancies in data input
    fflush(stdin);
    printf("enter the type of bug");
    fgets(new->type,10,stdin);
    fflush(stdin);
    printf("enter the description");
    fgets(new->description,500,stdin);
    fflush(stdin);
    printf("enter the priority of bug");
    fgets(new->priority,10,stdin);
    fflush(stdin);
    printf("enter the status of bug");
    fgets(new->status,30,stdin);
    fflush(stdin);
    printf("enter the name if filer");
    fgets(new->name,100,stdin);
    fflush(stdin);
    printf("enter the date as dd/mm/yyyy");
    fgets(new->date_filed,10,stdin);
    fflush(stdin);
    printf("enter the time as hh:mm:ss in 24-hr format");
    fgets(new->time_filed,8,stdin);
    fflush(stdin);
    //stores all details collected to bug_tracker.txt using fwrite()
    fwrite(new,sizeof(struct bug),1,fileptr);
    printf("Bug successfully added \n");
    fflush(stdin);
    return 0;  
}
/*update_bug takes the fileptr as input and performs updation functions on status and updating assigned_name 
if status is being changed to assigned. The user is prompted to input the bug id for the bug they want to update.*/
int update_bug(FILE *fileptr)
{
    //creates a temporary instance of structure bug from which to update
    struct bug temp;
    //below code is used to test if fileptr is null, if null
    if(!fileptr)
    {
        printf("Error opening file \n");
        exit(0);
    }
    int search_bug_id;
    printf("Enter bug id of bug to be updated \n");
    scanf("%d",&search_bug_id);
    fflush(stdin);
    /*fseek() is used to take the pointer to the start of the file to avoid any discrepancies.
    we then use a while loop to iterate over the records of the file. 
    When bug id is equal to inputted id, we print an updation menu.
    Updation menu prompts user on wether the want to change status or assign the bug*/
    fseek(fileptr, 0, SEEK_SET);
    while(fread(&temp,sizeof(struct bug),1,fileptr))
    {
        if(temp.id==search_bug_id)
        {
            int choice;
            printf("Updation menu \n Enter 1 to update status \n Enter 2 to assign the bug \n");
            scanf("%d",&choice);
            fflush(stdin);
            /*if user simply wants to update the status, it promts user for new status and changes the status appropriately.
            if user wants to assign the bug, it prompts user for the name of person bug is being assigned to and 
            automatically changes the status to assigned without user intervention*/
            switch(choice)
            {
                case 1: printf("Input the curent status \n");
                        fgets(temp.status,30,stdin);
                        fflush(stdin);
                        printf("Bug status successfully changed \n");
                    break;
                case 2: printf("Input the name of person being assigned \n");
                        fgets(temp.assigned_to_name,100,stdin);
                        fflush(stdin);
                        strcpy(temp.status,"Assigned \n");
                        printf("Bug successfully assigned \n");
                    break;
            }
        }
    }
    return 0;
}
/*The below function takes a fileptr as an argument and is used to display the details of a bug based on it's id.
The bug id to be searched for is inputted by the user. 
We iterate over all the records of a file, if it matches a record, all details of the file are displayed.*/
int display_bug( FILE *fileptr)
{
    struct bug temp;
    //below code is used to test if fileptr is null, if null
    if(!fileptr)
    {
        printf("Error opening file \n");
        exit(0);
    }
    int display_bug_id;
    printf("enter the id of the bug you want displayed \n");
    scanf("%d",&display_bug_id);
    fflush(stdin);
    fseek(fileptr, 0, SEEK_SET);
    //iterates over the file records and if bug id matches inputted bug id prints the details
    while(fread(&temp,sizeof(struct bug),1,fileptr))
    {
        if(temp.id==display_bug_id)
        {
            printf("the bug id id is %d \n",temp.id);
            printf("the type of bug is %s \n",temp.type);
            printf("the description of the bug is %s \n",temp.description);
            printf("the priority of the bug is %s \n",temp.priority);
            printf("the filers name is %s \n",temp.name);
            printf("the time filed is %s \n",temp.time_filed);
            printf("the date filed is %s \n",temp.date_filed);
            printf("the status of the bug is %s \n",temp.status);
            if(strcmp(temp.status,"Not yet assigned")==0)//if bug isn't assigned other details aren't filed
            {
                break;
            }   
            else //if Assigned,In process, fixed or delivered , displays the name of employee it's assigned to
            {
                printf("The bug is assigned to %s \n",temp.assigned_to_name);
            }
            
        }
    }
    fflush(stdin);
    return 0;           
}
/*search_bug takes the fileptr as input and prints all those bugs which match the search constraint. 
It can search based on the filer name, type and status of the bug. 
If condition is satisfied, It displays filer name, type, status and description*/
int search_bug(FILE *fileptr)
{
    //checks if filept is null, if yes then does the needful
    if(!fileptr)
    {
        printf("Error opening file \n");
        exit(0);
    }
    //creating a temp structure variable and choice option. Prints the menu and prompts user for choice
    struct  bug temp;
    int choice;
    printf("Search Menu \n For displaying all bugs with same Filed name, enter 1 \n");
    printf("For displaying all bugs with same type, enter 2 \n");
    printf("for displaying bugs with same status,enter 3 \n");
    scanf("%d",&choice);
    fseek(fileptr, 0, SEEK_SET);
    /*based on the choice of user executes the case.
    In case execution we create a dummy variable in order to store the users input in each case.
    If constraint is met, prints the details.
    We use strcmp() function to compare between the search constraint and value of the record*/
    switch(choice)
    {
        case 1: printf("enter the filers name \n");
                char search_filer_name[100];
                scanf("%s",search_filer_name);
                while (fread(&temp,sizeof(struct bug),1,fileptr))
                {
                    if(strcmp(search_filer_name,temp.name)==0)
                    {
                        printf("the temp is is %d \n",temp.id);
                        printf("the status of bug is %s \n",temp.status);
                        printf("the type of the bug is %s \n",temp.type);
                        printf("the description is %s \n",temp.description);
                        fflush(stdin);
                    }
                }
                fflush(stdin);
            break;
        case 2: printf("enter the type of bug \n");
                char search_type[10];
                scanf("%s",search_type);
                while (fread(&temp,sizeof(struct bug),1,fileptr))
                {
                    if(strcmp(search_type,temp.name)==0)
                    {
                        printf("the temp is is %d \n",temp.id);
                        printf("the name of filer is %s \n",temp.name);
                        printf("the status of bug is %s \n",temp.status);
                        printf("the description is %s \n",temp.description);
                        fflush(stdin);
                    }
                }
                fflush(stdin);
            break;
        case 3: printf("enter the status of bug \n");
                char search_status[30];
                scanf("%s",search_status);
                while (fread(&temp,sizeof(struct bug),1,fileptr))
                {
                    if(strcmp(search_status,temp.name)==0)
                    {
                        printf("the temp is is %d \n",temp.id);
                        printf("the name of filer is %s \n",temp.name);
                        printf("the type of bug is %s \n",temp.type);
                        printf("the description is %s \n",temp.description);
                        fflush(stdin);
                    }
                }
                fflush(stdin);
            break;
    }
    return 0;
}
