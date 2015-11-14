#include <stdio.h>
#include <stdlib.h>
#include "contiguous_list.h"
#include "custom_file.h"
#include <string.h>


int main(int argc, char* argv[])
{

    char tab2[9] = {'a','b','c','d','e','f','g','h'}; //contient seulement les lignes ordonnées de file 1 qu'on retrouve ds file2
    char tab1[9] = {'h','b','c','d','e','g','a','f'}; //contient seulement les lignes ordonnées de file2 qu'on retrouve ds file1
    t_list* result_list = list_create(8);
    t_list* tmp_list = list_create(8);

    int i, j, store, offset, start;
    char c;
    start = offset = 0;
    printf("tab1 de longueur: %d\ntab2 de longueur: %d\n", strlen(tab1), strlen(tab2));

    while((strlen(tab1)-start) > result_list->length){
      for(i = start; i < strlen(tab1); i++){
        c = tab1[i];
        //if(i < index)
        //list_append(tmp_list, c);
        printf("offset : %d\n", offset);
        for(j = offset; j < strlen(tab2); j++){

          if(c == tab2[j]){
            if(store){
              printf("Replace %c by %c\n", tmp_list->datas[tmp_list->length-1], c );
              tmp_list->datas[tmp_list->length-1] = c;
              store = (j == strlen(tab2)-1 ? 1 : 0);
              offset = j+1;
            }else{
              list_append(tmp_list, c); //incrémente list->length
              store = (j == strlen(tab2)-1 ? 1 : 0);
              offset = j+1;
            }
            printf("break\n");
            break;
          }
        }

        if(store && tmp_list->length > result_list->length){

          result_list->length = tmp_list->length;
          list_datas_copy(tmp_list, result_list);

          printf("Storing new result_list:\n");
          list_display(result_list);

          offset = 0;
        }
      }

    if(tmp_list->length > result_list->length){

      result_list->length = tmp_list->length;
      list_datas_copy(tmp_list, result_list);

      printf("Storing new result_list:\n");

      list_display(result_list);
    }

    offset = 0;
    list_remove_all_from(tmp_list, 0);

    printf("Remove all, tmp_list->length = %d\n", tmp_list->length);
    printf("List display tmp_list:");

    list_display(tmp_list);

    printf("List display result_list:");

    list_display(result_list);
    start++;
  }

  printf("Final result_list:\n");
  list_display(result_list);
  return 0;
}
