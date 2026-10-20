#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <dirent.h>
#include "files_management.h"
#include "basic_functions.h"
#include "redirection_functions.h"

#define READ 0
#define WRITE 1

//On what they do these functions check the syspro_AND_pipes_functions.c I explain there with comments what the purpose they have 
char **command_pipes(char *str);
int execution_managment(char *commands);
int execution_command(char **commands, int position);
int exec_command(char **executions);
int pipe_exist(char *str);
