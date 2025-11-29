# Get Next Line (GNL) - C Implementation

## Overview
A C implementation of a custom `getline` function that reads input from standard input (stdin) line by line. This program demonstrates dynamic memory allocation and low-level file I/O operations in C.

## Table of Contents
- [Features](#features)
- [Compilation](#compilation)
- [Usage](#usage)
- [Code Explanation](#code-explanation)
- [File Structure](#file-structure)
- [Limitations](#limitations)
- [License](#license)

## Features
- Reads input from standard input line by line
- Dynamic memory allocation with proper cleanup
- Handles various input scenarios including empty lines and EOF
- Buffer-based reading for efficiency

## Compilation

### Prerequisites
- GCC compiler
- Unix-like operating system (for unistd.h)

### Compilation Command
```bash
gcc -o gnl gnl.c
```

## Usage

### Basic Usage
```bash
# Run the program
./gnl

# Then type input, press Enter for first line, then second line
Hello World
This is line two
```

### Example Output
```
 'Hello World'
 'This is line two'
```

## Code Explanation

### Header Files
```c
#include<stdio.h>    // Standard I/O functions (printf)
#include<stdlib.h>   // Memory allocation functions (malloc, free)
#include<unistd.h>   // POSIX API (read function)
```

### Constants and Helper Function
```c
#define BUFSIZE 2048  // Maximum buffer size for reading input

// Helper function to zero out memory buffer
char *zero(char *p){
    unsigned int n;
    for (n=0; n<BUFSIZE; *(p + n++)=0);  // Set each byte to 0
    return p;
}
```
The `zero` function initializes a memory buffer by setting all bytes to zero, preventing garbage values.

### Main GNL Function
```c
char *gnl(){
    unsigned int n;      // Character counter
    char *p, *s;         // Pointers for buffer manipulation
    int r;               // Read return value
    
    n = 0;
    s = p = malloc(BUFSIZE);  // Allocate memory for buffer
    zero(s);                   // Initialize buffer to zeros
```

**Function Logic:**
1. **Memory Allocation**: Allocates `BUFSIZE` bytes and initializes to zero
2. **Reading Loop**: Continuously reads one character at a time from stdin (file descriptor 0)
3. **Error Handling**: 
   - If read returns <1 (error or EOF) and no characters read, return NULL
   - If read returns <1 but characters were read, return the buffer
4. **Buffer Limits**: Prevents buffer overflow by checking `BUFSIZE-2`

### Character Processing
```c
switch(*p)
{
    case 0:           // Null terminator
    case '\n':        // Newline - end of line
        *p = 0;       // Replace with null terminator
        return s;     // Return the string
        break;

    case '\r':        // Carriage return
        *p = 0;       // Replace with null terminator
        break;        // Continue reading

    default:          // Regular character
        p++;          // Move pointer forward
        n++;          // Increment character count
}
```

**Character Handling:**
- **Null terminator (0) and Newline (\n)**: Mark end of line, return string
- **Carriage return (\r)**: Convert to null terminator but continue reading
- **Regular characters**: Add to buffer and continue

### Main Function
```c
int main(){
    char *p1, *p2;
    p1 = gnl();  // Read first line
    p2 = gnl();  // Read second line

    printf(" '%s'\n '%s'\n", p1, p2);

    free(p2);  // Free allocated memory
    free(p1);  // Free allocated memory
    return 0;
}
```

The main function demonstrates usage by:
1. Reading two lines of input
2. Printing both lines with quotes
3. Properly freeing allocated memory

## File Structure
```
gnl.c                 # Main source file containing all functions
├── Header includes
├── zero() function   # Buffer initialization
├── gnl() function    # Main line reading logic
└── main() function   # Demonstration and testing
```

## Limitations

1. **Fixed Buffer Size**: Limited to 2048 characters per line
2. **No Reallocation**: Doesn't handle lines longer than BUFSIZE gracefully
3. **Single Character Reads**: Inefficient for large inputs
4. **Limited Error Handling**: Basic error handling for read operations

## Potential Improvements

1. Dynamic buffer resizing for longer lines
2. Batch reading instead of single character reads
3. More robust error handling
4. Support for different file descriptors
5. Return line length information

## License
This code is provided for educational purposes. Feel free to modify and use as needed.

---

This implementation provides a basic but functional line-reading utility that demonstrates important C programming concepts including memory management, file I/O, and pointer manipulation.
