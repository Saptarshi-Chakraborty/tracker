/* Checkin if a file/folder exists in  (.skip) file */

#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "primaryFunctions.c";

#define SKIP_FILE ".skip";

// Function Declaration
int isInSkipFile(const char *path);

void main()
{
    int result;
    char path[250];
    printf("\n---------------------------------------\n");
    printf("Hello World -> %s\n", __DATE__);

    // strcpy(path, "tfolder/abc");
    strcpy(path, "tfolder/efg/tdfold er/abc");

    // printf("[%d]\n",isFolder("tdfolder/"));
    // exit(0);

    result = isInSkipFile(path);
    printf("\n$ isInSkipFile [%s] -> %d (%s)\n", path, result, (result == 0) ? "Yes" : "No");

    printf("\n---------------------------------------\n");
}

// Function defination
int isInSkipFile(const char *path)
{
    FILE *skipFile;
    int i, a, lineHasTraillingShash = 1;
    char line[350], ch, *tempPath;
    char *tempStr1, *tempStr2, *tempStr3;
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

    // printf(">> temporary path created = (%s)\n",tempPath);

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

        // CASE: 1 (full_path_to/folder)
        if (strcmpi(path, line) == 0)
        {
            printf(">> direct match 1: path(%s) & line(%s)\n", path, line);
            return 0;
        }

        // CASE: 2 (/folder)
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
                printf(">> Match found 2: path[%s] & line[%s]-modified(%s) \n", path, line, tempStr2);
                return 0;
            }
            else
            {
                return 1;
            }

            free(tempStr2);
        }
        else if (tempPath[(strlen(tempPath) - 1) == '/'])
        {
            // CASE: 3 ( folder/ ) & ( folder ) <sub string>
            printf("\n>> Path has '/' at the end\n");

            tempStr1 = (char *)malloc(strlen(tempPath));

            strcpy(tempStr1, tempPath);
            if (line[strlen(line) - 1] == '/')
            {
                strcat(tempStr1, "/");
                printf(">> slash at the end of Line\n");
            }

            printf(">> after concat stage: tempStr1 (%s)\n", tempStr1);

            if (strcmpi(tempStr1, line) == 0)
            {
                printf(">> Direct match 3: path(%s)-modified[%s] & line(%s)\n", path, tempStr1, line);
                free(tempStr1);
                return 0;
            }
            printf(">> Not found any Direct match\n");

            while (tempStr1 != NULL)
            {
                tempStr1 = strchr(tempStr1, '/');

                if (tempStr1 == NULL)
                {
                    printf(">> NULL Returned\n");
                    break;
                }

                strcpy(tempStr1, &tempStr1[1]);
                printf(">> split path  -> %s\n", tempStr1);

                if (strcmpi(tempStr1, line) == 0)
                {
                    printf(">> Match found 3: path(%s)-m(%s) & line(%s)\n", path, tempStr1, line);
                    return 0;
                }
            }
            printf("\n>>Exit- split path with / -> %s\n", tempStr1);
            free(tempStr1);

            // CASE: 4 ( folder/ ) & ( folder ) <part by part>
            printf("\n-----------------------------------------------------------\n");

            tempStr1 = (char *)malloc(strlen(tempPath));

            strcpy(tempStr1, tempPath);
            if (line[(strlen(line) - 1)] == '/')
            {
                strcat(tempStr1, "/");
                lineHasTraillingShash = 0;
            }

            printf(">> after re-allocated: temp path (%s)\n", tempStr1);
            printf("LINE Is = [%s]\n", line);

            tempStr2 = (char *)malloc(sizeof(tempStr1));

            while (tempStr2 != NULL)
            {
                tempStr2 = strchr(tempStr1, '/');

                if (tempStr2 == NULL)
                {
                    printf(">> Returned Null\n");
                    break;
                }

                a = strlen(tempStr1) - strlen(tempStr2);

                tempStr3 = (char *)malloc(a + 1);
                strncpy(tempStr3, tempStr1, a);

                printf(">> Itrated part = [%s]\n", tempStr3);

                if (lineHasTraillingShash == 0)
                {
                    strcat(tempStr3, "/");
                }

                if (strcmpi(line, tempStr3) == 0)
                {
                    printf(">> Match found 4: path(%s)-m(%s) & line(%s)\n", path, tempStr3, line);
                    return 0;
                }

                strcpy(tempStr1, &tempStr2[1]);
            }

            free(tempStr1);
            free(tempStr2);
            free(tempStr3);
        }
    }

    free(tempPath);
    fclose(skipFile);

    return 1;
}
