#include <stdio.h>
#include <stdlib.h>
#include "contiguous_list_int.h"
#include "custom_file.h"
#include "linked_list.h"
#include <string.h>

t_list** algo(char** lines_content1, char** lines_content2,int lines_count1, int lines_count2);
void test_algo(char** file1, char** file2, int** expected_results, int lines_count1,int lines_count2);
void test_c_file(FILE* fp, int* char_count_per_line, int lines_count);


int main(int argc, char* argv[])
{

  char buffer[256];
  FILE *fp;
  fp = fopen("file.txt","w");
  char str[] =
  "Lorem ipsum dolor sit amet,\n consectetur adipiscing elit,\n sed do eiusmod tempor incididunt ut labore et dolore magna aliqua.\n Ut enim ad minim veniam,\n quis nostrud exercitation ullamco laboris nisi ut aliquip ex ea commodo consequat.\n Duis aute irure dolor in reprehenderit in voluptate velit esse cillum dolore eu fugiat nulla pariatur.\n Excepteur sint occaecat cupidatat non proident,\n sunt in culpa qui officia deserunt mollit anim id est laborum";
  fwrite(str, sizeof(char), sizeof(str),fp);

  int lines_count = 8;
  int char_count_per_line[] = {28,30,68,26,83,104,49,62};

  fclose(fp);
  fp = fopen("file.txt","r");
  test_c_file(fp, char_count_per_line, lines_count);


  char f1l1[] = "a\n";
  char f1l2[] = "b\n";
  char f1l3[] = "c\n";
  char f1l4[] = "d\n";
  char f1l5[] = "e\n";
  char f1l6[] = "f";
  char* file1[] = {f1l1,f1l2,f1l3,f1l4,f1l5,f1l6};
  printf("File1 filled");
  char f2l1[] = "a\n";
  char f2l2[] = "b\n";
  char f2l3[] = "e\n";
  char f2l4[] = "d";
  char* file2[] = {f2l1,f2l2,f2l3,f2l4};

  int result2[] = {1,2,3};
  int result1[] = {1,2,5};
  int* expected_results[] = {result1, result2};
  //test_algo(file1, file2, expected_results, 6, 4);

  fclose(fp);
  return 0;
}

void test_algo(char** file1, char** file2, int** expected_results, int lines_count1,int lines_count2){
  t_list** results = malloc(sizeof(t_list*)*2);
  results = algo(file1, file2 , lines_count1, lines_count2);
}


t_list** algo(char** lines_content1, char** lines_content2, int lines_count1, int lines_count2){

  //1er argument: cf1->lines_content
  //2eme arg: cf2->lines_content
  int maxlength = (lines_count2 >= lines_count1 ? lines_count1 : lines_count2);
  /*int length1 = cf1->lines_count;
  int length2 = cf2->lines_count;*/

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
/*********************** FIN ALGO ********************************/
  t_list** results = malloc(sizeof(t_list*)*2);
  results[0] = result_list1;
  results[1] = result_list2;
  return results;
}


void test_c_file(FILE* fp, int* char_count_per_line, int lines_count){
  printf("/***************************TEST C_FILE****************************/\n");
  char buffer[256];
  int i, success_count, fail_count;
  success_count = fail_count = 0;
  c_file *cf = new_c_file(fp);
  setParams(cf);
  rewind(fp);
  if(cf->lines_count == lines_count){
    printf("> Test c_file nombre de lignes: SUCCESS\n");
    success_count++;
  }else{
    printf("> Test c_file nombre de lignes: FAILED\n");
    fail_count++;
  }

  for(i = 0; i < lines_count; i++){
    if(cf->char_count_per_line[i] == char_count_per_line[i]){
      success_count++;
    }else{
      printf("> Difference de comptage de caracteres a la ligne %d: %d expected, %d currently \n", i, char_count_per_line[i] ,cf->char_count_per_line[i]);
      fail_count++;
    }
  }

  for(i = 0; i < lines_count; i++){
    fgets(buffer, 256, fp);
    //printf("Compare %s\nand\n%s\n", buffer, cf->lines_content[i]);
    if(strcmp(buffer, cf->lines_content[i]) == 0){
      success_count++;
    }else{
      printf("> Difference de caracteres a la ligne %d\n", i);
      fail_count++;
    }
  }

  printf("On %d tests\n %d FAILS\n %d SUCCESS\n", (lines_count*2)+1, fail_count, success_count);
  printf("/*************************** FIN ****************************/\n");
}
