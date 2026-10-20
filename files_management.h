#pragma once
#include <stdio.h>
#include <stdlib.h>
#include <fcntl.h>
#include <unistd.h>

#define PERMS 0644 //set access permissions
#define BUFFSIZE 1024

//On what they do these functions check the files_managment.c I explain there with comments what the purpose they have
int file_open1(char *name_file);
int file_open2(char *name_file);
int file_open3(char *name_file);