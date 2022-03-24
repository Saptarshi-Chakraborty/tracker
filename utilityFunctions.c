#ifndef utilityfunctions_c_file
#define utilityfunctions_c_file

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <direct.h>
#include <dirent.h>

void utilityFunctions(void)
{
    printf("This is 'utilityFunctions.c' file \n");
}

// Function to create a new file
// @Returns, 0-if file is created successfully, 1 - if failed to create file
int createFile(char *fileName)
{
    FILE *fp;
    if (isFile(fileName) == 0)
        return 0;
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
    if (isFolder(folderName) == 0)
        return 0;
    _getcwd(path, sizeof(path));
    strcat(path, "\\");
    strcat(path, folderName);
    printf("-- createFolder Path is [%s]\n", path);
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
        return 0;
    else
        return 1;
}

// Function to check if a folder exists
int isFolder(char *folderName)
{
    DIR *dir;
    char path[200];
    _getcwd(path, sizeof(path));
    strcat(path, "\\");
    strcat(path, folderName);
    // printf("-- isFolder Path is [%s]\n", path);
    if ((dir = opendir(path)) != NULL)
        return 0;
    else
        return 1;
}

// Function to replace a string in another string borrowed from GeeksForGeeks
char *replaceWord(const char *fullString, const char *oldWord, const char *newWord)
{
    char *result;
    int i, cnt = 0;
    int newWlen = strlen(newWord);
    int oldWlen = strlen(oldWord);
    for (i = 0; fullString[i] != '\0'; i++)
    {
        if (strstr(&fullString[i], oldWord) == &fullString[i])
        {
            cnt++;
            i += oldWlen - 1;
        }
    }
    result = (char *)malloc(i + cnt * (newWlen - oldWlen) + 1);
    i = 0;
    while (*fullString)
    {
        if (strstr(fullString, oldWord) == fullString)
        {
            strcpy(&result[i], newWord);
            i += newWlen;
            fullString += oldWlen;
        }
        else
            result[i++] = *fullString++;
    }
    result[i] = '\0';
    return result;
}

char *getFullPath(char *name)
{
    char path[200];
    char *tempName = replaceWord(name, "/", "\\");
    _getcwd(path, sizeof(path));
    strcat(path, "\\");
    strcat(path, tempName);
}

#endif // file include endif