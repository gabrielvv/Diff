#include <stdio.h>

#ifndef CUSTOM_FILE
#define CUSTOM_FILE

/**************************************************************
* STRUCTURE custom_file
* ------------------------------------------------------------
* a structure gathering a file's content
* and additional informations about this content
*
* lines_count           : how many lines?
* char_count_per_line   : how many char per line?
* lines_content         : line's content
* end                   : final line incomplete?
***************************************************************/
typedef struct custom_file{
  int lines_count;
  int* char_count_per_line;
  char **lines_content;
  short end;
}c_file;


/**************************************************************
* FUNCTION new_c_file
* ------------------------------------------------------------
* structure initialisation
*
* returns : a custom_file structure
*
***************************************************************/
c_file* new_c_file();


/**************************************************************
* FUNCTION set_lines_content
* ------------------------------------------------------------
* lines_count and char_count_per_line must be set
* in order for this function to work properly
*
* fill cf->lines_content with the lines' content from fp
***************************************************************/
void set_lines_content(c_file* cf, FILE* fp);


/**************************************************************
* FUNCTION set_lines_count
* ------------------------------------------------------------
*
* fill cf->lines_count with fp's lines' number
***************************************************************/
void set_lines_count_and_alloc(c_file* cf,FILE* fp);


/**************************************************************
* FUNCTION set_char_count_per_line
* ------------------------------------------------------------
* lines_count must be set
* in order for this function to do its job properly
*
* set cf->char_count_per_line with the number of characters
* from each fp's line
***************************************************************/
void set_char_count_per_line(c_file* cf, FILE* fp);


/**************************************************************
* FUNCTION set_params
* ------------------------------------------------------------
* set_lines_count_and_alloc
* set_char_count_per_line
* set_lines_content
***************************************************************/
void setParams(c_file*,FILE*);


/**************************************************************
* FUNCTION printContent
* ------------------------------------------------------------
* Display cf->lines_content
*
***************************************************************/
void printContent(c_file* cf);


/**************************************************************
* FUNCTION printContent
* ------------------------------------------------------------
* free the memory space allocated for cf
*
***************************************************************/
void custom_file_free(c_file* cf);

#endif
