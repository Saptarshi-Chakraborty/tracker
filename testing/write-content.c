#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

// #define function1
#define function2
#define LINE_SIZE 1000

int writeFileContent();
int readLengthIndependentLine();

int main()
{
    printf("Hello World\n");
    readLengthIndependentLine();
    return 0;
}

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


 
int readLengthIndependentLine()
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

    while (fgets(buffer, bufferLength, allFiles) != NULL)
    {
        i++;

        if (buffer[strlen(buffer) - 1] == '\n')
        {
            if (flag1 == 1)
            {
                value1 = strlen(tempStr1);
                line = (char *)malloc(value1 + strlen(buffer) + 1);

                strcpy(line, tempStr1);
                strcat(line, buffer);
                free(tempStr1);
            }
            else
            {
                // if buffer includes full line
                line = (char *)malloc(strlen(buffer));
                strcpy(line, buffer);
            }
        }
        else
        {
            if (flag1 == 0)
            {
                tempStr1 = (char *)malloc(LINE_SIZE);
                strcpy(tempStr1, buffer);
            }
            else
            {
                value1 = strlen(tempStr1);

                tempStr2 = (char *)malloc(value1);
                strcpy(tempStr2, tempStr1);

                tempStr1 = (char *)realloc(tempStr1, (value1 + strlen(buffer) + 1));
                strcpy(tempStr1, tempStr2);
                strcat(tempStr1, buffer);

                free(tempStr2);
            }
            flag1 = 1;
            continue;
        }

        // Now, line is ready to use
        value2 = strlen(line);
        // if (line[value2 - 1] == '\n')
        line[value2 - 1] = '\0';
        printf("line: [%s]\n", line);
        flag2++;

        flag1 = 0;
        free(tempStr1);
        free(line);
    } // while end

    printf("\n\n-----\ni= %d\n", i);
    printf("No of line: %d\n", flag2);
    fclose(allFiles);

    return 0;
}