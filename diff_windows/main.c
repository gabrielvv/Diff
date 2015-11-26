#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "directory.h"
#include "mystrcmp.h"

/**************************************************
* Program        : command diff                  *
* Description    : implémentation de diff utility*
* Author         : Fournier David                *
*                  Gabriel Vautrin               *
*                  Bordage Mickael               *
* Date           : 26/11/2015                    *
* Version        : V1.0                          *
*************************************************/


int main(int argc, char* argv[])
{

  char *options="";
  char *Source1, *Source2;

  if(argc == 2 && (strcmp(argv[1], "--help") == 0)){
      printf("Usage: diff [OPTION] FILE1 FILE2\n\n  -w  --ignore-all-space Ignore all white space.\n  -s  --report-identical-files Report when two files are the same.\n  --help Output this help.\n\nIf FILE1 or FILE2 is '-', read standard input.");
      return 0;
  }else if(argc == 1){
      printf("diff: missing operand\ndiff: try 'diff --help' for more information.");
      return 0;
  }
  else if(argc == 3){
      Source1 = argv[argc-2];
      Source2 = argv[argc-1];     // files or folders to compare
  }
  else if(argc == 4){
      Source1 = argv[argc-2];
      Source2 = argv[argc-1];     // files or folders to compare
      options = argv[1];
  }
  else if(argc > 4 ){
      printf("Usage: diff [OPTION] FILE1 FILE2\n  You can use one option.\n  --help Output this help.\n\nIf FILE1 or FILE2 is '-', read standard input.");
      return 0;
  }else{
    return 1;
  }

  //printf("%s, %s", Source1, Source2);
  if(check_folder(Source1) == 1 && check_folder(Source2) == 1){
    c_String* list1[count_path(Source1,0)];
    c_String* list2[count_path(Source2,0)];
    int cpt1=0;
    int cpt2=0;
    cpt1 = scan_folder(Source1, 0, list1);
    cpt2 = scan_folder(Source2, 0, list2);
    analyzeDirectories(list1, list2, Source1, Source2, cpt1, cpt2);
    analyzeDirectoriesReverse(list1, list2, Source1, Source2, cpt1, cpt2);
  }
  //printf("Source1: %s\tSource2: %s\n", Source1, Source2);
  else{
    analyzeFilesAndPrint(Source1, Source2, options);
  }

  return 0;
}
