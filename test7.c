#include <stdio.h>
#include <stdlib.h>
#include <string.h>

void explode(char *path, char *name)
{
    printf("START : path[%s]\n", path);
    printf("START : name[%s]\n", name);

    char *subString;
    char *part;
    int mainLength, subStringLength, partLength;

    mainLength = strlen(path);
    subString = malloc(partLength);

    strcpy(subString, path);
    printf("subString [%s]\n", subString);

    part = strtok(subString, "/");
    printf("part [%s]\n", part);

    char *token = strtok(path, "/");

    printf("token is [%s]\n", token);

    while (token != NULL)
    {
        printf("token = [%s]\n", token);
        token = strtok(NULL, "/");
    }
}

void main()
{
    char *str = "Hello World";
    char *token;
    char delim[2] = " ";

    printf("\n\n\n---------------------------------------------------------\n");
    printf("Hello World\n");

    char path[] = ".text/directory/all.txt";
    // char path[] = ".textXdirectoryXall.txt";
    char name[] = ".text";
    explode(path, name);

    printf("\n---------------------------------------------------------\n\n\n");
}
