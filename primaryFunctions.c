#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> // use this for directory traversal
#include <sys/types.h>

#include "utilityFunctions.c" //may need this to use utility functions in primary functions

#include "defines.h" // Custom Defines

void primaryFunctions(void)
{
    printf("This is 'primaryFunctions.c' file\n");
}

// Function to initialize the tracker in current folder
void tracker_start()
{
    if (isFolder(".text") == 0)
        printf("Tracker already running\n");
    else
    {
        if (createFolder(".text") == 0)
            printf("Tracker started in the current folder\n");
        else
            printf("Failed to start Tracker. Please give \"Admistration Permission\" to this file\n");
    }
}

// Function to check if Tracker is started or Not
int tracker_status()
{
    if (isFolder(".text") == 0)
    {
        printf("Tracker Running in this Folder\n");
        return 0;
    }
    else
    {
        printf("This folder is Not Tracking\n");
        return 1;
    }
}

// save all filename/foldername in current directory
// @rerturn 0-if Saved Successfully, 1-if source folder doesn't exist, 2-if save folder doesn't exist or failed to access
int getDirectoryList(char *foldername)
{
    DIR *dir;
    struct dirent *element;
    char *getFolder = foldername, *saveFolder = SAVE_FOLDER_NAME;
    char primaryPath[250], tempName[250]; // tempName for foldernames
    FILE *all, *files, *folders;
    int isRootFolder = (strcmp(getFolder, ".") == 0) ? 0 : 1;

    if (isFolder(getFolder) == 1) // if Source folder don't exist
        return 1;

    if (isFolder(saveFolder) == 1) // if Save folder don't exist
        return 2;

    if ((dir = opendir(getFolder)) == NULL) // if failed to access Save folder
        return 2;
    else
    {
        while ((element = readdir(dir)) != NULL)
        {
            all = fopen(SAVE_FILE_NAME, "a");
            if ((strcmp(element->d_name, ".") != 0) && (strcmp(element->d_name, "..") != 0))
            {
                if (isRootFolder == 1)
                {
                    strcpy(primaryPath, getFolder);
                    strcat(primaryPath, "/");
                    strcat(primaryPath, (element->d_name));
                }
                else
                    strcpy(primaryPath, (element->d_name));
                // printf("=> (%s)\n", primaryPath);

                if (isFolder(primaryPath) == 0)
                {
                    if ((strcmp(getFolder, ".") != 0) && (strcmp(getFolder, "..") != 0))
                        strcpy(tempName, primaryPath);
                    else
                        strcpy(tempName, (element->d_name));
                    strcat(tempName, "/");
                    fprintf(all, "%s\n", tempName);

                    getDirectoryList(primaryPath);

                    // printf(">> It is a folder => %s\n>> call gdl (%s) = %d\n", primaryPath,primaryPath, getDirectoryList(primaryPath));
                }
                else
                    fprintf(all, "%s\n", primaryPath);

                strcpy(primaryPath, "");
            }
            fclose(all);
        }
        return 0;
    }
}

// Extract basename of files & folders and save in files
// @returns, 0-Success ;1-File of pathnames not found ;2-failed to read file ; 3-failed to create files
int save_basename()
{
    FILE *files, *folders, *filename, *foldername;
    char line[260], ch;
    int i;

    if ((isFile(SAVE_ONY_FILES) == 1) || (isFile(SAVE_ONY_FOLDERS) == 1))
        return 1;

    files = fopen(SAVE_ONY_FILES, "r");
    folders = fopen(SAVE_ONY_FOLDERS, "r");
    if (files == NULL || folders == NULL)
        return 2;

    filename = fopen(SAVE_ONY_FILES_BASENAME, "w");
    foldername = fopen(SAVE_ONY_FOLDERS_BASENAME, "w");
    if (filename == NULL || foldername == NULL)
        return 3;

    // Extract Filenames
    i = 0;
    while (ch != EOF)
    {
        ch = fgetc(files);
        if ((ch != '\n') && (ch != '\n'))
            line[i++] = ch;

        if (ch == '\n')
        {
            if (i >= 1)
                line[i] = '\0';

            i = 0;
            // Now Line is ready to be processed
            fprintf(filename, "%s\n", path_to_basename(line));
        }
    }

    // Extract Foldernames
    i = 0;
    strcpy(ch, "");
    while (ch != EOF)
    {
        ch = fgetc(folders);
        if ((ch != '\n') && (ch != '\n'))
            line[i++] = ch;

        if (ch == '\n')
        {
            if (i >= 1)
                line[--i] = '\0'; // as fodlerpath ends with "/" so we need to remove it, --so decrement i

            i = 0;
            // Now Line is ready to be processed
            fprintf(foldername, "%s\n", path_to_basename(line));
        }
    }

    fclose(files);
    fclose(folders);
    fclose(filename);
    fclose(foldername);

    return 0;
}

// Writes all file contents in one file
//  @returns 0-success
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


/**
 * @brief Reads the draft file and performs necessary operations.
 * 
 * @return int Returns 0 on success.
 */
int readDraftFile()
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

            commitfile = regenerateFile(commitfile, filename);

            // break;
            continue;
        }
    }

    fgets(line, LINE_SIZE, commitfile);
    printf("Line : [%s]\n", line);
    fgets(line, LINE_SIZE, commitfile);
    printf("Line : [%s]\n", line);

    fclose(commitfile);

    return 0;
}



/**
 * Regenerates all folders based on the file contents.
 *
 * @param file A file pointer denoting the start of the content of folder list.
 * @return A pointer to the file after processing the folder paths, or NULL if an error occurs.
 */
FILE *regenerateAllFolders(FILE *file)
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

    return NULL;
}