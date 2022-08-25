#define _GNU_SOURCE

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>

// #define function1
#define function2
#define LINE_SIZE 10

int writeFileContent();

int main()
{
    printf("Hello World\n");
    writeFileContent();
    return 0;
}

#ifdef function1
int writeFileContent()
{
    FILE *draftFile, *targetFile;
    char *targetFileName = "abc.txt";
    char line[1000];

    targetFile = fopen(targetFileName, "r");
    if (targetFile == NULL)
        return 1;

    draftFile = fopen("_DRAFT_", "w");
    if (draftFile == NULL)
        return 2;

    while (fgets(line, sizeof(line), targetFile) != NULL)
    {
        printf("%s", line);
        fprintf(draftFile, "+%s", line);
    }

    fclose(targetFile);
    fclose(draftFile);
    return 0;
}
#endif

#ifdef function2

int writeFileContent()
{
    FILE *allFiles;
    char *fileName = "../.text/directory/files.txt";
    char buffer[LINE_SIZE], *line, *tempStr1, *tempStr2;
    int bufferLength, i = 0;
    int flag1, flag2, flag3;
    int value1, value2;
    printf("Start---\n\n");

    bufferLength = sizeof(buffer);
    allFiles = fopen(fileName, "r");
    if (allFiles == NULL)
    {
        perror("File not opened");
        exit(EXIT_FAILURE);
    }

    flag1 = 0;
    flag2 = 0;

    while (fgets(buffer, bufferLength, allFiles))
    {
        printf("[%s]\n", buffer);
        i++;

        if (buffer[strlen(buffer) - 1] != '\n')
        {
            flag1 = 1;
        }
        // flag1

        if (flag1 == 1)
        {
            if (flag2 == 0)
            {
                tempStr1 = (char *)malloc(LINE_SIZE);
                strcpy(tempStr1, buffer);
            }
            else
            {
                flag2 = 1;
                value1 = strlen(tempStr1);

                tempStr2 = (char *)malloc(value2);
                strcpy(tempStr2, tempStr1);
                tempStr1 = (char *)realloc(tempStr1, (value1 + strlen(buffer)));

                strcpy(tempStr1, tempStr2);
                strcat(tempStr1, buffer);

                free(tempStr2);
            }
        }
        else
        {

            // Do something
        }

    } // while end

    printf("\n\n-----\ni= %d\n", i);
    fclose(allFiles);

    return 0;
}

#endif