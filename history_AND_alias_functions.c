#include "history_AND_alias_functions.h"

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////History Managment////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

char **create_myhistory()//Creation of myhistory, points to a table with size = HISTORY_SIZE that every node 
{                        //is a pointer that points in a string (the last commands the user gave)

    char **history = malloc(sizeof(char *) * HISTORY_SIZE);
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
        history[i] = NULL;
    }
    return history;

}

int delete_myhistory(char **history)//Destruction of myhistroty
{
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
        if (history[i])
        {
            free(history[i]);
            history[i] = NULL;
        }    
    }
    free(history);
    history = NULL;
    return 0;
}

int print_myhistory(char **history)
{
    for (int i = 0; i < HISTORY_SIZE; i++)
    {
        if (history[i])
            printf(" %d   %s\n", i, history[i]);
    }
    return 0;
}

//The function set_myhistory first frees the pointer[i] and after that it points in the command[i + 1] the user 
//gave, in the last position of this table the pointer point in on the user_input (i.e the last command 
//the user gave)
int set_myhistory(char *user_input, char **myhistory)
{
    int i;
    for ( i = 0; i < (HISTORY_SIZE - 1); i++)
    {
        free(myhistory[i]);
        myhistory[i] = malloc(sizeof(char) * (strlen(myhistory[i + 1]) + 1));
        strcpy(myhistory[i], myhistory[i + 1]);
    }
    free(myhistory[i]);
    myhistory[i] = malloc(sizeof(char) * (strlen(user_input) + 1));
    strcpy(myhistory[i], user_input);
    return 0;
}

//The main use of the function noted is to store the command the user gave
int noted(char *user_input, char **myhistory)
{
    //The char **myhistory points to a table with size = HISTORY_SIZE that every node is a pointer that 
    //points in a string (the commands the user gave)
    int i = 0;
    // printf("user_input = %s\n", user_input);
    while ( 1 )
    {

        if (myhistory[i] == NULL)//We search the firt empty position in this table 
        {//If we find one we store the command 
            myhistory[i] =  malloc(sizeof(char) * (strlen(user_input) + 1));
            strcpy(myhistory[i], user_input);
            break;
        }
        i++;
        //If the table is full we must delete the oldest command i.e the firt one 
        //this is achieved with the function set_myhistory
        if ( i == HISTORY_SIZE )
        {
            set_myhistory(user_input, myhistory);
            break;
        }
    }
    return 0;
}

//check_command_history checks if the user gave the command "history"
int check_command_history(char *execution)
{
    if (strcmp("history", execution) == 0)
    {
        return 1;
    }
    return 0;
}

//Function replase_history() checks if we have for example !20 and if yes the user_input points now
//to this old command the history table has else if no the user_input it remains as it was
char *replace_history(char *user_input, char **myhistory)
{
    int flag = 0;
    int i;
    for ( i = 0; user_input[i]; i++)
    {
        if (user_input[i] == '!')
        {
            flag = 1;
            break;
        }
    }
    if (flag == 0)
    {
        return user_input;
    }
    char *ptr = &user_input[i + 1];
    strcpy(user_input,  myhistory[atoi(ptr)]);
    return user_input;
}

////////////////////////////////////////////////////////////////////////////////////////////////////////////
//////////////////////////////////////Aliasaes Managment////////////////////////////////////////////////////
//////////////////////////////////////////////////////////////////////////////////////////////////////////

aliases_struct  *init_aliases()//Initialize the structure of aliases and return a pointer who point to this
{                               //structure
    aliases_struct  *alias = malloc(sizeof(aliases_struct));
    for (int i = 0; i < SIZE; i++)
    {
        alias-> aliases[i] = NULL;
        alias-> commands[i] = NULL;
        // printf("%s", alias-> commands[i]);
    }
    return alias;
}

int delete_aliases(aliases_struct *alias)//Destruction of structure aliases
{
    for (int i = 0; i < SIZE; i++)//For every node 
    {
        if (alias->aliases[i])//We check if this node has something
        {
            free(alias->aliases[i]);
            alias-> aliases[i] = NULL;
            free(alias->commands[i]);
            alias->commands[i] = NULL;
        }
    }
    free(alias);
    alias = NULL;
    return 0;
}

int print_aliases(aliases_struct alias)
{
    printf("print aliases\n");
    for (int i = 0; i < SIZE; i++)
    {
        if (alias.aliases[i])
        {
            printf("%d\n", i);
            printf("%s\n", alias.aliases[i]); 
            printf("%s\n", alias.commands[i]);
        }
    }
    printf("end printing aliases\n");
    return 0;
}

