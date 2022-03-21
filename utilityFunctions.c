#include <stdio.h>
#include <sys/types.h>
#include <direct.h>

void utilityFunctions(void){
    printf("This is 'utilityFunctions.c' file \n");
}

// Function to create a new file
int createFile(char *fileName)
{
    FILE *fp;
    fp = fopen(fileName, "w");
    if (fp)
        return 0;
    else
        return 1;
}

// Function to create a folder
int createFolder(char *folderName)
{
    int i = 0;
    char path[200];
    _getcwd(path, sizeof(path));
    strcat(path, "\\");
    strcat(path, folderName);
    printf("Path is [%s]\n", path);
    i = _mkdir(path);
    if (i == 0)
        return 0;
    else
        return 1;
}

// Function to check if a file exists
int isFile(char *fileName)
{
    FILE *fp;
    fp = fopen(fileName, "r");
    if (fp)
        return 1;
    else
        return 0;
}

// Function to check if a folder exists
int isFolder(char *folderName)
{
    int i = 0;
    char path[200];
    _getcwd(path, sizeof(path));
    strcat(path, "\\");
    strcat(path, folderName);
    printf("Path is [%s]\n", path);
    i = _access(path, 0);
    if (i == 0)
        return 1;
    else
        return 0;
}