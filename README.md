# pp_print
## Usage
To use default print types include `src/pp_print.h` in your project:
```c
#define PP_PRINT_IMPLEMENTATION
#include "pp_print.h"
int main() {
  char* world = "World";
  println("Hello, ",world," number ",1);
}
```
See `src/example.c` for extensive example with custom types.

## Build

```bash
mkdir -p build
cc src/main.c -o build/main && build/main 63 > pp_print.h
```
Replace 63 to change number of maximum arguments for print funciton.  
If you decide to change the source you will have to change `src/unchanged.c` file too, since it is used to generate `pp_print.h`. You can use `src/make_text.c` to turn `pp_print.h` into a c string for `unchanged.c`.  
if you ever break `src/pp_print.h` you can regenerate it by copying `src/pp_print.origin.h` to its place and compiling again, this version of pp_print only works with 3 args, but it is enough to build `src/main.c`



## Credits
the counting macro was made by Eitan:  
Source - https://stackoverflow.com/q/11317474  
Posted by Eitan T, modified by community. See post 'Timeline' for change history  
Retrieved 2026-11-09, License - CC BY-SA 4.0  
