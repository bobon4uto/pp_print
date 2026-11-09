// This is the first iteration of PP_PRINT that was created by hand.
// It by itself was used to develop generator for PP_PRINT

#ifdef    DEFINE_IMPLEMENTATION
#define PP_PRINT_IMPLEMENTATION
#undef    DEFINE_IMPLEMENTATION
#endif // DEFINE_IMPLEMENTATION
#ifndef    _PP_PRINT_H_
#define    _PP_PRINT_H_
// pp_print interface

#ifndef PP_PRINT_CUSTOM

#define PP_PRINT_TYPES_DEFAULT
#define PP_PRINT_TYPES(...) \
    int:            fprint_int,                  \
    float:          fprint_float,                 \
    bool:           fprint_bool,                 \
    const char*:    fprint_char_ptr,              \
    char*:          fprint_char_ptr,

#include <stdio.h>
#define bool _Bool
#define true (bool)1
#define false (bool)0

void fprint_int     (FILE* f, int val);
void fprint_bool    (FILE* f, bool val);
void fprint_float   (FILE* f, float val);
void fprint_char_ptr(FILE* f, const char* val);

#endif // PP_PRINT_CUSTOM



// Source - https://stackoverflow.com/q/11317474
// Posted by Eitan T, modified by community. See post 'Timeline' for change history
// Retrieved 2026-11-09, License - CC BY-SA 4.0
#define PP_PRINT_ARG_N( \
          _1,  _2,  _3, N, ...) N

#define PP_PRINT_SEQ()                                        \
          PP_PRINT_3,  PP_PRINT_2,  PP_PRINT_1,  PP_PRINT_0

#define PP_PRINT_3(PRINT_INTERFACE, PRINT_TYPES, ARG_1, ARG_2, ARG_3) PP_PRINT_OVERLOADED(PRINT_INTERFACE, PRINT_TYPES, ARG_1); PP_PRINT_OVERLOADED(PRINT_INTERFACE, PRINT_TYPES, ARG_2); PP_PRINT_OVERLOADED(PRINT_INTERFACE, PRINT_TYPES, ARG_3);
#define PP_PRINT_2(PRINT_INTERFACE, PRINT_TYPES, ARG_1, ARG_2)        PP_PRINT_OVERLOADED(PRINT_INTERFACE, PRINT_TYPES, ARG_1); PP_PRINT_OVERLOADED(PRINT_INTERFACE, PRINT_TYPES, ARG_2);
#define PP_PRINT_1(PRINT_INTERFACE, PRINT_TYPES, ARG_1)               PP_PRINT_OVERLOADED(PRINT_INTERFACE, PRINT_TYPES, ARG_1)
#define PP_PRINT_0

#define PP_DISPATCH_PRINT_(...)    PP_PRINT_ARG_N(__VA_ARGS__)

#define PP_DISPATCH_PRINT(...)     PP_DISPATCH_PRINT_(__VA_ARGS__, PP_PRINT_SEQ())

#define PP_PRINT_OVERLOADED(f, PRINT_TYPES, val) _Generic(val,  \
    PRINT_TYPES() \
    default:        ((void *) 0)\
)(f, val)

#define interface_print(interface, PRINT_TYPES, ...)   do { PP_DISPATCH_PRINT(__VA_ARGS__)(interface, PRINT_TYPES, __VA_ARGS__); } while(0)
#define interface_println(interface, PRINT_TYPES, ...) do { interface_print(interface, PRINT_TYPES, __VA_ARGS__); interface_print(interface, PRINT_TYPES, "\n"); } while (0)



#ifdef    PP_PRINT_TYPES_DEFAULT

#define fprint(f,   ...) interface_print(f, PP_PRINT_TYPES, __VA_ARGS__)
#define fprintln(f, ...) interface_println(f, PP_PRINT_TYPES, __VA_ARGS__)

#define print(...)   fprint(stdout, __VA_ARGS__)
#define println(...) fprintln(stdout, __VA_ARGS__)

#endif // PP_PRINT_TYPES_DEFAULT








#ifdef      PP_PRINT_IMPLEMENTATION
// pp_print implementation

#ifdef PP_PRINT_TYPES_DEFAULT

void fprint_int(FILE* f, int val) {
  fprintf(f, "%d", val);
}
void fprint_bool(FILE* f, bool val) {
  if (val) {
    fprintf(f, "true");
  } else {
    fprintf(f, "false");
  }
}
void fprint_float(FILE* f, float val) {
  fprintf(f, "%f", val);
}
void fprint_char_ptr(FILE* f, const char* val) {
  fprintf(f, "%s", val);
}

#endif //PP_PRINT_TYPES_DEFAULT


#endif   // PP_PRINT_IMPLEMENTATION
#endif   //_PP_PRINT_H_

