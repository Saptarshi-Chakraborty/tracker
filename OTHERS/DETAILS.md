# All Details about the Code

## Headers

1. `<direct.h>`
   To use _\_mkdir()_ function [ not *mkdir()* ] we need this header file. We will use **_direct.h_** instead of **_dirent.h_** [ Only found in Linux ] in this program. The function in this header file [ like **_mkdir()** ] starts with a underscore[ \_ ].

2. `<dirent.h>`
   This header file is only found in **Linux System**. For windows, we will use _<direct.h>_ as a replacement.

3. `<sys/types.h>`
   It is used to use the types of data in program

---

## Functions Used

- `_mkdir()`
  It is used to create a new folder in the current directory
- `_getcwd()`
  It is used to get the path current directory | **\_\_getcwd(path, sizeof(path))** gives us the path of current directory in the _path_ variable.

---

## Custom Functions

<!--
******* Format *******
### functionName()
>`functionName(arguments ...)`\
>    Name with link if this function is similar to any other function. Then a long description about the function. After that describe @Return Value (if any).
-->


### createFile()
>`int createFile(char *fileName)`\
>    It is used to create a new file. It takes a file name (path) as an argument.

### createFolder()
>`int createFolder(char *folderName)`\
>    It is used to create a new folder in. It takes a folder name (path) as an argument.

### isFile()

> `int isFile(char * filename)`\
>  It is used to check if the file exist or not. It returns **0** if the file exists and **1** if the file does not exist.

### isFolder()

> `int isFolder(char * foldername)`\
>  Similar to [isFile()](#isfile) . It is used to check if the folder exist or not. It returns **0** if the folder exists and **1** if the folder does not exist.

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
- `readdir()`
  It is used to get the list of files in a directory
- `opendir()`
  It is used to open a directory
- `closedir()`
  It is used to close a directory
- `readdir_r()`
  It is used to get the list of files in a directory
- `readdir_r()`
  It is used to get the list of
