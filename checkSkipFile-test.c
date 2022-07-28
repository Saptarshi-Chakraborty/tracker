/* Checkin if a file/folder exists in  (.skip) file */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "primaryFunctions.c";

#define SKIP_FILE ".skip";

// Function Declaration
int isInSkipFile(char *path);

void main()
{
    int result;
    char path[250];
    printf("\n---------------------------------------\n");
    printf("Hello World -> %s\n", __DATE__);

    strcpy(path, "tfolder/abc");

    // printf("[%d]\n",isFolder("tdfolder/"));
    // exit(0);

    result = isInSkipFile(path);
    printf("\n$ isInSkipFile [%s] -> %d (%s)\n", path, result, (result == 0) ? "Yes" : "No");

    printf("\n---------------------------------------\n");
}

// Function defination
int isInSkipFile(char *path)
{
    FILE *skipFile;
    int i;
    char line[350], ch, *tempPath;
    char *tempStr1, *tempStr2;
    printf("\n>> Path got [%s]\n", path);

    skipFile = fopen(".skip", "r");

    // Check if Skip file exists
    if (skipFile == NULL)
    {
        printf("Sorry, But the file was not found...\n");
        return 1;
    }

    // Check if the given path is a file or folder
    if (isFile(path) == 0)
    {
        printf("# It is a File\n");
    }
    else if (isFolder(path) == 0)
    {
        printf("# It is a Folder\n");
    }

    // Retrive one by one line from .skip file
    tempPath = (char *)malloc(strlen(path));
    strcpy(tempPath, path);

    while (fgets(line, sizeof(line), skipFile) != NULL)
    {
        if (line[(strlen(line) - 1)] == '\n')
        {
            line[(strlen(line) - 1)] = '\0';
        }
        // printf("Line = [%s] - length(%d) \n", line, strlen(line));

        // Ignore Comment line(starting with #) & empty lines
        if (line[0] == '#' || strlen(line) == 0)
        {
            // printf("Comment Line [%s]\n", line);
            continue;
        }

        // line is Ready for Processing
        // FOR Folder
        printf(">> line [%s]\n", line);
        // CASE: 2 (/folder_name)
        if (strcmpi(path, line) == 0)
        {
            printf(">> direct match -> path(%s) & line(%s)\n", path, line);
            return 0;
        }

        // CASE: 2 (/folder_name)
        if (line[0] == '/' || line[0] == '\\')
        {
            // Eleminate the starting slash and check
            tempStr2 = (char *)malloc(strlen(line) + 1);
            for (i = 1; i < (strlen(line)); i++)
            {
                tempStr2[i - 1] = line[i];
            }
            tempStr2[(i - 1)] = '/';
            tempStr2[i] = '\0';

            printf(">> tempStr2 (%s)\n", tempStr2);

            if (strcmpi(path, tempStr2) == 0)
            {
                printf(">> matched path[%s] & line[%s]-modified(%s) \n", path, line, tempStr2);
                return 0;
            }
            else
            {
                return 1;
            }

            free(tempStr2);
        }
        // CASE: 3 (folder_name/)
        else if (tempPath[(strlen(tempPath) - 1) == '/'])
        {
            printf("\n>> Line has / at the end\n");

            tempStr1 = (char *)malloc(strlen(tempPath));

            strcpy(tempStr1, tempPath);
            strcat(tempStr1, "/");

            printf(">> after Concat tempStr1 (%s)\n", tempStr1);

            if (strcmpi(tempStr1, line) == 0)
            {
                printf(">> Direct match path(%s)-modified[%s] & line(%s)\n", path, tempStr1, line);
                free(tempStr1);
                return 0;
            }
            printf(">> Not found any Direct match\n");

            printf(">> split path with / -> %s\n", strchr(tempPath, '/'));

            free(tempStr1);
            return 1;
        }
    }

    free(tempPath);
    fclose(skipFile);

    return 1;
}
