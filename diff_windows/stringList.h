#ifndef STRINGFILE_H_INCLUDED
#define STRINGFILE_H_INCLUDED
#include <stdio.h>
/**************************************************
* Program        : command diff                  *
* Description    :                               *
* Author         : Fournier David                *
*                  Gabriel Vautrin               *
*                  Bordage Mickael               *
* Date           : 07/11/2015                    *
* Version        : V1.0                          *
*************************************************/


typedef struct s_String{
    char* datas;
    unsigned int max;
    unsigned int length;
}c_String;


c_String* string_create(unsigned int);
void string_display(c_String*);
void string_append(c_String*,char*);
int line_count(FILE*);
int string_length(char* chaine);


#endif // STRING_H_INCLUDED
