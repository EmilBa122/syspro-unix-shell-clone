#pragma once
#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <unistd.h>         //fork, execvp and pipes
#include <sys/types.h>      //wait
#include <sys/wait.h>       //wait



#include "files_management.h"
#include "syspro_AND_pipes_functions.h"
#include "history_AND_alias_functions.h"


//On what they do these functions check the basic_functions.c I explain there with comments what the purpose they have 
int parsing_commandline(char *user_input, char **myhistory, aliases_struct *alias);
int free_2pointer_array(char **args);
int print_2pointer_array(char **args);
int only_spaces(char *str);
char **remove_spaces(char **args);
char **user_command(char *str);
char **remove_inside_spaces(char *str);


