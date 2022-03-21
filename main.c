#include <stdio.h>
#include <direct.h>
#include <sys/types.h>

#include "primaryFunctions.c"
#include "utilityFunctions.c"

//  Primary Function Declarations
void tracker_start();

/* Utility Function Declarations */
int createFile(char *fileName);
int createFolder(char *folderName);
int isFile(char *folderName);
int isFolder(char *folderName);
char *replaceWord(const char *fullString, const char *oldWord, const char *newWord);

// ***  Main Function  ***
int main()
{
    printf("\n---------------------------------------------------\n");
    printf("Hello World\n");
    printf("\n---------------------------------------------------\n");
    return 0;
}