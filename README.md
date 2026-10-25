# syspro unix shell clone

## Assignment Description
Implementation of a Unix shell in C with support for I/O redirections, pipes, aliases and command history<br>

## Compiling and Running the program :

1) Type `make`
2) Type `./mysh` to run the program

## What the user can type in the program and have it executed :

- First of all the program is able to handle multiple commands with semicolons as independent from one another during their execution
- It is able to understand and separate the command from the spaces i.e. e.g.

  ```
        ls         -t       ;ls
  ls    -lt             ;
  ```

  it can execute them. Also in the examples below with pipes, redirections or even a combination of the two it is able to separate the command from the spaces i.e.

  ```
  ls>file1|sort file2
  ```

  It will do a completely similar operation as if we had

  ```
  ls > file1 | sort file2
  ```
- Also the program can handle the command `cd something` the same way a normal terminal handles it
- It can handle commands with more than one pipe e.g.

  ```
  ls > file1 | sort file2 | ls
  ```
- It can handle pipes together with redirections e.g.

  ```
  cat file1 file2 file3 | sort > file4
  ```
- It can handle all redirections i.e. `<` , `>` , `>>` and even if we have

  ```
  sort < file1 > file2
  ```
- If the user gives it the command `history` it prints the user's last 20 commands and to execute the n-th command they type `!n` ( just like in the linux terminal )
- It handles aliases e.g. if the user does

  ```
  createalias lsa "ls -lt"
  ```

  and then the user types `lsa` it maps it to `ls -lt` and executes it

  Also if the user gives the command

  ```
  createalias lsa "cat file1"
  ```

  it now makes `lsa` equivalent to the command `cat file1` and not to `ls -lt`

  It also recognizes `destroyalias lsa`

## Design choices:

- The user can enter up to 10000 (`MAXSIZE`) characters ( as in the linux terminal )
- For the history storage (myHistory) I have declared in the file `history_AND_alias_functions.h` the global variable `char **myhistory` which points to an array of pointers where each pointer points to a string

  (Note I know that this is not the best design choice but the way I organized my code if the user gave `history` I would have to carry `char **myhistory` through 5 different functions where in the end I would only need it in the last one which ‘executes the command’ so this was the main reason I used a global variable but I tried to handle it like a non-global variable i.e. in the functions `delete_myhistory(...)`, `noted(...)`, `print_myhistory(…)`, `replace_myhistory(…)` where I change the contents of the array that `myhistory` points to I pass it as an argument)
- To save code if the user gives a simple command e.g. `ls -lt` I pass it through the function `command_pipe` which basically since it does not see that it has a pipe just removes the leading/trailing spaces and returns it normally as `ls -lt` so later in the function `execution_pipe` which will call the function `execution_command` it will not fork – and create a pipe because it does not have more than one part ( from the function `command_pipe` which ‘splits’ the initial string based on the pipes it has ) therefore it will go straight to executing the command `ls -lt`, so for simple commands like e.g. `ls -lt` I used the pipe functions without creating a pipe to save code

## Therefore :

In the files `basic_functions.c/.h` I have some basic functions such as the function `char **user_command(…)` which builds the structure `char **args` which points to an array of pointers where each position of the array points to a string these strings are the user's commands separated according to the semicolons if there are any in the initial string they wrote, we have the function `int parsing_commandline (…)` where for each pointer of the above array that points to a user command it calls various functions i.e. it does the parsing, we have `int free_2pointer_array(…)` which frees this whole array, the function `char **remove_spaces(...)` which ‘deletes’ the leading/trailing spaces from each string that each node of the array points to and the function `char **remove_inside_spaces(…)` which ‘deletes’ the inner spaces from each string that each node of the array points to.

In the files `syspro_AND_pipes_functions.c/.h` I have the functions that are related either to the things we learn in the course or to pipes i.e. the function `int execution_managment(…)` takes a string and checks if it has pipes, redirections, if it has the command `cd something` or if it is a simple command and according to what it finds it calls the corresponding functions, the function `char **command_pipes(…)` works in a similar way to `char **user_command(…)` from the previous paragraph i.e. it builds a `char **args` which points to an array of pointers where each pointer points to a string separated according to the pipes if there are any from the string it takes as an argument, the function `int execution_pipe(…)` which starts building this chain of pipes if there are any in the command by calling the function `int execution_command(…)` which if it has more than one element from the array returned by `char **command_pipe(…)` creates the pipe and depending on which part of the pipe we are in (left or right of the “ | ”) either writes into it or waits to read from the pipe and calls itself for the implementation of the right part of the pipe because there may be another pipe then it creates it and writes into it or if there is not it executes the command and this is repeated for as many pipes as we have in the command, finally we have the function `int exec_command(…)` which simply executes the command according to the argument it takes.

We have the files `redirection_functions.c/.h` where the functions related to redirections are located

We have the files `history_AND_alias_functions.c/.h` which refer to the history and alias structures with the corresponding functions needed for their implementation

Finally we have the files `file_managment.c/.h` for opening the files

## WHAT HAS BEEN IMPLEMENTED:

**shell**
- [x] Basic shell functionality for entering and calling simple commands e.g. `ls`
- [x] Returning and printing results

**redirections**
- [x] Single redirection `>` or `<`
- [x] Double redirection
- [x] Append redirection `>>`

**pipes**
- [x] Simple pipe `cat file |grep "nikos"`
- [x] Combination with redirection `cat file |grep "nikos" >file2`

**aliases**
- [x] Create and use alias
- [x] Destroy (deletion)

**history**
- [x] `myHistory` save and print
- [x] Calling a command without retyping it

## WHAT HAS NOT BEEN IMPLEMENTED:

EVERYTHING HAS BEEN IMPLEMENTED EXCEPT c) execution of commands in the Background (&), d) wild character support and f) signal handling (signals)

**THANK YOU!!!!!!!**
