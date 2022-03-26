#include <stdio.h>
#include <direct.h>
#include <sys/types.h>

// ---- Custom  Defines ----
#ifndef HOST_FOLDER_NAME
#define HOST_FOLDER_NAME ".text\\directory"
#define SAVE_FILE_NAME ".text\\directory\\all.txt"
#define SAVE_ONY_FILES ".text\\directory\\files.txt"
#define SAVE_ONY_FOLDERS ".text\\directory\\folders.txt"
#endif

//  Primary Function Declarations
void tracker_start();
int tracker_status();
int getDirectoryList(char *);

/* Utility Function Declarations */
int createFile(char *fileName);
int createFolder(char *folderName);
char *getFullPath(char *name);
int isFile(char *folderName);
int isFolder(char *folderName);
char *replaceWord(const char *fullString, const char *oldWord, const char *newWord);
int separate_File_Folder();
char *path_to_basename(char *path);

// ***  Main Function  ***
int main()
{
    printf("\n---------------------------------------------------\n");
    printf("Hello World\n");
    printf("\n---------------------------------------------------\n");
    return 0;
}

// Include Function Definitions
#include "primaryFunctions.c"
#include "utilityFunctions.c"