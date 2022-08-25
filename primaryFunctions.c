#include <stdio.h>
#include <stdlib.h>
#include <dirent.h> // use this for directory traversal
#include <sys/types.h>

#include "utilityFunctions.c" //may need this to use utility functions in primary functions

// ---- Custom  Defines ----
#ifndef SAVE_FOLDER_NAME
#define SAVE_FOLDER_NAME ".text\\directory"
#define SAVE_FILE_NAME ".text\\directory\\all.txt"
#endif

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