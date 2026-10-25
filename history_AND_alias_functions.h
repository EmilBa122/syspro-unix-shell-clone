#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define HISTORY_SIZE 6//20
char **myhistory;       //Points to a table with size = HISTORY_SIZE that every node is a pointer that 
                        //points in a string (the last commands the user gave)
#define MAXSIZE 10000   //I use this for the maxinum number of characters the user can give in one command
#define SIZE 8//100     


//Structure for alias use, aliases[i] is the new name of the command which match with commands[i] the real command
typedef struct aliases_struct{//We can have SIZE aliases
    char *aliases[SIZE];
    char *commands[SIZE];
}aliases_struct;

//myHistory functions
//Creation of myhistory, points to a table with size = HISTORY_SIZE that every node is a pointer that points in a string 
//(the last commands the user gave) 
char **create_myhistory();
int delete_myhistory(char **history);//Destruction of myhistroty
int print_myhistory(char **history);
int check_command_history(char *execution);//check_command_history checks if the user gave the command "history"
int noted(char *user_input, char **myhistory);//The main use of the function noted is to store the command the user gave
char *replace_history(char *user_input, char **myhistory);

//Alias functions
aliases_struct  *init_aliases();//Initialize the structure of aliases and return a pointer who point to this structure
int delete_aliases(aliases_struct *alias);//Destruction of structure aliases
int print_aliases(aliases_struct alias);
int alias_managment(char *user_input, aliases_struct *alias);//This function manages if the user gave createalias or destroyalias
char *alias_to_command(char *user_input, aliases_struct *alias);
int alias_exists(char *user_input, aliases_struct *alias);