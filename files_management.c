#include "files_management.h"

//SOS
//I have 3 different ways to open a file
//first one is the function file_open1() that I open with O_CREAT | O_TRUNC | O_RDWR
//second one is the function file_open2 that I open with O_RDWR
//third one is the function file_open3 that I open with O_APPEND | O_CREAT | O_RDWR

int file_open1(char *name_file)
{
    int fd;

    if ((fd = open(name_file, O_CREAT | O_TRUNC | O_RDWR, PERMS)) == -1)
    {
            printf("error opening file\n");
            exit(1);
    }
    return fd;
}

int file_open2(char *name_file)
{
    int fd;

    if ((fd = open(name_file, O_RDWR, PERMS)) == -1) 
    {
            printf("error opening file\n");
            exit(1);
    }
    return fd;
}

int file_open3(char *name_file)
{
    int fd;

    if ((fd = open(name_file, O_APPEND | O_CREAT | O_RDWR, PERMS)) == -1)
    {
            printf("error opening file\n");
            exit(1);
    }
    return fd;
}


