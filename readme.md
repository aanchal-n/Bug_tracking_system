
This is a bug tracking software developed in C language. 
The bug tracking software can file a new bug, update either the status of the bug or assign the bug,
display bugs based on same filer name, same status or type and display any bugs based on the bug id.

Variable description
It classifies a bug based ob Bug_id, type, desciption, priority, status, name(filer),
assigned_to_name, date_filed, time_filed, date_solved and time_solved. 
The bug is intialized based on the bug id of the last record in the text file. 
The type of the bug is Cosmetic, Minor and Major in the same case of letters. 
Description is given by the filer and shouldn't be longer than 500 characters. 
Priority of the bug can be High, Medium and Low in the same case. 
Status of the bug can be Not yet assigned, Assigned, In process, Fixed and Delivered.
Name stores the name of the filer. 
assigned_to_name stores the name of person the bug is assigned to. 
date_filed and date_solved store dates in dd/mm/yyyy.

Execution
make -f makefile.mk
./a.out
This executes the program displaying the menu for operations and prompts user for choices.
It doesn't terminate after performing one operation. It prompts user on wether they want to continue with another 
operation and makes a decision based on users choice.

Challenges:
i) The fgets, fwrite and fread commands are often used for binary streams. I've assumed that this is the reason why any data which involves numbers has automatically been encoded into it's binary format. I reached out to my professor for guidance with respect to this issue. However when the records are being read to be displayed there is no error in displaying of records. 
