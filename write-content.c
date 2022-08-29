#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>

#define ALL_FILE_LIST ".text/directory/files.txt"
#define DRAFT_FILE_NAME "__draft__"
#define LINE_SIZE 1000
#define END_OF_FILE_STRING "\%--<__EOF>{END_OF_FILE}--=\%"
#define END_OF_FILE_PATH_STRING "0--<__EOFP>{END_OF_FILE_PATH}--=1"

// Function Declaration
int writeFileContent(char *);
int makedraft();

int main()
{
    printf("Hello World\n");

    // draft_all_file_path();
    makedraft();

    printf("\n---- program end ---- \n");
    return 0;
}

#ifdef testing
int test()
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

int makedraft()
{
    FILE *allFiles;
    char *fileName = ALL_FILE_LIST;
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

    // write all the files paths in draft file
    draft_all_file_path();


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

        writeFileContent(line);

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

// int writeFileContent(char *ch)
int writeFileContent(char *file)
{
    FILE *fp, *target_file;
    char ch;

    fp = fopen(DRAFT_FILE_NAME, "a");
    target_file = fopen(file, "r");
    if (target_file == NULL)
    {
        perror("Failed to open target file");
        exit(EXIT_FAILURE);
    }

    fprintf(fp, "\nF:%s\n", file);

    while (1)
    {
        ch = fgetc(target_file);
        if (ch == EOF)
            break;

        fputc(ch, fp);
    }

    fprintf(fp, "\n%s", END_OF_FILE_STRING);
    fputc('\n', fp);

    fclose(fp);
    fclose(target_file);
}

int draft_all_file_path()
{
    FILE *allFiles, *draft;
    char *fileName = ALL_FILE_LIST;
    char buffer[LINE_SIZE], *line, *tempStr1, *tempStr2;
    int bufferLength, i = 0;
    int flag1, flag2, flag3;
    int value1, value2;

    bufferLength = sizeof(buffer);
    allFiles = fopen(fileName, "r");
    if (allFiles == NULL)
    {
        perror("File not opened");
        exit(EXIT_FAILURE);
    }

    draft = fopen(DRAFT_FILE_NAME, "w");

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
        line[value2 - 1] = '\0';

        printf("file path: [%s]\n", line);
        fprintf(draft, line);
        fputc('\n', draft);

        flag2++;
        flag1 = 0;
        free(tempStr1);
        free(line);
    } // while end

    fprintf(draft, END_OF_FILE_PATH_STRING);
    fputc('\n', draft);
    fputc('\n', draft);

    fclose(allFiles);
    fclose(draft);

    return 0;
}