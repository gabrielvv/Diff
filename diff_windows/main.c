#include <stdio.h>
#include <stdlib.h>
#include "contiguous_list_int.h"
#include "custom_file.h"
#include "linked_list.h"
#include "first_char_of_line.h"
#include <string.h>

// + ESPACE DE NOMS

// CR = 13
// LF = 10




short line_comp();
void dealingWithArg(char*);
void printOutput();
void displayHelp();

//GESTION DES ERREURS

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
    //printContent(myCustomFile);

    fp2 = fopen(argv[2], "r");
    c_file *myCustomFile2 = new_c_file(fp2);
    setParams(myCustomFile2);
    //printContent(myCustomFile2);


    /*char tab2[11] = {'a','b','c','d','e','f','g','h','a','z'}; //contient seulement les lignes ordonnées de file 1 qu'on retrouve ds file2
    char tab1[9] = {'h','b','c','d','e','g','a','f'}; //contient seulement les lignes ordonnées de file2 qu'on retrouve ds file1*/
    int length = (myCustomFile2->lines_count >= myCustomFile->lines_count ? myCustomFile->lines_count : myCustomFile2->lines_count);
    int length1 = myCustomFile->lines_count;
    int length2 = myCustomFile2->lines_count;
    printf("length = %d", length);
    t_list* result_list1 = list_create(length);
    t_list* result_list2 = list_create(length);
    t_list* tmp_list1 = list_create(length);
    t_list* tmp_list2 = list_create(length);

    int i, j, store, offset, start;
    char* str;
    store = start = offset = 0;

    while(myCustomFile2->lines_count-start > result_list2->length){

      for(i = start; i < length2; i++){
        str = myCustomFile2->lines_content[i];
        //printf("offset : %d\n", offset);
        for(j = offset; j < length1; j++){
          if(strcmp(str,myCustomFile->lines_content[j]) == 0){
            if(store){
              //printf("Replace %d by %d\n", tmp_list2->datas[tmp_list2->length-1], i );
              tmp_list1->datas[tmp_list1->length-1] = j;//ss sequ file1
              tmp_list2->datas[tmp_list2->length-1] = i; //ss sequ file2
              store = (j == length1-1 ? 1 : 0);
              offset = j+1;
            }else{
              list_append(tmp_list1, j); //incrémente list->length
              list_append(tmp_list2, i);
              store = (j == length1-1 ? 1 : 0);
              offset = j+1;
            }
            //printf("break\n");
            break;
          }
        }

        if(store && tmp_list2->length > result_list1->length){
          result_list1->length = tmp_list1->length;
          result_list2->length = tmp_list2->length;
          list_datas_copy(tmp_list1, result_list1);
          list_datas_copy(tmp_list2, result_list2);

          /*printf("Storing new result_list:\n");
          list_display(result_list);*/

          offset = 0;
        }
      }
    if(tmp_list2->length > result_list1->length){
      result_list1->length = tmp_list1->length;
      result_list2->length = tmp_list2->length;
      list_datas_copy(tmp_list1, result_list1);
      list_datas_copy(tmp_list2, result_list2);

      printf("Storing new result_list:\n");
      list_display(result_list1);
    }
    offset = 0;
    list_remove_all_from(tmp_list1, 0);
    list_remove_all_from(tmp_list2, 0);
    printf("Remove all, tmp_list->length = %d\n", tmp_list2->length);
    printf("List display tmp_list: ");

    list_display(tmp_list2);

    printf("List display result_list: ");

    list_display(result_list2);
    start++;
  }
  printf("Final result_list:\n");
  list_display(result_list2);
  list_display(result_list1);
  fclose(fp1);
  fclose(fp2);
  return 0;
}
