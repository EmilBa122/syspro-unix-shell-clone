#pragma once
#include "syspro_AND_pipes_functions.h"

//On what they do these functions check the redirection_functions.c I explain there with comments what the purpose they have 
char **command_redirection(char *str);
char **command_append(char *str);
int right_redirection_exist(char *str);
int left_redirection_exist(char *str);
int left_right_redirection_exist(char *str);
int append_exist(char *str);
int execution_right_redirection(char **commands);
int execution_left_redirection(char **commands);
int execution_left_right_redirection(char **commands);
int execution_append(char **commands);
int inside_redirections(char *command);