//this function 'deletes' the spaces from the new_command
void clear_new_command(char *new_command)
{
    new_command[strlen(new_command) - 1] = 0;
    char *ptr = &new_command[1];
    strcpy(new_command, ptr);
}

//This function is used when I want to make a match in the structure aliases_struct between the string *alias_name and
//*new_command
int create_new_alias(char *alias_name, char *new_command, aliases_struct *alias)
{
    int flag = 0;
    int i;
    //this function 'deletes' the spaces from the new_command
    clear_new_command(new_command);//for this function check above
    //we check if in the structure aliases_struct is already exist the alias_name then if yes we replace the old command
    //with the new_command that the alias_name will match
    for ( i = 0; i < SIZE; i++)
    {
        if (alias->aliases[i])
        { 
            if (strcmp(alias_name,alias->aliases[i]) == 0)
            {
                free(alias->commands[i]);
                alias->commands[i] = malloc(sizeof(char ) * (strlen(new_command) + 1));
                strcpy(alias->commands[i], new_command);
                flag = 1;
                break;
            }
        }
    }
    if (flag)
    {
        return 1;
    }
    //we find the first empty position of the structure aliases_struct to insert this new match
    for ( i = 0; i < SIZE; i++)
    {
        if (alias->aliases[i] == NULL)
        {
            alias->aliases[i] = malloc(sizeof(char) * (strlen(alias_name) + 1));
            alias->commands[i] = malloc(sizeof(char ) * (strlen(new_command) + 1));
            strcpy(alias->aliases[i], alias_name);
            strcpy(alias->commands[i], new_command);
            // printf("\n\n");
            // printf("%s %s\n", alias->aliases[i], alias->commands[i]);
            // printf("\n\n");
            break;
        }
    }
    return 1;
}

//In this function we destroy the match between an alias_name and a command inside the structure aliases_struct
int destroy_alias(char *alias_name, aliases_struct *alias)
{
    for ( int i = 0; i < SIZE; i++)
    {
        if (!strcmp(alias_name,alias->aliases[i]))
        {
            free(alias->aliases[i]);
            alias-> aliases[i] = NULL;
            free(alias->commands[i]);
            alias->commands[i] = NULL;
            return 1;
        }
    }
    printf("Something went wrong check carefully what you write in keyboard\n\n");
    return 0;
}

//This function manages if the user gave createalias or destroyalias
int alias_managment(char *user_input, aliases_struct *alias)
{
    char buffer[MAXSIZE];
    char alias_name[MAXSIZE], new_command[MAXSIZE];
    strcpy(buffer, user_input);
    char *token = strtok(buffer, " ");
    if ( (strcmp(token, "createalias")) && (strcmp(token, "destroyalias")) )//Everything else expect createalias/destroyalias
    {
        return 0;//We dont care
    }
    if (!strcmp(token, "createalias"))//if the user gave createalias something1 something2
    {
        //we separate the something1 alias name from the string
        token = strtok(NULL , " ");
        strcpy(alias_name, token);
        token = strtok(NULL , "\0");//prin edw eixa " \0"  !!!!!!
        //we separate the something2 command from the string
        strcpy(new_command, token);
        // printf("alias %s %s\n", alias_name, new_command);
        //we call this function to make this match between the alias and the actual command in the structure aliases_struct
        return create_new_alias(alias_name, new_command, alias);//for this function check above                                 
    }
    else if ((!strcmp(token, "destroyalias")))//if the user gave destroyalias something
    {
        token = strtok(NULL , " \0");
        strcpy(alias_name, token);
        return destroy_alias(alias_name, alias);//for this function check above
    }
    return 0;
}

//the main use of this function is to find the match between the alias the user gave and the real command which is stored
//in the structure aliases_struct
char *alias_to_command(char *user_input, aliases_struct *alias)
{
    for (int i = 0; i < SIZE; i++)//alias->aliases[i]
    {
        if (alias->aliases[i])
        {
            if (!strcmp(alias->aliases[i], user_input))
            {
                return alias->commands[i];
            }
        }
    }
    return user_input;
}

int alias_exists(char *user_input, aliases_struct *alias)
{
    for (int i = 0; i < SIZE; i++)//alias->aliases[i]
    {
        if (alias->aliases[i])
        {
            if (!strcmp(alias->aliases[i], user_input))
            {
                return 1;
            }
        }
    }
    return 0;
}








