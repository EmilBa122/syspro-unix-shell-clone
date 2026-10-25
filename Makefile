OBJS 	= main.o basic_functions.o files_management.o syspro_AND_pipes_functions.o redirection_functions.o history_AND_alias_functions.o
SOURCE	= main.c basic_functions.c files_management.c syspro_AND_pipes_functions.c redirection_functions.c history_AND_alias_functions.c
HEADER  = basic_functions.h files_management.h syspro_AND_pipes_functions.h redirection_functions.h history_AND_alias_functions.h
OUT  	= mysh
CC		= gcc
FLAGS   = -g -c 
# -g option enables debugging mode 
# -c flag generates object code for separate files

all: $(OBJS)
	$(CC) -g $(OBJS) -o $(OUT)

# create/compile the individual files >>separately<< 
main.o: main.c basic_functions.h
	$(CC) $(FLAGS) main.c

history_AND_alias_functions.o: history_AND_alias_functions.c history_AND_alias_functions.h
	$(CC) $(FLAGS) history_AND_alias_functions.c

basic_functions.o: basic_functions.c basic_functions.h
	$(CC) $(FLAGS) basic_functions.c

files_management.o: files_management.c files_management.h
	$(CC) $(FLAGS) files_management.c

redirection_functions.o: redirection_functions.c redirection_functions.h
	$(CC) $(FLAGS) redirection_functions.c

syspro_AND_pipes_functions.o: syspro_AND_pipes_functions.c syspro_AND_pipes_functions.h
	$(CC) $(FLAGS) syspro_AND_pipes_functions.c

# clean house
clean:
	rm -f $(OBJS) $(OUT)

