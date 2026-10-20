#include "syspro_AND_pipes_functions.h"

//This functions accepts a pointer to a string with one or more pipes, creates a char **args who point in a 
//char *table that every node points into a string which is the one part of characters the pipes separate  
//from the 'original' string (i.e *str)
char **command_pipes(char *str)
{
    char **args = malloc(sizeof(char *) * SIZE);
    const char s[] = "|";
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

int pipe_exist(char *str)
{
    for (int i = 0; str[i] != '\0'; i++)
    {
        if (str[i] == '|')
        {
            return 1;
        }
    }
    return 0;
}

//this functions execute the strings of every pointer of this table points
int exec_command(char **executions)
{
    //we check if the command is the "history"
    if ( check_command_history(executions[0]) )//for this function go to history_AND_alias_functions.c/.h
    {
        print_myhistory(myhistory);//for this function go to history_AND_alias_functions.c/.h
        return 0;
    }
    
    int counter = 0;
    for (int i = 0; executions[i]; i++)//to know how many parameters has this command
    {
        counter++;
    }
    // print_2pointer_array(executions);


    char* main_command = executions[0];
    char* argument_list[counter + 1];
    int i;
    for (i = 0; executions[i]; i++)
    {
        argument_list[i] = executions[i];
    }
    argument_list[i] = NULL;
    
    // printf("Before calling execvp()\n");
    
    int status_code = execvp(main_command, argument_list);

    if (status_code == -1) 
    {
        printf("%s: Command not found\n", main_command);
        exit(3);    
    }
}

//here we execute the command from the pointer of the table commands[i] according with the value of the position
int execution_command(char **commands, int position)
{
    if (commands[position + 1] == NULL)//we check if this command is the last to execute from the table
    {
        //we check if we have redirections in the string
        //if no we execute the followings lines
        if ( inside_redirections(commands[position]) == 0 )//about this function go to redirection_functions.c/.h
        {                           
            char **executions;
            //now we remove the inside spaces if they exist for this string
            executions = remove_inside_spaces(commands[position]);//about this function go basic_function.c/.h
            //the above function create a new table that every node point into a string and all of those strings
            //compose the string (*commands[position]) but without the inside spaces 
            //here we call the below functions to execute the strings which the pointers of the new table
            //point
            exec_command(executions);//for this function check above
            exit(3);
        }
    }
    //if this command is not the last one then we add another link on this chain this is achieved with the
    //use of another fork
    pid_t pid ;
    int fd[2];
    if (pipe(fd) == -1) { perror(" pipe "); exit(1); }//we create a pipe
    if ((pid = fork()) == -1) { perror(" fork "); exit(1); }

    if (pid != 0)//parent and writes
    {
        close(fd[READ]);
        dup2(fd[WRITE] ,1);
        close(fd[WRITE]); 

        //we check if we have redirections in the string
        //if no we execute the followings lines
        if ( inside_redirections(commands[position]) == 0)//about this function go to redirection_functions.c/.h
        {
            char **executions;
            //now we remove the inside spaces if they exist for this string
            executions = remove_inside_spaces(commands[position]);//about this function go basic_function.c/.h
            //the above function create a new table that every node point into a string and all of those strings
            //compose the string (*commands[position]) but without the inside spaces 
            //here we call the below functions to execute the strings which they are pointed by the pointers of 
            //the new table
            exec_command(executions);//for this function check above
            exit(3); 
        }    
    }
    else if(pid == 0)//child and reads
    {   
        close(fd[WRITE]);
        dup2(fd[READ] ,0);
        close(fd[READ]);
        //call the same function but this time with position + 1 i.e for execution of the next command in line
        //of this pointer table
        execution_command(commands, position + 1);
        exit(3); 
    }
}

//now we begin to create this chain of executed commands 
int execution_pipe(char **commands)
{
    pid_t pid ;
    if ((pid = fork()) == -1) { perror(" fork "); exit(1); }
    

    if (pid != 0)//the parent wait to finish the child
    {
        wait(NULL);
        sleep(1);

        //We free the table
        free_2pointer_array(commands);//for function free_2pointer_array() check basic_functions.c/.h
        return 0;
    }
    else if(pid == 0)//here is the child
    {     
        //go to function execution_command with the number of the current node we are to execute the 
        //command who points 
        execution_command(commands, 0);//for more info about this functions check above
    }
}

int cd_exist(char *str)
{
    const char s[] = " \0";
    char *token;
    char temp[MAXSIZE];
    strcpy(temp, str);
    token = strtok(temp, s);
    if (!strcmp(token, "cd"))
    {
        return 1;
    }
    return 0;
}

int execution_cd(char *str)
{
    char **executions;
    char msg[MAXSIZE];    
    executions = remove_inside_spaces(str);
    if (chdir(executions[1]) == -1)
    {
        printf("%s: No such file or directory\n", executions[1]);
        return -1;
    }
    printf("%s\n", getcwd(msg, MAXSIZE));  
    for ( int i = 0; executions[i]; i++)
    {
        free(executions[i]);
        executions[i] = NULL;
    }
    free(executions);
    executions = NULL;
    return 0;
}

//From here starts the chain for execute command
//Now the str point in a string that dont has beginning/ending spaces but we dont know for now if it has inside it
//The use of this function is to check if the command has pipes and redirection
//From most inmportant to less important is if we have first pipe/pipes (with or without redirection), second
//is to have first left and after that right redirection (or more with this scheme), third right redirection 
//(or more than one), fourth to have left redirection (or more than one) and last to have 
//nothing of all this e.g ls -lt
int execution_managment(char *str)//apo edw xekinaei h alusida ekteleshw entolwn ;h mias
{
    char **commands;
        
    if ( pipe_exist(str) )//if we have the symbol of pipe in the command
    {
        //we break the str in pieces (i.e substrings) according with the number of pipes we have in the string
        //to see the function command_pipes go above
        commands = command_pipes(str);//to see this function check above
        //now we have the commnads who points in a table that every node points in a string i.e the characters
        //which the pipes separate between them
       
        //we call the function execution_pipe() to execute every command the table points 
        execution_pipe(commands);//to see this function check above
    }
    else if ( left_right_redirection_exist(str))//with this if I achieve to execute first the pipes and after
    {                                           //the redirections if I have both of those                                            
        
        //inside this if we have the pattern something1 < something2 > something3
        
        // Every function that has to do with redirection go to redirection_functions.c/.h //

        //we break the str in pieces (i.e substrings) according to the redirections the user gave
        commands = command_redirection(str);
        // print_2pointer_array(commands);
        //and now we execute the command
        execution_left_right_redirection(commands);
    }
    else if ( right_redirection_exist(str) )//if we have something1 > something2
    {
        //we break the str in pieces (i.e substrings) according to the redirection the user gave
        commands = command_redirection(str);
        //and now we execute the command
        execution_right_redirection(commands);
    }
    else if ( left_redirection_exist(str) )//if we have something1 < something2
    {
        //we break the str in pieces (i.e substrings) according to the redirection the user gave
        commands = command_redirection(str);
        //and now we execute the command
        execution_left_redirection(commands);
    }
    else if ( append_exist(str))//if we have something1 >> something2
    {
        //we break the str in pieces (i.e substrings) according to the redirection the user gave
        commands = command_append(str);
        //and now we execute the command
        execution_append(commands);
    }
    else if ( cd_exist(str))//if the user gave the command cd something
    {
        execution_cd(str);//for this function check above
        return 0;
    }
    else//if the user gave only a command e.g ls -lt
    {
        //I call the function command_pipes() because Ι wanted to save code for this situation ,because the below
        //function will return the strings the pipe separate so if a command doesnt have pipe the function
        //will return the same string 
        commands = command_pipes(str);//to see this function check above
        //the same thought I use here i.e because we dont have pipe the table has only one node so the function
        //execution_pipe will execute only for the first node, with this trick and here I save some code
        execution_pipe(commands);//to see this function check above
    }
    return 0;
}
