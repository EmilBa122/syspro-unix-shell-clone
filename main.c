
#include "basic_functions.h"

int main(int argc, char *argv[])
{
////////////////////////////////////////////////////////////////////////////
//If the user in ./mysh give something extra 
//e.g. ./mysh sla 
    char *c = argv[0];
    if (!(argc == 1) && (strcmp(c,"./mysh") == 0))
    {
        printf("Check Line Arguments, try again\n");
        return -1;   
    }
///////////////////////////////////////////////////////////////////////////    
    //From here begins the interaction with the user
    char str[MAXSIZE];
    int ch;

    //myhistory is a global variable char ** which points to a table with size = HISTORY_SIZE that every node 
    myhistory = create_myhistory();//is a pointer that points to a string (the last commands the user gave) 
                            
    
    //Initialization of the structure alias and *alias points there
    aliases_struct *alias = init_aliases();
                            
   
    //I clean the buffer from the previous use 
    memset(str, 0 , MAXSIZE);//Initialize the buffer with 0
    printf("in-mysh-now:>");
    ch = getchar();
    while (ch != EOF)
    {                   
        strncat(str, ((char*) &ch), 1);
        ch = getchar();
        if (ch == '\n')
        {
            ch = 0;
            //Stick the 0 who is the NULL in string to know where ends this string 
            strncat(str, ((char*) &ch), 1);
            
            //function for parsing, see more info in basic_functions.c/.h
            parsing_commandline(str, myhistory, alias);
           
            // printf("printing my history\n");
            // print_myhistory(myhistory);
            // printf("end printing myhistory\n");


            printf("in-mysh-now:>");
            //I clean the buffer from the previous use 
            memset(str, 0 , MAXSIZE);//Initialize the buffer with 0
        }              
    } 
    // print_aliases(*alias);
    delete_aliases(alias); 
    delete_myhistory(myhistory);         
}
  
   

