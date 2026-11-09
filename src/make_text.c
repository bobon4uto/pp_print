// just a helper to convert file into a multiline cstring
// NOTE: It only escapes " \ and newline so if the file has any other charaacter that has to be escaped, it will fail.
// use like this:
//   cat file.c | ./make_text > out.c

#include <stdio.h>
int main() {
  char c = getc(stdin);

  putc('"', stdout);
  while (c!=EOF) {
    switch (c) {
      case '\\': {
        putc('\\', stdout);
        putc('\\', stdout);
      } break;
      case '"': {
        putc('\\', stdout);
        putc('"', stdout);
      } break;
      case '\n': {
        putc('\\', stdout);
        putc('n', stdout);
        putc('"', stdout);
        putc('\n', stdout);
        putc('"', stdout);
      } break;

      default: putc(c, stdout);
    }


    c = getc(stdin);
  }
  putc('"', stdout);

}
