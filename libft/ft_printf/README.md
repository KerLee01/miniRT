*This project has been created as part of the 42 curriculaum by kerlee.*

## Description
This project is **ft_printf** is a custom implementation of the C standard librray function "printf". This project focuses on the implementation of **variadic functions**, **struct-based state management** and **low_level buffer manipulation**.

## Instructions
**The libft project is not utilized in this project.**

The project utilizes a **Makefile** with standard rules:

```
make            # Compiles the library libftprintf.a
make bonus      # Compiles with bonus flags
make clean      # Removes object files
make fclean     # Removes object files and the library
make re         # Recompiles everything

```
## Prerequisites
- GCC or Clang compiler
- Make

## Compilation
You can make your own test file and run it with :
    cc -Wall -Wextra -Werror <your_test_file.c> libftprintf.a <program_name>
    ./<program_name>

or you can use this main.c file

and run it with :
    cc -Wall -Wextra -Werror main.c libftprintf.a
    ./a.out

## Resources
- Man pages
- AI :
        > Used to provide insight for idea of tackling the project.
          (Example: "AI is asked if using write to write each character would be more feasible or a (char *)buffer with an allocated stack size is used and flushed when filled is better. The AI gives information for both implementations and assures that a buffer with allocated stack size is better. I tackle the project using a buffer with allocated stack size.)

        > To obtain information of which flags are implemented on which specifiers and how precision and widths affect the specifier format.

***AI Policy: AI tools were used solely for conceptual understanding (e.g., comparing write syscall overhead vs. buffering) and documentation structure. No AI-generated code was used in the final compilation.**

## Testing 
1. Francinette
2. Manual Edge Case (Tests for INT_MIN, NULL)
3. Memory Analysis (No leaks on Valgrind)

## Directory Structure
```
.
├── Makefile
├── README.md  
├── ft_printf.c          # Main entry point & Variadic logic
├── ft_printf_utils.c    # Helper functions used in ft_printf.c
├── ft_printf.h          # Header file (Structs & Prototypes)
└── specifier_handlers/  # Modular handlers for each type
    ├── c_handler.c
    ├── s_handler.c
    ├── p_handler.c
    ├── i_d_handler.c
    ├── u_handler.c
    ├── x_X_handler.c
    └── specifier_utils.c   # Helper functions for specifiers
├── ft_printf_bonus.c          # Main entry point & Variadic logic for bonus part
├── ft_printf_utils_bonus.c    # Helper functions used in ft_printf_bonus.c
├── ft_printf_bonus.h          # Header file (Structs & Prototypes) for bonus part
└── specifier_handlers_bonus/  # Modular handlers for each type
    ├── c_handler_bonus.c
    ├── s_handler_bonus.c
    ├── p_handler_bonus.c
    ├── i_d_handler_bonus.c
    ├── u_handler_bonus.c
    ├── x_X_handler_bonus.c
    └── specifier_utils_bonus.c   # Helper functions for specifiers

**The contents of the bonus files are similar to the mandatory parts. (The bonuses were taken into consideration from the start of the project)**
```
### Additional Information
The program utilizes a 4KB stash array (seen in t_data struct in ft_printf.h) instead of writing out each char by char. This is for three reasons:

1. **Performance (System Calls)**

    When the write character is used to print every char found, the CPU switches from User mode to Kernel mode for every single byte making it incredibly slow. Hence, usin
    the stash array of 4096 bytes and flushing it when it fills up, the write function is only called once every 4096 characters (only one switch from User mode to Kernel mode once eveyr 4096 bytes) speeding up the project for large outputs.

2. **Algorithmic Complexity**

    Using malloc requires us to know the array length before hand, meaning the program would have to pass the same information twice. Once to count the length, second to malloc it. By using the stash array, the program will just have to fill up the stash array and flush it when it fills up. after, the program am still able to reuse it again. It handles infinite data!

3. **Memory Safety**

    Refering to point #2, we know that there are multiple steps to obtain the perfect malloc data. First, the OS has to search for a free block, this requires time. Malloc also has a failure isk which it can return NULL. We have to clean up the memory after using, else there will be a memory leak. BUT when a stash array is used, it is stored in the stack, it is instantly allocated, no failure risk and the cleanup is automatic! This means the program significantly reduce the amount of bugs in the project, saving time as well. 

In conclusion, using a stash array, the program turns from a Two-Pass Algorithm to a ONE-Pass Algorithm is memory-safe and highly optimized.

## More Information On Variables in the Struct

In the struct, the stash is used to store bytes read from the format string and has a size of 4096 which is the standard size of a Linux page. Each time the struct is full, the data it holds is flushed and the index resets to 0. The index is monitored using current_byte.

Boolean variables are used for each flags (#, (space), -, +) except 1. The variables are initialised to false and set to true when the specified flag is encountered. The variable for 0 flag is a char which will be set to 0 if the flag is encountered and initialised as (space). The variables are used in the specifier handlers only when it applies to the specific specifier. 

Integer variables are used for width and precision. A boolean variable called precision_set is used as precision is initialised to 0 and if precision of 0 is present in the format, it is handled differently. Precision_set helps us differenciate that.

The variable total_bytes is used to accumulate all the bytes read and returned as the return value of ft_printf.
