#include "linked_list.h"
#include "first_char_of_line.h"
#include <stdlib.h>
#include <string.h>
/*fcol** getEqualLines(c_file* file1, c_file* file2){

  fcol** first_chars = malloc(sizeof(*fcol));
  int i, j;
  int lines_count_min, lines_count_max;
  if((i = file1->lines_count1) >= (j = file2->lines_count2)){
    lines_count_max = i;
    lines_count_min = j;
  }else{
    lines_count_max = j;
    lines_count_min = i;
  }

  for(i = 0; i < lines_count_max; i++){
    for(j = 0; j < lines_count_min; j++){
      if(strcmp(file1->lines_content[i], file2->lines_content[j]){
        fcol* fc = malloc(sizeof(fcol));
        fc->
      }
    }
  }

}*/


//éventuellement à remplacer par l'utilisation de strcmp ds l'algo de recherche de sous-séquence
t_maillon** getEqualLines(c_file* file1, c_file* file2, t_maillon** fc){

  printf("getEqualLines\n");
  t_maillon* fc1 = NULL;
  t_maillon* fc2 = NULL;
  int i, j, pos;
  pos = 0;
  /*int lines_count_min, lines_count_max;
  if((i = file1->lines_count) >= (j = file2->lines_count)){
    lines_count_max = i;
    lines_count_min = j;
  }else{
    lines_count_max = j;
    lines_count_min = i;
  }*/

  for(i = 0; i < file1->lines_count; i++){

    for(j = 0; j < file2->lines_count; j++){
      printf("comparaison\n string1: %s\n string2: %s\n",file1->lines_content[i], file2->lines_content[j]);
      if(strcmp(file1->lines_content[i], file2->lines_content[j]) == 0){
        printf("Linked list append\n");
        linked_list_append(&fc1, i, file1->lines_content[i][0]);
        pos = linked_get_insert_pos(fc2,j);
        printf("pos = %d\n", pos);
        pos < 0 ? linked_list_append(&fc2, j, file2->lines_content[j][0]) : linked_list_insert(&fc2, j, file2->lines_content[j][0], pos);
      }
    }
  }

  fc[0] = fc1;
  fc[1] = fc2;
  return fc;
}
