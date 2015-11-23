#include <stdio.h>

#ifndef CUSTOM_FILE
#define CUSTOM_FILE


typedef struct custom_file{
  int lines_count;
  int* char_count_per_line;
  char **lines_content;
  short end;
}c_file;

c_file* new_c_file();

void set_lines_content(c_file* cf, FILE* fp);

void set_lines_count_and_alloc(c_file*,FILE*);
int get_lines_count(c_file*, int nbr);

void set_char_count_per_line(c_file*,FILE*);
int get_char_count_per_line(c_file*);

void setParams(c_file*,FILE*);

void printContent(c_file*);

void custom_file_free(c_file* cf);

#endif
