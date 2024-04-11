# LinkListBrainfuck
Normal Brainfuck but made with linkedList.<br />
My first linkedList project.

# Download
```bash
$ git clone https://github.com/Atduyar/LinkListBrainfuck.git
$ cd LinkListBrainfuck
```
## Build
```bash
$ premake5 gmake2
$ make
# or you can build without premake
$ make -f Makefile.linux
```
## Start test run
```
$ ./bin/Release/bf -s 25
```
# Brainfuck overview
Brainfuck operates on an array of memory cells, each initially set to zero. (In the original implementation, the array was 30,000 cells long, but this may not be part of the language specification; different sizes for the array length and cell size give different variants of the language). There is a pointer, initially pointing to the first memory cell. The commands are:
| Brainfuck   | C                     | description                                                         |
|:-----------:|-----------------------|---------------------------------------------------------------------|
| `>`         | `++ptr;`              | Move the pointer to the right                                       |
| `<`         | `--ptr;`              | Move the pointer to the left                                        |
| `+`         | `++*ptr;`             | Increment the memory cell at the pointer                            |
| `-`         | `--*ptr;`             | Decrement the memory cell at the pointer                            |
| `[`         | `while (*ptr) {`      | Output the character signified by the cell at the pointer           |
| `]`         | `}`                   | Input a character and store it in the cell at the pointer           |
| `.`         | `putchar(*ptr);`      | Jump past the matching ] if the cell at the pointer is 0            |
| `,`         | `ptr[0] = getchar();` | Jump back to the matching [ if the cell at the pointer is nonzero   |

All characters other than ><+-.,[] should be considered comments and ignored.

# Usage
## Run
```bash
$ ./bin/Release/bf -f ./input.bf -s 25
```
# Man
```man
NAME
       bf - LinkedList Brainfuck compiler
SYNOPSIS
       bf  [-f FILENAME] [-s SPEED]
DESCRIPTION
       Concatenate FILE(s) to standard output.

       With no FILE, or when FILE is -, read standard input.

       -f, -file, -i, -input *FILENAME*
              input is FILENAME.

       -s, -speed *SLEEP*
              Expects SLEEP ms per character.
              if not set SLEEP to the number starting with * in the first line of the file,
              otherwise it will set the sleep to 0 ms per character.
              
EXAMPLES
       bf 
              input.bf will run with 0ms per character
              
       bf -f test.txt -s 500
              text.txt will run with 500ms per character

       bf -f test.txt 
              text.txt will run with 0ms per character
```
