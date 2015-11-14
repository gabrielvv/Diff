#include <stdio.h>
#include <stdlib.h>
#include "contiguous_list_int.h"
#include "custom_file.h"
#include "linked_list.h"
#include <string.h>

int main(int argc, char* argv[])
{
    if(argc < 3){
        printf("Nombre d' arguments insuffisant");
        return 1;
    }

    FILE *fp1, *fp2;
    fp1 = fopen(argv[1], "r");
    c_file *myCustomFile = new_c_file(fp1);
    setParams(myCustomFile);

    fp2 = fopen(argv[2], "r");
    c_file *myCustomFile2 = new_c_file(fp2);
    setParams(myCustomFile2);

    int length = (myCustomFile2->lines_count >= myCustomFile->lines_count ? myCustomFile->lines_count : myCustomFile2->lines_count);
    int length1 = myCustomFile->lines_count;
    int length2 = myCustomFile2->lines_count;

    t_list* result_list1 = list_create(length);
    t_list* result_list2 = list_create(length);
    t_list* tmp_list1 = list_create(length);
    t_list* tmp_list2 = list_create(length);

    int i, j, store, offset, start, index;
    char* str;
    store = start = offset = 0;

    /****************** ALGO RECHERCHE SS SEQ : remplie result_list1 et result_list2 avec les indices des lignes de la sous seq la + longue ********************/
    while(myCustomFile2->lines_count-start > result_list2->length){

      for(i = start; i < length2; i++){
        str = myCustomFile2->lines_content[i];

        for(j = offset; j < length1; j++){

          if(strcmp(str,myCustomFile->lines_content[j]) == 0){

            if(store){
              index = ((int)(tmp_list2->length-1) < 0 ? 0 : (int)(tmp_list2->length-1));

              tmp_list1->datas[index] = j+1;//sub seq file1
              tmp_list2->datas[index] = i+1; //sub seq file2

              if(index == 0){
                tmp_list2->length++;
                tmp_list1->length++;
              }

            }else{
              list_append(tmp_list1, j+1);
              list_append(tmp_list2, i+1);
            }
            store = (j == length1-1 ? 1 : 0);
            offset = j+1;
            break;
          }
        }

        if(store && tmp_list2->length > result_list1->length){
          result_list1->length = tmp_list1->length;
          result_list2->length = tmp_list2->length;
          list_datas_copy(tmp_list1, result_list1);
          list_datas_copy(tmp_list2, result_list2);
          store = 1; //superflu
          offset = 0;
        }
      }
    if(tmp_list2->length > result_list1->length){
      result_list1->length = tmp_list1->length;
      result_list2->length = tmp_list2->length;
      list_datas_copy(tmp_list1, result_list1);
      list_datas_copy(tmp_list2, result_list2);
    }
    offset = 0;
    list_remove_all_from(tmp_list1, 0);
    list_remove_all_from(tmp_list2, 0);
    start++;
  }
  /*********************** FIN ALGO ********************************/
  
  printf("Final result_list:\n");
  printf("Fichier 2 :");
  list_display(result_list2);
  printf("Fichier 1 :");
  list_display(result_list1);
  fclose(fp1);
  fclose(fp2);

  return 0;
}
