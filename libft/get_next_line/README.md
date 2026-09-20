*This project has been created as part of the 42 curriculaum by kerlee.*

## Description
This project is **get_next_line**. This project focuses on the implementation of **static variables** in C language.

## Instructions

You can make your own test file and run it with:
	cc -Wall -Wextra -Werror <your_test_file.c> get_next_line.c get_next_line_utils.c <program_name>
	./<program_name>
or for bonuses
	cc -Wall -Wextra -Werror <your_test_file.c> get_next_line_bonus.c get_next_line_utils_bonus.c <program_name>
        ./<program_name>

## Prerequisites
- GCC or Clang compiler

## Resources
- Man pages
- AI : 
	> Used to provide insight for idea of solving the project.
	(Example: A static array was first used to store the file descriptors, hence the size of the array was hardcoded. AI gave the recommendation to use a linked list to store the filde descriptors so infinite amount of file descriptors can be stored. The logic is used in this project.)

## Testing
1. Francinette
2. Memory Analysis (No leaks on Valgrind)
3. Manual Edge Cases (e.g `BUFFER_SIZE` = 1, 4096, 10000000) and when there are no newlines in the file, empty file, or multiple newlines. 

## Directory Structure
```
.
├── get_next_line_bonus.c
├── get_next_line_bonus.h
├── get_next_line.c
├── get_next_line.h
├── get_next_line_utils_bonus.c
├── get_next_line_utils.c
└── README.md

```

# Additional Information
The program utilizes a linked list in order to take in unlimited amount of file descriptors compared to a fixed array. A new node is created for every new file descriptor introduced to the list and when the file descriptor already exists, the existing node is used. The linked list is set as static to hold the data until the program is done executing so that data from each call of `get_next_line` is preserved such as bytes read that are not printed or data of nodes of another file descriptor.

The program starts with the `get_next_line` function which take a parameter fd. The function first searches the linked list to match fd to the each node's fd. After, it calls the `read_more` function to read the contents of the file into the stash of the node until a newline is found.

The key in the `read_more` function lies in the `allocate_buffer` function where a memory pool is created. (A memory pool is when a huge amount of memory is allocated from the start and the memory area is gets filled up bit by bit after.) Each time `allocate_buffer` is called, it checks of the amount of memory is enogh to hold `BUFFER_SIZE` + `stash_length` (the maximum amount of bytes that will be read for the next call to read() and the length of stash.). If the size is less than or equal to , the memory pool expands twice as much. This created more memory area for a lot of future calls to read(), preventing the program from calling malloc() too often. 

This is because malloc calls are expensive. Every call to malloc, malloc searches through the heap for a free memory space that matches the amount of memory requested. malloc is also a system call, hence, every call to malloc, the program switches from User mode to Kernel mode which is computationally expensive. 

After the node's stash is filled by `read_more()`. The `find_line` function is called in order to find the first line in the stash. 

After `update_stash` function is used to update the stash. The stash will now contain the bytes read that are not returned by the function and will be used in the next `get_next_line` function call.
