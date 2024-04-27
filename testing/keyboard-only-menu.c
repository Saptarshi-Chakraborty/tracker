#include <stdio.h>
#include <conio.h>
#include <string.h>
#include <stdlib.h>

#if defined(_WIN32) || defined(_WIN64)
#define _CLEAR_TERMINAL_ system("cls");
#elif defined(__linux__) || defined(__APPLE__)
#define _CLEAR_TERMINAL_ system("clear");
#endif

// int keyboardNavigatorMenu(char **, int);

/// @brief Keyboard navigator menu that allows the user to navigate through a list of options using arrow keys and select an option with the Enter key.
/// Example: keyboardNavigatorMenu((char *[]){"HELLO", "WORLD"}, 2);
/// @param _options A pointer to an array of strings representing the options in the menu.
/// @param _numberOfOptions The number of options in the menu.
/// @return The index of the selected option
int keyboardNavigatorMenu(char **_options, int _numberOfOptions)
{
    char ch = 0, k = 0;
    int currentOption = 0, i;

    while (1)
    {
        _CLEAR_TERMINAL_
        for (i = 0; i < _numberOfOptions; i++)
        {
            // green color text start
            if (i == currentOption)
                printf("\033[0;32m");

            printf("%s", (currentOption == i) ? ">>" : "  ");
            printf(" %s ", *(_options + i));
            printf("%s", (currentOption == i) ? "<<" : "  ");
            printf("\n");

            // green color text end
            if (i == currentOption)
                printf("\033[0m");
        }

        fflush(stdin);
        ch = getch();

        if (ch == 13) // Enter key
        {
            break;
        }
        else if (ch == 72) // Up Arrow key
        {
            currentOption = (currentOption == 0) ? (_numberOfOptions - 1) : currentOption - 1;
        }
        else if (ch == 80) // Down Arrow key
        {
            currentOption = (currentOption == _numberOfOptions - 1) ? 0 : currentOption + 1;
        }
    }

    return currentOption;
}

int main()
{
    printf("\nHello World from main()\n\n");
    char *menu[] = {"Rectangle", "Circle", "Square", "EXIT"};
    int a;

    a = keyboardNavigatorMenu(menu, 4);

    printf("\na = (%d)\n", a);
    return 0;
}