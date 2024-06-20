# Get Next Line

The `get_next_line` project involves writing a function that reads a line from a file descriptor, returning the line read. The goal of the project is to The get_next_line project is to practice file I/O, use of linked lists and memory management in C.

## Table of Contents
- [Function Prototypes](#functionprototypes)
- [Usage](#usage)
- [Important Considerations](#importantconsiderations)
  
## Function Prototype

```c
char *get_next_line(int fd);
```
The get_next_line function reads from a file descriptor fd and returns the next line read from the file. Each call to get_next_line returns a new line until the end of the file is reached. 
### Parameters
int fd: The file descriptor to read from.
### Return Value
Returns the next line read from the file descriptor.
Returns NULL if there is nothing more to read or an error occurs.


## Usage
Include the Header: Ensure you include the get_next_line.h header in your source files.
```sh
#include "get_next_line.h"
```
Compile the Source Files: Compile get_next_line.c and get_next_line_utils.c along with your main program.
```sh
gcc -Wall -Wextra -Werror -Iincludes -c srcs/get_next_line.c srcs/get_next_line_utils.c my_program.c
```
Here is an example of using the get_next_line function in a simple program:
```sh
#include <fcntl.h>
#include <stdio.h>
#include "get_next_line.h"

int main(void)
{
    char *line;
    int fd;

    fd = open("example.txt", O_RDONLY);
    if (fd == -1)
        return (1);
    while ((line = get_next_line(fd)) != NULL)
    {
        printf("%s\n", line);
        free(line);
    }
    close(fd);
    return (0);
}
```
## Important Considerations
### Memory Management:
Each call to get_next_line allocates memory for the line returned. It is the responsibility of the caller to free this memory to avoid memory leaks.
### Buffer Size: 
The buffer size can be defined in the get_next_line.h file. Make sure to choose an appropriate buffer size for your needs.
