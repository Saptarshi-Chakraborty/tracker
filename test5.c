/*     Test  functions for (.skip) file     */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "utilityFunctions.c"

#define SKIP_FILE ".skip"

// Function Declaration
int isInSkipFile(char *path); // 0-yes, 1-no

int main()
{
    printf("\n---------------------------------------------------\n");
    printf("Hello World -> %s\n", __DATE__);
    // printf("checkSkipFile() => %d\n", checkSkipFile());

    char path[250] = ".text/directory/all.txt";

    int result = isInSkipFile(path);
    printf("\n$ isInSkipFile [%s]  => %d (%s)\n", path, result, (result == 0) ? "Yes" : "No");
    printf("\n---------------------------------------------------\n");
    return 0;
}

// Function to check if a path is in .skip file
int isInSkipFile(char *path)
{
    FILE *skip;
    char line[450], ch, *tempName;
    int i = 0, flag1 = 1;
    int a, b, pathLength;
    char *pathCopy, *token;

    printf("START : path [%s]\n\n", path);

    skip = fopen(SKIP_FILE, "r");
    if (skip == NULL)
        return 1;

    while (fgets(line, sizeof(line), skip))
    {
        if (line[strlen(line) - 1] == '\n')
            line[strlen(line) - 1] = '\0';

        if (line[0] == '#' || strlen(line) == 0)
            continue;
        else if (line[0] == '/') // if the line starts with / in .skip file
        {
            // Line is ready for processing
            printf("---- line(f) : (%s) ----\n", line);

            tempName = (char *)malloc(sizeof(char) * (strlen(line) + 2));
            strcpy(tempName, &line[1]);
            if (tempName[strlen(tempName) - 1] != '/')
                strcat(tempName, "/");
            // printf("---folder Search = [%s]\n", tempName);
            // printf(">> Difference of [%s] & [%s] = %s\n",path,tempName,strstr(path, tempName));

            if (strstr(path, tempName) != NULL)
            {
                printf(">> Matched [%s] & [%s]\n", path, tempName);
                return 0;
            }
            free(tempName);
        }
        else
        {
            // Line is ready for processing
            printf("---- line : (%s) ----\n", line);
            if (stricmp(path, line) == 0) // if both matches
                return 0;

            pathCopy = (char *)malloc(sizeof(char) * (strlen(path)));
            strcpy(pathCopy, path);
            printf(">> pathCopy = [%s]\n", pathCopy);

            if (strstr(pathCopy, line) != NULL)
            {
                token = strtok(pathCopy, "/");
                while (token != NULL)
                {
                    printf(">> token = [%s]\n", token);
                    if ((stricmp(token, line) == 0))
                    {
                        printf(">> Matched [%s] & [%s]\n", path, line);
                        return 0;
                    }
                    token = strtok(NULL, "/");
                }
                free(pathCopy);
            }
            else
                return 3;
        }
    }

    fclose(skip);
    return 1;
}