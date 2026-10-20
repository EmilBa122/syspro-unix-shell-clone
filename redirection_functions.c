#include "redirection_functions.h"

//This functions accepts a pointer to a string with one of the symbol > or < or both of them inside it, creates a char **args 
//who point in a char *table that every node points into a string which is the one part of characters these symbols separate  
//from the 'original' string (i.e *str)
char **command_redirection(char *str)
{
    char **args = malloc(sizeof(char *) * SIZE);
    const char s[] = "<>";
    char *token;
    int count = 0;
    /* get the first token */

    token = strtok(str, s);

    /* walk through other tokens */
    while( token )
    {  
        args[count] = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(args[count], token);
        count++;
        token = strtok(NULL, s);
    }
    args[count + 1] = NULL;//to know where it ends
    //to remove the beginning/ending space/spaces
    args = remove_spaces(args);//check basic_functions.c/.h for this function
    return args;
}

//this function does the same thing as above but this time for the symbol >>
char **command_append(char *str)
{
    char **args = malloc(sizeof(char *) * SIZE);
    const char s[] = ">>";
    char *token;
    int count = 0;
    /* get the first token */

    token = strtok(str, s);

    /* walk through other tokens */
    while( token )
    {  
        args[count] = malloc(sizeof(char) * (strlen(token) + 1));
        strcpy(args[count], token);
        count++;
        token = strtok(NULL, s);
    }
    args[count + 1] = NULL;//to know where it ends
    //to remove the beginning/ending space/spaces
    args = remove_spaces(args);//check basic_functions.c/.h for this function
    return args;
}

int right_redirection_exist(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if  (str[i] == '>')
        {
            if (str[i + 1] == '>')
            {
                return 0;
            }
            else
            {
                return 1;
            }
        }
    }
    return 0;
}

int left_redirection_exist(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if   ( str[i] == '<' )
        {
            return 1;
        }
    }
    return 0;
}

//we check if we have the pattern something1 < something2 > something3
int left_right_redirection_exist(char *str)
{
    return (left_redirection_exist(str) && right_redirection_exist(str));
}

//we check if we have the pattern something1 >> something2
int append_exist(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if ( (str[i] == '>') && (str[i+1] == '>'))
        {
            return 1;
        }
    }
    return 0;
}

//this function is called to execute the strings which they are pointed by the table commands[i]
//with the form something1 > something2
int execution_right_redirection(char **commands)
{
    pid_t pid ;
    char **executions;
    if ((pid = fork()) == -1) { perror(" fork "); exit(1); }
    
    if (pid != 0)
    {
        wait(NULL);

        //We free the table
        free_2pointer_array(commands);//for function free_2pointer_array() check basic_functions.c/.h
        return 0;
    }
    else if (pid == 0)
    {
        int fd = file_open1(commands[1]);//for how I open a file check files_managment.c/.h
        dup2(fd, 1);
        //now we remove the inside spaces if they exist for this string
        executions = remove_inside_spaces(commands[0]);//about this function go basic_function.c/.h   
        //the above function create a new table that every node point into a string and all of those strings
        //compose the string (*commands[0]) but without the inside spaces 
        //here we call the below functions to execute the strings which they are pointed by the pointers of the new table
        exec_command(executions);//for this function go syspro_AND_pipes_functions.c/.h
    }
}

//this function is called to execute the strings which they are pointed by the table commands[i]
//with the form something1 < something2
int execution_left_redirection(char **commands)
{
    pid_t pid ;
    char **executions;
    if ((pid = fork()) == -1) { perror(" fork "); exit(1); }
    
    if (pid != 0)
    {
        wait(NULL);
        
        //We free the table
        free_2pointer_array(commands);//for function free_2pointer_array() check basic_functions.c/.h
        return 0;    
    }
    else if (pid == 0)
    {
        int fd = file_open2(commands[1]);//for how I open a file check files_managment.c/.h
        dup2(fd, 0);
        //now we remove the inside spaces if they exist for this string
        executions = remove_inside_spaces(commands[0]);//about this function go basic_function.c/.h
        //the above function create a new table that every node point into a string and all of those strings
        //compose the string (*commands[0]) but without the inside spaces 
        //here we call the below functions to execute the strings which they are pointed by the pointers of the new table
        exec_command(executions);//for this function go syspro_AND_pipes_functions.c/.h
    }
}

