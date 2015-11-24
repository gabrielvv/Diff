#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <wchar.h>
#include "contiguous_list_int.h"
#include "custom_file.h"


t_list** subsequence_research(wchar_t** lines_content1, wchar_t** lines_content2,int lines_count1, int lines_count2);
void print_bounds(int upper_bound,int lower_bound, short end);
void print_result(wchar_t** lines_content1, wchar_t** lines_content2, t_list** results);


int main(int argc, char* argv[])
{
  if(argc < 3){
      printf("Nombre d' arguments insuffisant");
      return 1;
  }
  printf("DEBUG: start\n");
  FILE *fp1, *fp2;
  printf("DEBUG: fopen\n");
  fp1 = fopen(argv[1], "r");
  printf("DEBUG: new_c_file\n");
  c_file *myCustomFile = new_c_file();
  printf("DEBUG: setparams\n");
  setParams(myCustomFile, fp1);
  printf("DEBUG: printContent\n");
  printContent(myCustomFile);
  fclose(fp1);


  fp2 = fopen(argv[2], "r");
  c_file *myCustomFile2 = new_c_file();
  setParams(myCustomFile2, fp2);
  printContent(myCustomFile2);
  fclose(fp2);

  t_list** results = malloc(sizeof(t_list*)*2);
  printf("DEBUG: subsequence research\n");
  results = subsequence_research(myCustomFile->lines_content, myCustomFile2->lines_content, myCustomFile->lines_count, myCustomFile2->lines_count);

  printf("/*********************************** SUBSEQUENCES  ******************************************/\n");
  printf("DEBUG File 1 :");
  list_display(results[0]);
  printf("DEBUG File 2 :");
  list_display(results[1]);

  printf("/*********************************** DISPLAY *******************************************/\n");
  print_result(myCustomFile->lines_content, myCustomFile2->lines_content, results);

  custom_file_free(myCustomFile);
  custom_file_free(myCustomFile2);
  list_free(results[0]);
  list_free(results[1]);
  free(results);

  return 0;
}


void print_bounds(int upper_bound,int lower_bound, short end){
  if(upper_bound+1 == lower_bound-1){
    printf("%d", upper_bound+1);
    end ? printf("\n") : 0 ;
  }else{
    printf("%d,%d", upper_bound + 1, lower_bound - 1);
    end ? printf("\n") : 0 ;
  }
}

void print_result(wchar_t** lines_content1, wchar_t** lines_content2, t_list** results){

  int i, j, diff1, diff2;
  int sub_seq_length = results[0]->length;

  for(i = 0; i < sub_seq_length-1; i++){

    int upper_bound1, lower_bound1, upper_bound2, lower_bound2; // attention sup et inf ici concernent l'ordre d'ordonnancement des bounds et non leurs valeurs
    // la borne supérieure est i et inférieure est i+1

    upper_bound1 = results[0]->datas[i];
    lower_bound1 = results[0]->datas[i+1];
    upper_bound2 = results[1]->datas[i];
    lower_bound2 = results[1]->datas[i+1];

    diff1 = lower_bound1 - upper_bound1;
    diff2 = lower_bound2 - upper_bound2;
    //printf("DEBUG diff1:%d diff2:%d\n", diff1, diff2);

    if(diff2 > 1 && diff1 > 1){
    /********************** CHANGE ******************/

      print_bounds(upper_bound1, lower_bound1, 0);
      printf("c");
      print_bounds(upper_bound2, lower_bound2, 1);
      for(j = upper_bound1; j < lower_bound1-1; j++){
        // -1 shift because we're getting string values from a 2 dimensions array whose index starts from 0
        wprintf(L"< %ls", (wchar_t*)lines_content1[j]);
      }
      printf("---\n");
      for(j = upper_bound2; j < lower_bound2-1; j++){
        wprintf(L"> %ls", (wchar_t*)lines_content2[j]);
      }


    }else if(diff2 == 1 && diff1 > 1){
    /*************** DELETE *****************/

      print_bounds(upper_bound1, lower_bound1, 0);
      printf("d");
      print_bounds(upper_bound2-1, upper_bound2+1, 1);
      for(j = upper_bound1; j < lower_bound1-1; j++){
        // -1 shift because we're getting string values from a 2 dimensions array whose index starts from 0
        wprintf(L"< %ls", lines_content1[j]);
      }

    }else if(diff2 > 1 && diff1 == 1){
    /*************** APPEND *****************/
      print_bounds(upper_bound1-1, lower_bound1, 0);
      printf("a");
      print_bounds(upper_bound2, lower_bound2, 1);
      for(j = upper_bound2; j < lower_bound2-1; j++){
        // -1 shift because we're getting string values from a 2 dimensions array whose index starts from 0
        wprintf(L"> %ls", lines_content2[j]);
      }
    }
  }
}

t_list** subsequence_research(wchar_t** lines_content1, wchar_t** lines_content2, int lines_count1, int lines_count2){

  int maxlength = (lines_count2 >= lines_count1 ? lines_count1+1 : lines_count2+1);
  printf("DEBUG:  maxlength = %d\n", maxlength);
  t_list* result_list1 = list_create(maxlength);
  t_list* result_list2 = list_create(maxlength);
  t_list* tmp_list1 = list_create(maxlength);
  t_list* tmp_list2 = list_create(maxlength);

  int i, j, store, offset, start, index;
  wchar_t* str;
  store = start = offset = 0;

  /****************** SUBSEQUENCE RESEARCH : fill result_list1 and result_list2 with line's indexes from file1 and file2 longest common subsequence ********************/
  while(lines_count2-start > result_list2->length){

    for(i = start; i < lines_count2; i++){
      str = lines_content2[i];

      for(j = offset; j < lines_count1; j++){
        printf("DEBUG: strcmp %ls vs %ls\n",str, lines_content1[j]);
        if(strcmp((char*)str,(char*)lines_content1[j]) == 0){

          if(store){
            /******************** REPLACE **************************/
            index = ((int)(tmp_list2->length-1) < 0 ? 0 : (int)(tmp_list2->length-1));

            tmp_list1->datas[index] = j+1;//subseq file1
            tmp_list2->datas[index] = i+1; //subseq file2

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
        store = 1; //useless?
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

  list_free(tmp_list1);
  list_free(tmp_list2);

  list_insert(result_list1, 0, 0);
  list_insert(result_list2, 0, 0);
  printf("DEBUG final list_append\n");
  list_append(result_list1, lines_count1+1);
  list_append(result_list2, lines_count2+1);

  t_list** results = malloc(sizeof(t_list*)*2);
  results[0] = result_list1;
  results[1] = result_list2;
  return results;
}
