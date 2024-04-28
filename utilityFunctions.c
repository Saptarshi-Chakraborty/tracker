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
#define ALL_FILE_LIST ".text/directory/files.txt"
#define DRAFT_FILE_NAME "__draft__"
#define LINE_SIZE 1000
#define END_OF_FILE_STRING "1--<__EOF>{END_OF_FILE}--=3"
#define END_OF_FILE_PATH_STRING "0--<__EOFP>{END_OF_FILE_PATH}--=1"
#define END_OF_FOLDER_PATH_STRING "0--<__EOFOP>{END_OF_FOLDER_PATH}--=1"
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

// write all tracking file paths in 'draft' file from [.text/directory/files.txt]
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

// Writes content of given file path in 'draft' file
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

FILE *regenerateFile(FILE *file, char filepath[])
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

    return NULL;
}

/// @brief Keyboard navigator menu that allows the user to navigate through a list of options using arrow keys and select an option with the Enter key.
/// Example: keyboardNavigatorMenu((char *[]){"HELLO", "WORLD"}, 2);
/// @param _options A pointer to an array of strings representing the options in the menu.
/// @param _numberOfOptions The number of options in the menu.
/// @return The index of the selected option
int keyboardNavigatorMenu(char **_options, int _numberOfOptions)
{
    char ch = 0, k = 0;
    int currentOption = 0, i;

    while (1)
    {
#ifdef _WIN32 // Windows
        system("cls");
#else // Linux or Mac
        system("clear");
#endif

        for (i = 0; i < _numberOfOptions; i++)
        {
            // green color text start
            if (i == currentOption)
                printf("\033[0;32m");

            printf("%s", (currentOption == i) ? ">>" : "  ");
            printf(" %s ", *(_options + i));
            printf("%s", (currentOption == i) ? "<<" : "  ");
            printf("\n");

            // green color text end
            if (i == currentOption)
                printf("\033[0m");
        }

        fflush(stdin);
        ch = getch();

        if (ch == 13) // Enter key
        {
            break;
        }
        else if (ch == 72) // Up Arrow key
        {
            currentOption = (currentOption == 0) ? (_numberOfOptions - 1) : currentOption - 1;
        }
        else if (ch == 80) // Down Arrow key
        {
            currentOption = (currentOption == _numberOfOptions - 1) ? 0 : currentOption + 1;
        }
    }

    return currentOption;
}

#endif // file include endif