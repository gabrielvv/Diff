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

  char *Param="";
  char *Source1, *Source2;

  if(argc < 2 && compare(argv[1], "--help")){
      printf("Usage: diff [OPTION] FILE1 FILE2\n\n  -w  --ignore-all-space Ignore all white space.\n  -s  --report-identical-files Report when two files are the same.\n  --help Output this help.\n\nIf FILE1 or FILE2 is '-', read standard input.");
      return 1;
  }
  if(argc < 2){
      printf("diff: missing operand\ndiff: try 'diff --help' for more information.");
      return 1;
  }
  if(argc == 3){
    Source1 = argv[argc-2];
    Source2 = argv[argc-1];     // files or folders to compare
  }
  if(argc ==4 ){
      Source1 = argv[argc-2];
      Source2 = argv[argc-1];     // files or folders to compare
      Param = argv[1];
  }
  if(argc > 4 ){
      printf("Usage: diff [OPTION] FILE1 FILE2\n  You can use one option.\n  --help Output this help.\n\nIf FILE1 or FILE2 is '-', read standard input.");
      return 1;

  }

  //printf("%s, %s", Source1, Source2);
  if(check_folder(Source1) == 1 && check_folder(Source2) == 1){
    c_String* list1[count_path(Source1,0)];
    c_String* list2[count_path(Source2,0)];
    int cpt1=0;
    int cpt2=0;
    //printf("remplissage des list\n");
    cpt1 = scan_folder(Source1, 0, list1);
    cpt2 = scan_folder(Source2, 0, list2);
    //printf("cpt1 %d cpt2 %d\n",cpt1,cpt2);
    //string_display(list1[1]);
    //printf("bijour %s", list1[1]->datas);
    analyze(list1, list2, Source1, Source2, cpt1, cpt2);
    analyzereverse(list1, list2, Source1, Source2, cpt1, cpt2);
  }
  //printf("Source1: %s\tSource2: %s\n", Source1, Source2);
  else{
    analyzeAndPrint(Source1, Source2, Param);
  }

  return 0;
}
