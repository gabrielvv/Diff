#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "contiguous_list_int.h"
#include "custom_file.h"

/**************************************************
* Program        : command diff                  *
* Description    : implémentation de diff utility*
* Author         : Fournier David                *
*                  Gabriel Vautrin               *
*                  Bordage Mickael               *
* Date           : 26/11/2015                    *
* Version        : V1.0                          *
*************************************************/

enum bool {FALSE, TRUE};

t_list** subsequence_research(char** lines_content1, char** lines_content2,int lines_count1, int lines_count2);
void print_bounds(int upper_bound,int lower_bound, short end);
void print_result(char** lines_content1, char** lines_content2, t_list** results, char* options);
void analyzeAndPrint(char* fileName1, char* fileName2, char* options);

int main(int argc, char* argv[])
{
  /*if(argc < 3){
      printf("Nombre d' arguments insuffisant");
      return 1;
  }*/

  analyzeAndPrint(argv[1],argv[2],"s");

  return 0;
}

/**************************************************************
* FUNCTION analyzeAndPrint
* ------------------------------------------------------------
* analyze two files and display their differences
*
* fileName1 : string containing the name of file1
* fileName2 : string containing the name of file2
* options   : string containing one character per option
*
***************************************************************/
void analyzeAndPrint(char* fileName1, char* fileName2, char* options){

  int i;
  enum bool s, w, y;
  s = y = w = FALSE;

  for(i = 0; i < strlen(options); i++){
    switch(options[i]){
      case 's': s = TRUE;
        break;
      case 'y': y = TRUE;
        break;
      case 'w': w = TRUE;
        break;
    }
    printf("DEBUG: s = %d\ty = %d\tw = %d\n", s, y, w);
  }
  FILE *fp1, *fp2;
  fp1 = fopen(fileName1, "r");
  c_file *myCustomFile = new_c_file();
  setParams(myCustomFile, fp1);
  //printContent(myCustomFile);
  fclose(fp1);


  fp2 = fopen(fileName2, "r");
  c_file *myCustomFile2 = new_c_file();
  setParams(myCustomFile2, fp2);
  //printContent(myCustomFile2);
  fclose(fp2);

  t_list** results; /* freed at the end of analyzeAndPrint */
  results = subsequence_research(myCustomFile->lines_content, myCustomFile2->lines_content, myCustomFile->lines_count, myCustomFile2->lines_count);

  printf("/*********************************** SUBSEQUENCES  ******************************************/\n");
  printf("DEBUG File 1 :");
  list_display(results[0]);
  printf("DEBUG File 2 :");
  list_display(results[1]);

  printf("/*********************************** DISPLAY *******************************************/\n");
  printf("DEBUG: results[0]->length = %d\tmyCustomFile->lines_count = %d\n", results[0]->length,myCustomFile->lines_count);
  printf("DEBUG: results[1]->length = %d\tmyCustomFile2->lines_count = %d\n", results[1]->length,myCustomFile2->lines_count);
  if(results[0]->length - 1 == myCustomFile->lines_count && results[1]->length - 1 == myCustomFile2->lines_count && myCustomFile->end == myCustomFile2->end){
      printf("Files %s and %s are identical", fileName1, fileName2);
  }else{
    print_result(myCustomFile->lines_content, myCustomFile2->lines_content, results, options);
  }

  custom_file_free(myCustomFile);
  custom_file_free(myCustomFile2);
  list_free(results[0]);
  list_free(results[1]);
  free(results);
}

/**************************************************************************************
* FUNCTION print_bounds
* --------------------------------------------------------------------------------
* print the bounds linked to one difference in a file
*
* upper_bound : string containing the name of file1
* lower_bound : string containing the name of file2
* end         : mark the end of the line in the output after the printing
*
***************************************************************************************/
void print_bounds(int upper_bound,int lower_bound, short end){
  if(upper_bound+1 == lower_bound-1){
    printf("%d", upper_bound+1);
    end ? printf("\n") : 0 ;
  }else{
    printf("%d,%d", upper_bound + 1, lower_bound - 1);
    end ? printf("\n") : 0 ;
  }
}

