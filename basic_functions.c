#include "basic_functions.h"

 
int free_2pointer_array(char **args)
{
    // printf("you call free\n");
    int i = 0;
    while ( args[i] )//Because in the initialization we make the last node of the table to point in NULL
    {
        free(args[i]);
        args[i] = NULL;
        i++;
    }
    free(args);
    args = NULL;
    return 0;
}

int print_2pointer_array(char **args)
{
    printf("=============================================================\n");
    printf("you call your printf\n");
    int i = 0;
    while ( args[i] )
    {
        printf("string %d is --%s--\n", i,args[i]);
        i++;
    }
    printf("=============================================================\n");
    return 0;
}

int only_spaces(char *str)
{
    int i = 0;
    while (str[i] == ' ')
    {
        i++;
    }
    return (str[i] == 0);
    
}

//remove_spaces() deletes the spaces if they exist at the beginning and at the ending of a substring 
//but NO the spaces if they exist inside in the substring
char **remove_spaces(char **args)
{
    char *token;
    char **new_args = malloc(sizeof(char *) * SIZE);
    int i;
    for (i = 0; args[i]; i++)//For every substring
    {
        if (only_spaces(args[i])) continue;
        if  (args[i][0] == ' ')//if the substring begins with space/spaces
        {
            int jj;
            for( jj = 0; (args[i][jj] == ' '); jj++);//'deletes' the beginning spaces if they exist for every args[i]
            token = (args[i] + jj);//The token now points after the beginning spaces 
            int size = strlen(token);
            for(int j = size - 1; token[j] == ' '; j--)//'deletes' the ending spaces if they exist for every args[i]
            {                                          
                token[j] = 0;
            }
            new_args[i] = malloc(sizeof(char) * (strlen(token) + 1));
            strcpy(new_args[i], token);
        }
        else//if we dont have beginning spaces
        {
            if (args[i][strlen(args[i]) - 1] == ' ')//if we have ending space/spaces
            {
                int size = strlen(args[i]);
                for(int j = size - 1; args[i][j] == ' '; j--)//'deletes' the ending spaces if they exist for every args[i]
                {
                    args[i][j] = 0;
                }
                new_args[i] = malloc(sizeof(char) * (strlen(args[i]) + 1));
                strcpy(new_args[i], args[i]);
            }
            else//if we dont have beginning and ending spaces in this substring
            {
                new_args[i] = malloc(sizeof(char) * (strlen(args[i]) + 1));
                strcpy(new_args[i], args[i]);
            }
        }
    }
    new_args[i] = NULL;//To know where ends the table
    free_2pointer_array(args);//We free the old table, check above for function free_2pointer_array()
    return new_args;//And we return the new one

}

//We use this function to create substrings (char **args) from the 'original' string that has semicolons 
char **user_command(char *str)
{
    char **args = malloc(sizeof(char *) * SIZE);
    const char s[] = ";\n";
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
    args[count + 1] = NULL;//To know where it ends
    
    //remove_spaces() deletes the spaces if they exist at the beginning and at the ending of a substring 
    //but NO the spaces if they exist inside in the substring
    //For more info about remove_spaces() check above
    args = remove_spaces(args);
    return args;
}


char **remove_inside_spaces(char *str)
{
    char **args = malloc(sizeof(char *) * SIZE);
    const char s[] = " \n";
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
    args[count + 1] = NULL;
    return args;
}

//Function for parshing, it receive the string from the user and breaks it
int parsing_commandline(char *user_input, char **myhistory, aliases_struct *alias)
{ 
    char **args;
    //In function replase_history() we check if we have for example !20 and if yes the user_input points now
    //to this old command the history table has
    user_input = replace_history(user_input, myhistory);//for this function check history_AND_alias_functions.c/.h
     
    //Here I check if the user gave createalias or destroyalias 
    if (alias_managment(user_input, alias))//for this function check history_AND_alias_functions.c/.h
    {
        //I am inside this if only if the user gave createalias or destroyalias
        //The main use of the function noted() is to store the command the user gave 
        noted(user_input, myhistory);//for this function check history_AND_alias_functions.c/.h
        // printf("user_input %s\n", user_input);
        // print_aliases(*alias);
        // printf("==================================================================\n");
        return 0;
    }
    else if (alias_exists(user_input, alias))//else if the user gave an alias command I find the match on the structure
    {//and I repace it with the equivalent command the commands[i] points and assign the real command to user_input for later execution
        user_input = alias_to_command(user_input, alias);//for these functions check history_AND_alias_functions.c/.h
    }
    //We use the function noted for saving the command the user gave
    //For more info go to history_AND_alias_functions.c/.h
    noted(user_input, myhistory);  
      
    //If the command has semicolons then every args[i] points in a string i.e the substring that the 
    //semicolons separate from the 'original' string, if we dont have semicolon or we have one then only
    //the args[0] will have some data inside it 
    //For more info for the function user_command check above
    args = user_command(user_input);
    // print_2pointer_array(args);
    int i;
    for ( i = 0; args[i]; i++)//For every substring that is a command executite 
    {
        //Now go to syspro_AND_pipes_functions.c/.h for more info
        execution_managment(args[i]);        
    }       
    //We free the table
    free_2pointer_array(args);//for function free_2pointer_array() check basic_functions.c/.h
}