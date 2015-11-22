#include <stdio.h>
#include <stdlib.h>
#include "contiguous_list_int.h"
#include "custom_file.h"
#include <string.h>

t_list** algo(char** lines_content1, char** lines_content2,int lines_count1, int lines_count2);
void print_bornes(int borne_sup,int borne_inf, short end);
void print_result(char** lines_content1, char** lines_content2, t_list** results);


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

  t_list** results = malloc(sizeof(t_list*)*2);
  results = algo(myCustomFile->lines_content, myCustomFile2->lines_content, myCustomFile->lines_count, myCustomFile2->lines_count);

  printf("/*********************************** SOUS SEQUENCES  ******************************************/\n");
  printf("DEBUG File 1 :");
  list_display(results[0]);
  printf("DEBUG File 2 :");
  list_display(results[1]);
  fclose(fp1);
  fclose(fp2);


  printf("/*********************************** AFFICHAGE *******************************************/\n");
  print_result(myCustomFile->lines_content, myCustomFile2->lines_content, results);

  return 0;
}


void print_bornes(int borne_sup,int borne_inf, short end){
  if(borne_sup+1 == borne_inf-1){
    printf("%d", borne_sup+1);
    end ? printf("\n") : 0 ;
  }else{
    printf("%d,%d", borne_sup + 1, borne_inf - 1);
    end ? printf("\n") : 0 ;
  }
}

void print_result(char** lines_content1, char** lines_content2, t_list** results){

  int i, j, end, start, diff1, diff2;
  int sub_seq_length = results[0]->length;
  //printf("DEBUG sub_seq_length = %d\n", sub_seq_length);

  for(i = 0; i < sub_seq_length-1; i++){
    (i == sub_seq_length-1) ? end = 1 : 0 ;
    int borne_sup1, borne_inf1, borne_sup2, borne_inf2; // attention sup et inf ici concernent l'ordre d'ordonnancement des bornes et non leurs valeurs
    // la borne supérieure est i et inférieure est i+1

    borne_sup1 = results[0]->datas[i];
    borne_inf1 = results[0]->datas[i+1];
    borne_sup2 = results[1]->datas[i];
    borne_inf2 = results[1]->datas[i+1];

    diff1 = borne_inf1 - borne_sup1;
    diff2 = borne_inf2 - borne_sup2;
    //printf("DEBUG diff1:%d diff2:%d\n", diff1, diff2);

    if(diff2 > 1 && diff1 > 1){
    /********************** CHANGE ******************/

      print_bornes(borne_sup1, borne_inf1, 0);
      printf("c");
      print_bornes(borne_sup2, borne_inf2, 1);
      for(j = borne_sup1; j < borne_inf1-1; j++){
        // déclage de -1 parce qu'on va chercher les valeurs de lignes ds un tableau dont l'index commence à 0
        printf("< %s", lines_content1[j]);
      }
      printf("---\n");
      for(j = borne_sup2; j < borne_inf2-1; j++){
        printf("> %s", lines_content2[j]);
      }


    }else if(diff2 == 1 && diff1 > 1){
    /*************** DELETE *****************/

      print_bornes(borne_sup1, borne_inf1, 0);
      printf("d");
      print_bornes(borne_sup2-1, borne_sup2+1, 1);
      for(j = borne_sup1; j < borne_inf1-1; j++){
        // déclage de -1 parce qu'on va chercher les valeurs de lignes ds un tableau dont l'index commence à 0
        printf("< %s", lines_content1[j]);
      }

    }else if(diff2 > 1 && diff1 == 1){
    /*************** APPEND *****************/
      print_bornes(borne_sup1-1, borne_inf1, 0);
      printf("a");
      print_bornes(borne_sup2, borne_inf2, 1);
      for(j = borne_sup2; j < borne_inf2-1; j++){
        // déclage de -1 parce qu'on va chercher les valeurs de lignes ds un tableau dont l'index commence à 0
        printf("> %s", lines_content2[j]);
      }
    }
  }
}

t_list** algo(char** lines_content1, char** lines_content2, int lines_count1, int lines_count2){

  int maxlength = (lines_count2 >= lines_count1 ? lines_count1+1 : lines_count2+1);

  t_list* result_list1 = list_create(maxlength);
  t_list* result_list2 = list_create(maxlength);
  t_list* tmp_list1 = list_create(maxlength);
  t_list* tmp_list2 = list_create(maxlength);

  int i, j, store, offset, start, index;
  char* str;
  store = start = offset = 0;

  /****************** ALGO RECHERCHE SS SEQ : remplie result_list1 et result_list2 avec les indices des lignes de la sous seq la + longue ********************/
  while(lines_count2-start > result_list2->length){
  //for(h = 0; h < cf2->lines_count; h++){
    for(i = start; i < lines_count2; i++){
      str = lines_content2[i];

      for(j = offset; j < lines_count1; j++){

        if(strcmp(str,lines_content1[j]) == 0){

          if(store){
            /** REPLACE **/
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
          store = (j == lines_count1-1 ? 1 : 0);
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

  list_insert(result_list1, 0, 0);
  list_insert(result_list2, 0, 0);
  list_append(result_list1, lines_count1+1);
  list_append(result_list2, lines_count2+1);
  /*if(result_list1->datas[result_list1->length-1] != lines_count1){
    list_append(result_list1, lines_count1);
  if(result_list2->datas[result_list2->length-1] != lines_count2){
    list_append(result_list2, lines_count2);
  }*/
  t_list** results = malloc(sizeof(t_list*)*2);
  results[0] = result_list1;
  results[1] = result_list2;
  return results;
}
