#ifndef FIRST_CHAR_OF_LINE
#define FIRST_CHAR_OF_LINE

#include "linked_list.h"
#include "custom_file.h"

/*typedef struct first_char_of_line{
  int line_index;
  char first_char;
  fcol* next;
}fcol;


fcol* getEqualLines(c_file*, c_file*);*/

t_maillon** getEqualLines(c_file*, c_file*, t_maillon**);

#endif
