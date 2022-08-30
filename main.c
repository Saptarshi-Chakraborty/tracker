#include <stdio.h>
#include <direct.h>
#include <sys/types.h>

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
#define END_OF_FILE_STRING "\%--<__EOF>{END_OF_FILE}--=\%"
#define END_OF_FILE_PATH_STRING "0--<__EOFP>{END_OF_FILE_PATH}--=1"
#endif

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