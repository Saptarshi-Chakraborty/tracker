#include <stdio.h>
#include <string.h>

#ifndef HOST_FOLDER_NAME
#define HOST_FOLDER_NAME ".text\\directory"
#define SAVE_FILE_NAME ".text\\directory\\all.txt"
#define SAVE_ONY_FILES ".text\\directory\\files.txt"
#define SAVE_ONY_FOLDERS ".text\\directory\\folders.txt"
#endif

int separate_File_Folder();

int main()
{
  printf("@return = %d\n", separate_File_Folder());
  return 0;
}

int separate_File_Folder()
{
  FILE *all, *files, *folders;
  char line[260], ch;
  int num_of_lines = 0, i;

  printf("separate_File_Folder()\n");

  all = fopen(SAVE_FILE_NAME, "r");
  if (all == NULL)
    return 1;

  i = 0;
  files = fopen(SAVE_ONY_FILES, "w");
  folders = fopen(SAVE_ONY_FOLDERS, "w");
  while (ch != EOF)
  {
    ch = fgetc(all);
    if ((ch != '\n') && (ch != '\n'))
      line[i++] = ch;

    if (ch == '\n')
    {
      if (i >= 1)
        line[i] = '\0';

      i = 0;
      // Now Line is ready to be processed
      if (isFile(line) == 0)
      {
        printf("File : (%s)\n", line);
        fprintf(files, "%s\n", line);
      }
      else if (isFolder(line) == 0)
      {
        printf("Folder : (%s)\n", line);
        fprintf(folders, "%s\n", line);
      }
      else
      {
        printf("Unknown : (%s)\n", line);
        fprintf(files, "%s\n", line);
      }
    }
  }
  if (line >= 1)
    line[--i] = '\0';

  fclose(all);
  fclose(files);
  fclose(folders);
  return 0;
}

// #include "utilityFunctions.c"