void print_result(char** lines_content1, char** lines_content2, t_list** results, char* options){

  int i, j, diff1, diff2;
  int sub_seq_length = results[0]->length;

  enum bool y;
  y = FALSE;

  for(i = 0; i < strlen(options); i++){
    switch(options[i]){
      case 'y': y = TRUE;
        break;
    }
  }

  for(i = 0; i < sub_seq_length-1; i++){

    int upper_bound1, lower_bound1, upper_bound2, lower_bound2; /*upper_bound equals to the Nth element of the LCS and lower_bound equals the (N+1)th element */

    upper_bound1 = results[0]->datas[i];
    lower_bound1 = results[0]->datas[i+1];
    upper_bound2 = results[1]->datas[i];
    lower_bound2 = results[1]->datas[i+1];

    diff1 = lower_bound1 - upper_bound1;
    diff2 = lower_bound2 - upper_bound2;

    if(diff2 > 1 && diff1 > 1){
    /******************************************** CHANGE ****************************************************/

      if(y){

      }else{
        print_bounds(upper_bound1, lower_bound1, 0);
        printf("c");
        print_bounds(upper_bound2, lower_bound2, 1);
        for(j = upper_bound1; j < lower_bound1-1; j++){
          // -1 shift because we're getting string values from a 2 dimensions array whose index starts from 0
          printf("< %s", lines_content1[j]);
        }
        printf("---\n");
        for(j = upper_bound2; j < lower_bound2-1; j++){
          printf("> %s", lines_content2[j]);
        }
      }


    }else if(diff2 == 1 && diff1 > 1){
    /******************************************** DELETE ***************************************************/

      if(y){

      }else{
        print_bounds(upper_bound1, lower_bound1, 0);
        printf("d");
        print_bounds(upper_bound2-1, upper_bound2+1, 1);
        for(j = upper_bound1; j < lower_bound1-1; j++){
          // -1 shift because we're getting string values from a 2 dimensions array whose index starts from 0
          printf("< %s", lines_content1[j]);
        }
      }

    }else if(diff2 > 1 && diff1 == 1){
    /********************************************* APPEND ***************************************************/
      if(y){

      }else{
        print_bounds(upper_bound1-1, lower_bound1, 0);
        printf("a");
        print_bounds(upper_bound2, lower_bound2, 1);
        for(j = upper_bound2; j < lower_bound2-1; j++){
          /* -1 shift because we're getting string values from a 2 dimensions array whose index starts from 0 */
          printf("> %s", lines_content2[j]);
        }
      }
    }
  }
}

/**************************************************************************************
* FUNCTION subsequence_research
* ------------------------------------------------------------------------------------
* find the Longest Common Subsequence (LCS) between two files
* the line's content being an element
*
* lines_content1 : string array - contains a file's content
* lines_content2 : string array - contains the reference file's content
* lines_count1   : the length of lines_content1
* lines_count2   : the length of lines_content2
*
* returns     : a contiguous list array with a length equals to 2,
                each contiguous list represents the line number from the lines
                from the LCS in their respective file
***************************************************************************************/
t_list** subsequence_research(char** lines_content1, char** lines_content2, int lines_count1, int lines_count2){

  int maxlength = (lines_count2 >= lines_count1 ? lines_count1+1 : lines_count2+1);

  t_list* result_list1 = list_create(maxlength);
  t_list* result_list2 = list_create(maxlength);
  t_list* tmp_list1 = list_create(maxlength);
  t_list* tmp_list2 = list_create(maxlength);

  int i, j, store, offset, start, index;
  char* str;
  store = start = offset = 0;

  /****************** SUBSEQUENCE RESEARCH : fill result_list1 and result_list2 with line's indexes from file1 and file2 longest common subsequence ********************/
  while(lines_count2-start > result_list2->length){

    for(i = start; i < lines_count2; i++){
      str = lines_content2[i];

      for(j = offset; j < lines_count1; j++){

        if(strcmp(str,lines_content1[j]) == 0){

          if(store){
            /** REPLACE **/
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
  list_append(result_list1, lines_count1+1);
  list_append(result_list2, lines_count2+1);

  t_list** results = malloc(sizeof(t_list*)*2);
  results[0] = result_list1;
  results[1] = result_list2;
  return results;
}
