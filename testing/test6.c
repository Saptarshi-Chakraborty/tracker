#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <pthread.h>

void *myturn(void *arg)
{
    while (1)
    {
        sleep(1);
        printf("My Turn\n");
    }
    return NULL;
}

void yourturn()
{
    while (1)
    {
        sleep(2);
        printf("Your Turn\n");
    }
}

void main()
{
    printf("Hello World!\n");
    #ifdef _WIN32
    printf("-- You have Windows Operating System\n");
    #elif defined(__linux__)
    printf("-- You have Linux Operating System\n");
    #elif defined(__APPLE__)
    printf("-- You have Apple Operating System\n");
    #endif

    return;
    pthread_t newthread;

    pthread_create(&newthread, NULL, myturn, NULL);

    // myturn();
    yourturn();
}