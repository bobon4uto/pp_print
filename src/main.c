
#define PP_PRINT_IMPLEMENTATION
#include "pp_print.h"
#include <stdlib.h>


void generate(int num);

int main(int argc, char** argv) {
  if (argc == 2) {
    char* num_s = argv[1];
    int num = atoi(num_s);
    if (num <= 0) {
      println("Cannot generate pp_print.h with support for ", num_s ," args!");
      return 1;
    }
    generate(num);
  } else {
    char* exe_name = "pp_remake";
    if (argc > 0) {
      exe_name = argv[0];
    }
    println(exe_name, " usage: ");
    println("  ", exe_name, " <max args num>");
    println("Example:");
    println("  ", exe_name, " 5");
    println("This will print pp_print.h with support for 5 args to stdout.");
  }


  return 0;
}

void generate(int num) {
  #include "unchanged.c"
  print(pp_print_start);

  //print(pp_print_changed);

  println("#define PP_PRINT_ARG_N( \\");
  for (int i = 1; i <= num; i++) {
    print("_",i,", ");
  }
  println("N, ...) N");
  //println("          _1,  _2,  _3, N, ...) N");
  println("#define PP_PRINT_SEQ() \\");
  for (int i = num; i > 0; i--) {
    print("PP_PRINT_",i,", ");
  }
  println("PP_PRINT_0");

  println("#define PP_PRINT_0");
  for (int i = 1; i <= num; ++i) {
    print("#define PP_PRINT_",i,"(PRINT_INTERFACE, PRINT_TYPES, ");
    for (int arg_num = 1; arg_num <= i; ++arg_num) {
      print("ARG_", arg_num);
      if (arg_num != i) {
        print(", ");
      }
    }
    print(") ");
    for (int arg_num = 1; arg_num <= i; ++arg_num) {
      print("PP_PRINT_OVERLOADED(PRINT_INTERFACE, PRINT_TYPES, ARG_",arg_num,"); ");
    }
    println("");
  }

  print(pp_print_end);
}
