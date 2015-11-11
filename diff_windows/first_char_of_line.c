#include "linked_list.h"
#include "first_char_of_line.h"

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

t_maillon** getEqualLines(c_file* file1, c_file* file2){

  t_maillon* fc1 = NULL;
  t_maillon* fc2 = NULL;
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
        linked_list_append(&fc1, int i, char file1->lines_content[i][0]);
        linked_list_append(&fc2, int j, char file2->lines_content[j][0]);
      }
    }
  }

  t_maillon **fc = malloc(sizeof(t_maillon*)*2);
  fc[0] = &fc1;
  fc[2] = &fc2;
  return fc;
}
