#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <dirent.h>
#include <direct.h>
#include <sys/types.h>

#define HOST_FOLDER_NAME ".data"
#define SAVE_FILE_NAME ".data\\all.txt"

int isFolder(char *folderName);
int getDirectoryList(char *);
int createFolder(char *folderName);

main()
{
    if (isFolder(HOST_FOLDER_NAME) == 1)
        createFolder(HOST_FOLDER_NAME);

    printf("\n>> getDirectoryList = %d\n", getDirectoryList("."));
    // printf("\n>> getDirectoryList = %d\n", getDirectoryList("OTHERS"));
    // printf("%d\n", isFolder("source"));
}

// save all filename/foldername in current directory
int getDirectoryList(char *foldername)
{
    DIR *dir;
    struct dirent *element;
    char *getFolder = foldername, *saveFolder = HOST_FOLDER_NAME;
    char primaryPath[250], tempName[250]; // tempName for foldernames
    FILE *all, *files, *folders;
    int isRootFolder = (strcmp(getFolder, ".") == 0) ? 0 : 1;

    printf("--- getDirList called for (%s), isRootFolder (%d) ----\n", getFolder, isRootFolder);
    if (isFolder(getFolder) == 1) // if Source folder don't exist
        return 1;

    if (isFolder(saveFolder) == 1) // if Save folder don't exist
        return 2;

    if ((dir = opendir(getFolder)) == NULL) // if failed to access Save folder
        return 3;
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

                printf("=> (%s)\n", primaryPath);

                if (isFolder(primaryPath) == 0)
                {
                    if ((strcmp(getFolder, ".") != 0) && (strcmp(getFolder, "..") != 0))
                        strcpy(tempName, primaryPath);
                    else
                        strcpy(tempName, (element->d_name));
                    strcat(tempName, "/");
                    fprintf(all, "%s\n", tempName);

                    printf(">> It is a folder => %s\n", primaryPath);
                    printf(">> call gdl (%s) = %d\n", primaryPath, getDirectoryList(primaryPath));
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

// Function to check if a folder exists
int isFolder(char *folderName)
{
    DIR *dir;
    char path[200];
    _getcwd(path, sizeof(path));
    strcat(path, "\\");
    strcat(path, folderName);
    // printf("-- isFolder Path is [%s]\n", path);
    if ((dir = opendir(path)) != NULL)
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