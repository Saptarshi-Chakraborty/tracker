#include <stdio.h>
#include <string.h>

char *str_replace(char *, char *, char *);

void main()
{
    char str[50] = "Hello World";
    char old_str[10] = "World";
    char new_str[10] = "India";
    str_replace(str, old_str, new_str);
}

char *str_replace(char *fullString, char * searchString, char *replaceString){
    printf("Full String (%s)\n", fullString);
    printf("Search String (%s)\n", searchString);
    printf("Replace String (%s)\n", replaceString);
}