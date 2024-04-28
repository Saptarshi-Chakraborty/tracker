#include <stdio.h>
#include <stdlib.h>
#include <string.h>

char *createHash(char *);

int main()
{
    char filepath[100] = "createHash.c";
    char *hash = createHash(filepath);
    printf("Hash: [%s]\n", hash);
    free(hash);
    return 0;
}

char *createHash(char *filepath)
{

    char command[200];
    sprintf(command, "certutil -hashfile \"%s\" MD5", filepath);

    FILE *fp;
    char buffer[1035];

    // Open the command for reading
    fp = popen(command, "r");
    if (fp == NULL)
    {
        printf("Failed to run command\n");
        exit(1);
    }

    int flag = 0;

    // Read the output a line at a time
    while (fgets(buffer, sizeof(buffer), fp) != NULL)
    {
        // Print each line to stdout
        // printf("--| %s", buffer);

        if (buffer[0] == 'M' && buffer[1] == 'D' && buffer[2] == '5')
        {
            flag = 1;
            continue;
        }

        if (flag == 1)
        {
            pclose(fp);

            char *hash = (char *)malloc(33 * sizeof(char));
            strncpy(hash, buffer, 32);
            hash[32] = '\0';
            return hash;
        }
    }

    // Close the pipe
    pclose(fp);

    return NULL;
}