//this function is called to execute the strings which they are pointed by the table commands[i]
//with the form something1 < something2 > something3
int  execution_left_right_redirection(char **commands)
{
    pid_t pid ;
    char **executions;
    if ((pid = fork()) == -1) { perror(" fork "); exit(1); }
    
    if (pid != 0)
    {
        wait(NULL);
        //We free the table
        free_2pointer_array(commands);//for function free_2pointer_array() check basic_functions.c/.h
        return 0;
    }
    else if (pid == 0)
    {
        int file1 = file_open2(commands[1]);//for how I open a file check files_managment.c/.h
        dup2(file1, 0);
        int file2 = file_open1(commands[2]);//for how I open a file check files_managment.c/.h
        dup2(file2, 1);
        //now we remove the inside spaces if they exist for this string
        executions = remove_inside_spaces(commands[0]);//about this function go basic_function.c/.h
        //the above function create a new table that every node point into a string and all of those strings
        //compose the string (*commands[0]) but without the inside spaces 
        //here we call the below functions to execute the strings which they are pointed by the pointers of the new table
        exec_command(executions);//for this function go syspro_AND_pipes_functions.c/.h
    }
}

//this function is called to execute the strings which they are pointed by the table commands[i]
//with the form something1 >> something2
int execution_append(char **commands)
{
    pid_t pid ;
    char **executions;
    if ((pid = fork()) == -1) { perror(" fork "); exit(1); }
    
    if (pid != 0)
    {
        wait(NULL);
        //We free the table
        free_2pointer_array(commands);//for function free_2pointer_array() check basic_functions.c/.h
        return 0;
    }
    else if (pid == 0)
    {
        int fd = file_open3(commands[1]);//for how I open a file check files_managment.c/.h
        dup2(fd, 1);
        //now we remove the inside spaces if they exist for this string
        executions = remove_inside_spaces(commands[0]);//about this function go basic_function.c/.h
        //the above function create a new table that every node point into a string and all of those strings
        //compose the string (*commands[0]) but without the inside spaces 
        //here we call the below functions to execute the strings which they are pointed by the pointers of the new table
        exec_command(executions);//for this function go syspro_AND_pipes_functions.c/.h
    }
}

//this function is called because maybe we have redirections in the string which is pointed by command
int inside_redirections(char *command)
{
    char **commands;
    //if we have the pattern something1 < something2 > something3
    if ( left_right_redirection_exist(command))
    {
        //we break the str in pieces (i.e substrings) according to the redirections the user gave
        commands = command_redirection(command);
        //and now we execute the command
        execution_left_right_redirection(commands);
    }
    else if ( right_redirection_exist(command) )//if we have something1 > something2
    {
        //we break the str in pieces (i.e substrings) according to the redirection the user gave
        commands = command_redirection(command);
        //and now we execute the command
        execution_right_redirection(commands);
    }
    else if ( left_redirection_exist(command) )//if we have something1 < something2
    {
        //we break the str in pieces (i.e substrings) according to the redirection the user gave
        commands = command_redirection(command);
        //and now we execute the command
        execution_left_redirection(commands);
    }
    else if ( append_exist(command) )//if we have something1 >> something2
    {
        //we break the str in pieces (i.e substrings) according to the redirection the user gave
        commands = command_append(command);
        //and now we execute the command
        execution_append(commands);
    }
    else//if in this string we dont have redirection
    {
        return 0;
    }
    return 1;//if in this string we have redirection
}
