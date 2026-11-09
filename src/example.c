
#include <stdio.h>
#include <string.h>

#define PP_PRINT_CUSTOM
#include "pp_print.h"


typedef struct sBuf {
  char items[256];
  int count;
} Buf;

void  buf_print_char(Buf* buf, char c);
void  buf_print_char_ptr(Buf* buf, const char* s);

#define          BUF_TYPES(...)      \
    const char:  buf_print_char,     \
    char:        buf_print_char,     \
    int:         buf_print_char,     \
    const char*: buf_print_char_ptr, \
    char*:       buf_print_char_ptr,

#define buf_print(buf,   ...) interface_print((buf), BUF_TYPES, __VA_ARGS__)
#define buf_println(buf, ...) interface_println((buf), BUF_TYPES, __VA_ARGS__)




typedef struct sMyType {
  int i;
  float f;
} MyType;

typedef struct sFloatFormat {
  float f;
  enum { FLOAT_FORMAT_NORMAL, FLOAT_FORMAT_EXP, } format;
} FloatFormat;

void fprint_my_type     (FILE* f, MyType my_type);
void fprint_buf         (FILE* f, Buf buf);
void fprint_int         (FILE* f, int i);
void fprint_float_format(FILE* f, FloatFormat ff);
void fprint_float       (FILE* file, float f);
void fprint_char_ptr    (FILE* f, const char* s);

FloatFormat float_format_normal(float f);
FloatFormat float_format_exp(float f);

#define PP_CUSTOM_TYPES(...) \
    MyType:      fprint_my_type,      \
    Buf:         fprint_buf,          \
    FloatFormat: fprint_float_format, \
    int:         fprint_int,          \
    float:       fprint_float,        \
    const char*: fprint_char_ptr,     \
    char*:       fprint_char_ptr,

#define fprint(f,   ...) interface_print((f), PP_CUSTOM_TYPES, __VA_ARGS__)
#define fprintln(f, ...) interface_println((f), PP_CUSTOM_TYPES, __VA_ARGS__)

#define print(...) fprint(stdout, __VA_ARGS__)
#define println(...) fprintln(stdout, __VA_ARGS__)

int main() {
  MyType mt = {0};
  mt = (MyType){-10,2000.0f};
  println( mt );
  Buf b = {0};
  // C has a very bad habit of making char literals int.
  // So you either accept them as chars or don't use them
  buf_print(&b, "Hello", ',');
  buf_print(&b, ' ', "World!");

  println(b);

  // You have to put initialized structs in prentasys Cause its all MACROS
  println( "My type: ", ((MyType){10,10.0f}) );
}



void  buf_print_char(Buf* buf, char c) {
  if (buf->count < 256) {
    buf->items[buf->count++] = c;
  }
}
void  buf_print_char_ptr(Buf* buf, const char* s) {
  if (buf->count + strlen(s) < 256) {
    memcpy( buf->items + buf->count, s, sizeof(char)*strlen(s));
    buf->count += strlen(s);
  }
}


void fprint_buf (FILE* f, Buf buf) {
  fprintf(f, "%.*s", buf.count, buf.items);
}
void fprint_my_type (FILE* f, MyType my_type) {
  fprint(f, "MyType{",my_type.i,",",my_type.f,"}");
}
void fprint_int     (FILE* f, int i) {
  fprintf(f, "i(%d)",i);
}
void fprint_float_format   (FILE* f, FloatFormat ff) {
  switch ( ff.format ) {
    case FLOAT_FORMAT_NORMAL: {
      fprintf(f, "%f", ff.f);
    } break;
    case FLOAT_FORMAT_EXP: {
      fprintf(f, "%e", ff.f);
    } break;
  }
}
void fprint_float   (FILE* file, float f) {
  if (f > 1000 || f < 0.001) {
    fprint(file, float_format_exp(f));
  } else {
    fprint(file, float_format_normal(f));
  }
}
void fprint_char_ptr(FILE* f, const char* s) {
  fprintf(f, "%s",s);
}


FloatFormat float_format_normal(float f) {
  return (FloatFormat){
    .f = f,
    .format = FLOAT_FORMAT_NORMAL,
  };
}
FloatFormat float_format_exp(float f) {
  return (FloatFormat){
    .f = f,
    .format = FLOAT_FORMAT_EXP,
  };
}





