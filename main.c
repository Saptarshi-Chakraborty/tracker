#include <stdio.h>
#include <direct.h>
#include <sys/types.h>

#include "defines.h" // Custom Defines

//  Primary Function Declarations
void tracker_start();
int tracker_status();
int getDirectoryList(char *);
int save_basename();
int makedraft();

/* Utility Function Declarations */
int createFile(char *fileName);
int createFolder(char *folderName);
char *getFullPath(char *name);
int isFile(char *folderName);
int isFolder(char *folderName);
char *replaceWord(const char *fullString, const char *oldWord, const char *newWord);
int separate_File_Folder();
char *path_to_basename(char *path);
int isFileTracking(char *filename);
int isFolderTracking(char *foldername);
int draft_all_file_path();
int writeFileContent(char *);

// ***  Main Function  ***
int main()
{
    printf("\n---------------------------------------------------\n");
    printf("Hello World\n");
    char *path = ".text/directory/all.txt";
    printf("isFileTracking [%s] => %d\n", path, isFileTracking(path));
    printf("\n---------------------------------------------------\n");
    return 0;
}

// Include Function Definitions
#include "primaryFunctions.c"
#include "utilityFunctions.c"