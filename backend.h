#include <stdio.h>
struct bug
{
    int id; //generated automatically based on last bug id in the file
    char type[10]; //characterises the bug into Major, Minor or Cosmetic 
    char description[500]; //description inputed by the person filling bug
    char priority[10]; //order based on which bugs should be assigned. can be High, Medium or Low
    char status[30]; //current status of the bug wether it is Not yet assigned, Assigned, In process, Fixed or Delivered 
    char name[100]; // holds the name of the person who filed the bug 
    char assigned_to_name[100];// holds name of person manager assigns bug to
    char date_filed[10];//holds date filed on in dd/mm/yyyy format
    char time_filed[8];// stores time in the 24 hour format as hh:mm:ss
};
int new_bug(struct bug *s, FILE *fileptr); //filing a new bug with all necessary details
int update_bug(FILE *fileptr);// update a bugs status or assigns the bug  based on bug id's
int display_bug(FILE *fileptr); //displays all the stats of a particular bug based on bug id 
int search_bug(FILE *fileptr);// searches for and displays all bugs based on various criteria such as status, type snd filer name

