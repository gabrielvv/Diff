#ifndef DIRECTORY_INCLUDE
#define DIRECTORY_INCLUDE
#include <stdio.h>
#include "stringList.h"
#include "contiguous_list_int.h"

/**************************************************
* Program        : command diff                  *
* Description    :                               *
* Author         : Fournier David                *
*                  Gabriel Vautrin               *
*                  Bordage Mickael               *
* Date           : 07/11/2015                    *
* Version        : V1.0                          *
*************************************************/

#ifndef WIN32
    #include <sys/types.h>
#endif



short check_folder(char*);
int scan_folder(char*,int,c_String**);
int count_path(char*,int);
int analyze(c_String**,c_String**,char*,char*,int,int);
int analyzereverse(c_String**,c_String**,char*,char*,int,int);


t_list** subsequence_research(char** lines_content1, char** lines_content2,int lines_count1, int lines_count2, char* options);
void print_bounds(int upper_bound,int lower_bound, short end);
void print_result(char** lines_content1, char** lines_content2, t_list** results, char* options);
void analyzeAndPrint(char* fileName1, char* fileName2, char* options);

#endif
