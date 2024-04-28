# All Details about the Code

## Contents in this Page :

`(Click the below links to directly go to that section)`

1. [Header Files](#headers-files)
2. [Library Functions Used](#library-functions-used)
3. [Custom Functions](#custom-functions)
4. [Other Function](#other-functions)

---

## Headers Files

1. `<direct.h>`
   To use _\_mkdir()_ function [ not *mkdir()* ] we need this header file. We will use **_direct.h_** instead of **_dirent.h_** [ Only found in Linux ] in this program. The function in this header file [ like **_mkdir()** ] starts with a underscore[ \_ ].

2. `<dirent.h>`
   This header file is only found in **Linux System**. Need to use readdir() function to read the directory.

3. `<sys/types.h>`
   It is used to use the types of data in program

4. `<string.h>`
   Need this header file to Use the string related functions (like. strcpy,strcat etc).

5. `<stdlib.h>`
   Need this header file to Use the [**malloc()**](#library-functions-used) function in our cunstom-function [replaceWord()](#replaceword).

---

## Library Functions Used

- `_mkdir()`
  It is used to create a new folder in the current directory
- `_getcwd()`
  It is used to get the path current directory | **\_\_getcwd(path, sizeof(path))** gives us the path of current directory in the _path_ variable.
- `opendir()`
  It is used to open a directory (not to create).
- `readir()`
  It is used to read a directory, after opening it with _opendir_ , and get all file & folder names of that directory.
- `closedir()`
  It is used to close a directory.
- `strcmp()`
  It is used to remove a directory.
- `malloc()`
  It is used to allocate some memory to a variable. Normally used to allocate memory to a string pointer.
- `strcpy()`
  It is used to copy a string to another string variable/pointer.
- `strcat()`
  It is used to concatenate a string with another string variable/pointer.
- `strrchr()`
  It is used to get the last occurance of a character in a string.
- `fopen()`
  It is used to Open a file for writing or reading.
- `fprintf()`
  It is used to write formatted text [ like we do in _printf()_ ], in a file.
- `sprintf()`
  It is used to write formatted text [ like we do in _printf()_ ], in a string.

---

## Custom Functions

<!--
******* Format *******
### functionName()
>**`returnType functionName(arguments ...)`**\
>    Name with link if this function is similar to any other function. Then a long description about the function. After that describe @Return Value (if any).
-->

<!----------------  Primary  Functions ----------------->

### tracker_start()

> **`void tracker_start()`**\
>  Start the Tracker in current folder. It prints out if the Tracker is already started or, Started now or not.

### tracker_status()

> **`int tracker_status()`**\
>  Prints out if Tracker started or not in Current folder. Return, **0** - if Started already, **1** - if not Started.

### getDirectoryList()

> **`int getDirectoryList(char *foldername)`**\
>  Saves all the file & folder path of the given _foldername_ and it's sub-folders in [ `.text/directory/all.txt` ] . Return, **0** - if all saved successfully, **1** - if source folder(_foldername_) doesn't exists , **2** - if save folder does't exists or failed to access.

<!----------------  Utiity  Functions ----------------->

### createFile()

> **`int createFile(char *fileName)`**\
>  It is used to create a new file. It takes a file name (path) as an argument.

### createFolder()

> **`int createFolder(char *folderName)`**\
>  Similar to [createFile()](#createfile) . It is used to create a new folder in. It takes a folder name (path) as an argument.

### isFile()

> **`int isFile(char * filename)`**\
>  It is used to check if the file exist or not. It returns **0** if the file exists and **1** if the file does not exist.

### isFolder()

> **`int isFolder(char * foldername)`**\
>  Similar to [isFile()](#isfile) . It is used to check if the folder exist or not. It returns **0** if the folder exists and **1** if the folder does not exist.

### replaceWord()

> **`char *replaceWord(const char *fullString, const char *oldWord, const char *newWord)`**\
>  Used to replace all occurences of a specific word/character in a String with another word/character. @parameters, _fullString_ is the String of which the specific word would nbe replaced, _oldWord_ is the word/character to be replaced and _newWord_ is the new word/character which I want to put in the String.

### getFullPath()

> **`char *getFullPath(char *name)`**\
>  Takes file/foldername as @parameter. @returns full path of that file/folder in **path\to\folder\file** format.

### separate_File_Folder()

> **`int separate_File_Folder()`**\
>  It reads the **.text/directory/all.txt** file and separates File & Folder paths in two different files, **.text/directory/file.txt** and **.text/directory/folder.txt** correspondingly.

### path_to_basename()

> **`char *path_to_basename(char *path)`**\
>  It is used to get the base file/folder name of the given path. It takes a path as @parameter and returns the origina filename/foldername.

### itrateAllFiles()

> **`void itrateAllFiles()`**\
>  It is the driver function to start reading the commit file and call the _generateAllFolders()_ & _writeFileContent()_ functions sequentially.

### keyboardNavigatorMenu()

> **`int keyboardNavigatorMenu(char **\_options, int \_numberOfOptions)`\*\*\
>  This function creates a menu with the given options where user can navigate using the arrow keys and select the option using the Enter key of the keyboard. It takes the options and the number of options as @parameters. It @returns the index of the selected option.

---

## Other Functions

- `rmdir()`
  It is used to remove a folder in the current directory
- `chdir()`
  It is used to change the current directory
- `chmod()`
  It is used to change the permission of a file
- `chown()`
  It is used to change the owner of a file
- `chgrp()`
  It is used to change the group of a file
- `stat()`
  It is used to get the information of a file
- `lstat()`
  It is used to get the information of a symbolic link
- `fstat()`
  It is used to get the information of a file descriptor
- `access()`
  It is used to check the permission of a file
- `utime()`
  It is used to change the access and modification time of a file
- `readlink()`
  It is used to get the symbolic link of a file
- `symlink()`
  It is used to create a symbolic link
- `link()`
  It is used to create a hard link
- `unlink()`
  It is used to remove a file
- `rename()`
  It is used to rename a file
- `truncate()`
  It is used to truncate a file
- `ftruncate()`
  It is used to truncate a file descriptor
- `readdir_r()`
  It is used to get the list of files in a directory
- `fsync()`
  It is used to synchronize a file with the underlying storage device
- `fdatasync()`
  It is used to synchronize a file with the underlying storage device
- `sync()`
  It is used to synchronize the entire file system
- `fstatfs()`
  It is used to get the file system statistics
- `statfs()`
  It is used to get the file system statistics
