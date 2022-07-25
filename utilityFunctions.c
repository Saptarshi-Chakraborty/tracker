#ifndef _utilityfunctions_c_file
#define _utilityfunctions_c_file

#include <stdio.h>
#include <stdlib.h>
#include <sys/types.h>
#include <direct.h>
#include <dirent.h>

// ---- Custom  Defines ----
#ifndef SAVE_FOLDER_NAME
#define SAVE_FOLDER_NAME ".text\\directory"
#define SAVE_FILE_NAME ".text\\directory\\all.txt"
#define SAVE_ONY_FILES ".text\\directory\\files.txt"
#define SAVE_ONY_FOLDERS ".text\\directory\\folders.txt"
#define SAVE_ONY_FILES_BASENAME ".text\\directory\\filename.txt"
#define SAVE_ONY_FOLDERS_BASENAME ".text\\directory\\foldername.txt"
#endif

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

int separate_File_Folder()
{
    FILE *all, *files, *folders;
    char line[260], ch;
    int i;

    all = fopen(SAVE_FILE_NAME, "r");
    if (all == NULL)
        return 1;

    i = 0;
    files = fopen(SAVE_ONY_FILES, "w");
    folders = fopen(SAVE_ONY_FOLDERS, "w");

    if (files == NULL || folders == NULL)
        return 2;

    while (ch != EOF)
    {
        ch = fgetc(all);
        if ((ch != '\n') && (ch != '\n'))
            line[i++] = ch;

        if (ch == '\n')
        {
            if (i >= 1)
                line[i] = '\0';

            i = 0;
            // Now Line is ready to be processed
            if (isFile(line) == 0)
                fprintf(files, "%s\n", line);
            else if (isFolder(line) == 0)
                fprintf(folders, "%s\n", line);
            else
                fprintf(files, "%s\n", line);
        }
    }
    if (i >= 1)
        line[--i] = '\0';

    fclose(all);
    fclose(files);
    fclose(folders);
    return 0;
}

// Return file/foldername from the given path
char *path_to_basename(char *path)
{
    char *p;
    p = strrchr(path, '/');
    if (p)
        return p + 1;
    else
        return path;
}

// Function to check if a given file tracking or Not
// @Return
int isFileTracking(char *filename)
{
    FILE *fp;
    char line[260];
    fp = fopen(SAVE_ONY_FILES, "r");
    if (fp)
    {
        while (fgets(line, sizeof(line), fp))
        {
            if (line[strlen(line) - 1] == '\n')
                line[strlen(line) - 1] = '\0';
            if (strcmp(line, filename) == 0)
                return 0;
        }
    }
    return 1;
}

// Function to check if a given folder tracking or Not
int isFolderTracking(char *foldername)
{
    FILE *fp;
    char line[260];
    fp = fopen(SAVE_ONY_FOLDERS, "r");
    if (fp)
    {
        while (fgets(line, sizeof(line), fp))
        {
            if (line[strlen(line) - 1] == '\n')
                line[strlen(line) - 1] = '\0';
            if (strcmp(line, foldername) == 0)
                return 0;
        }
    }
    return 1;
}

#endif // file include endif