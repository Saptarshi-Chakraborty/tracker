#include <stdio.h>
// #include "utilityFunctions.c" //may need this to use utility functions in primary functions

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
