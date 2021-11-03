# LinkListBrainfuck


# Language overview
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
