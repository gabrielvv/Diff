#include <stdio.h>

#ifndef CUSTOM_FILE
#define CUSTOM_FILE

typedef struct custom_file{
  int lines_count;
  int* char_count_per_line;
  char **lines_content;
  short end;
  FILE* file;
}c_file;

void setParams(c_file*);
c_file* new_c_file(FILE*);
c_file* set_lines_count(c_file*);
void set_lines_count_and_alloc(c_file*);
int get_lines_count(c_file*, int nbr);
void set_char_count_per_line(c_file*);
int get_char_count_per_line(c_file*);
void printContent(c_file*);
short line_comp(c_file*, c_file*, int);


#endif
