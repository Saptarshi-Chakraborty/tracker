#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <direct.h>
#include <dirent.h>

// ---- Custom Defines ---- //
#define ALL_FILE_LIST ".text/directory/files.txt"
#define ALL_FOLDER_LIST ".text/directory/folders.txt"
#define DRAFT_FILE_NAME "commit_1"
// #define DRAFT_FILE_NAME "c1"
#define LINE_SIZE 1000
#define END_OF_FILE_STRING "1--<__EOF>{END_OF_FILE}--=3"
#define END_OF_FILE_PATH_STRING "0--<__EOFP>{END_OF_FILE_PATH}--=1"
#define END_OF_FOLDER_PATH_STRING "0--<__EOFOP>{END_OF_FOLDER_PATH}--=1"

// ---- Function Prototypes ---- //
void itrateAllFiles();
FILE * writeFileContent(FILE *, char[]);
FILE *generateAllFolders(FILE *);
int createFile(char *);
int createFolder(char *);
int isFile(char *);
int isFolder(char *);

int main()
{
    printf("Hello World\n");

    itrateAllFiles();

    return 0;
}

void itrateAllFiles()
{
    FILE *commitfile;
    char line[LINE_SIZE], filename[LINE_SIZE];
    int line_length = 0;

    commitfile = fopen(DRAFT_FILE_NAME, "r");
    if (!commitfile)
    {
        fprintf(stderr, "!!! Commit File not found !!!\n");
        return;
    }
    printf("Openning file...\n");

    while (fgets(line, LINE_SIZE, commitfile) != NULL)
    {
        // printf("%s", line);
        line_length = strlen(line);

        if (line[line_length - 1] == '\n')
        {
            line[line_length - 1] = '\0';
        }

        int comp = strcmp(line, END_OF_FOLDER_PATH_STRING);

        // printf("Comparing [%s] with [%s] = %d\n", line, END_OF_FOLDER_PATH_STRING, comp); // DEBUG

        if (strcmp(line, END_OF_FILE_PATH_STRING) == 0)
        {
            printf("--- End of File Path ---\n");
            break;
        }
    } // End of while

    // Now read line by line and generate folders
    generateAllFolders(commitfile);

    // Now one by one file content starts
    // First get fill the First F: line
    // Then get the file path
    // Then get the file content
    while (fgets(line, LINE_SIZE, commitfile) != NULL)
    {
        line_length = strlen(line);

        if (line_length < 3)
            continue;

        // trim the next line character
        if (line[line_length - 1] == '\n')
        {
            line[line_length - 1] = '\0';
        }

        // check if the line is file path
        if (line[0] == 'F' && line[1] == ':')
        {
            printf("File Path : [%s]\n", line);

            strcpy(filename, &line[2]);
            printf("File Name : [%s]\n", filename);

            commitfile = writeFileContent(commitfile, filename);

            // break;
            continue;
        }
    }

    fgets(line, LINE_SIZE, commitfile);
    printf("Line : [%s]\n", line);
    fgets(line, LINE_SIZE, commitfile);
    printf("Line : [%s]\n", line);

    fclose(commitfile);
}

FILE *generateAllFolders(FILE *file)
{
    char line[LINE_SIZE];
    int line_length = 0;

    while (fgets(line, LINE_SIZE, file) != NULL)
    {
        line_length = strlen(line);

        if (line[line_length - 1] == '\n')
        {
            line[line_length - 1] = '\0';
        }

        if (strcmp(line, END_OF_FOLDER_PATH_STRING) == 0)
        {
            printf("--- End of Folder Path ---\n");
            return file;
        }

        printf("Folder Path : [%s]\n", line);
        createFolder(line);
    }

    return 0;
}

FILE * writeFileContent(FILE *file, char filepath[])
{
    printf("--- Filepath : [%s] --\n", filepath);
    createFile(filepath);

    // Now write the content of the file till the END_OF_FILE_STRING

    char line[LINE_SIZE], prevline[LINE_SIZE];
    int line_length = 0, prevline_length = 0;
    int flag = 0;
    FILE *fp;

    fp = fopen(filepath, "w");

    while (fgets(line, LINE_SIZE, file) != NULL)
    {
        line_length = strlen(line);
        // trim the next line character
        if (line[line_length - 1] == '\n')
        {
            line[line_length - 1] = '\0';
        }

        if (strcmp(line, END_OF_FILE_STRING) == 0)
        {
            fprintf(fp, "%s", prevline);
            printf("--- End of File Content ---\n");
            
            return file;
        }

        if (flag != 0)
            fprintf(fp, "%s\n", prevline);

        prevline_length = strlen(line);
        strcpy(prevline, line);

        flag = 1;
        // printf("File Content : [%s]\n", line);
    }

    fclose(fp);

    return 0;
}

// ---- Utility Functions ---- //

// Function to create a file
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
    char path[250];
    _getcwd(path, sizeof(path));
    strcat(path, "\\");
    strcat(path, folderName);
    // printf("-- isFolder Path is [%s]\n", path);
    if ((dir = opendir(path)) != NULL)
        return 0;
    else
        return 1;
}