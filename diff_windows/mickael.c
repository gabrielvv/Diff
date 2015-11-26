#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "contiguous_list_int.h"
#include "custom_file.h"
#include "directory.h"
#include "stringList.h"


int main(int argc, char* argv[])
{
  if(argc < 3){
      printf("Nombre d' arguments insuffisant");
      return 1;
  }
  if(check_folder(argv[1])== 1 && check_folder(argv[2])==1){
    c_String* list1[count_path(argv[1],0)];
    c_String* list2[count_path(argv[2],0)];
    int cpt1=0;
    int cpt2=0;
    //printf("remplissage des list\n");
    cpt1 = scan_folder(argv[1],0,list1);
    cpt2 =scan_folder(argv[2],0,list2);
    //printf("cpt1 %d cpt2 %d\n",cpt1,cpt2);
    //string_display(list1[1]);
    //printf("bijour %s", list1[1]->datas);
    analyze(list1,list2,argv[1],argv[2],cpt1,cpt2);
    analyzereverse(list1,list2,argv[1],argv[2],cpt1,cpt2);
  }
  else{

  }

  return 0;
}
