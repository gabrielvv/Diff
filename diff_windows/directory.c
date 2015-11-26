#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <dirent.h>
#include "stringList.h"
#include "contiguous_list_int.h"
#include "custom_file.h"
#include "directory.h"
#include "mystrcmp.h"

/**************************************************
* Program        : command diff                  *
* Description    :                               *
* Author         : Fournier David                *
*                  Gabriel Vautrin               *
*                  Bordage Mickael               *
* Date           : 07/11/2015                    *
* Version        : V1.0                          *
*************************************************/


/**************************************************************
* FUNCTION check_folder
* Check if the path is an existing folder
***************************************************************/
short check_folder(char *path)
{
	DIR *is_folder=NULL;

	is_folder=opendir(path);
	if (is_folder!=NULL){
		closedir(is_folder);
		return 1;
	}
	closedir(is_folder);
	return 0;

}

/**************************************************************
* FUNCTION scan_folder
* fill c_string
***************************************************************/
int scan_folder(char* dirname,int i,c_String** list)
{
	DIR *folder;
	struct dirent *file;
	char *real_path  =NULL;
	char *path = NULL;

    folder=opendir(dirname);
	while((file = readdir(folder))){

		if(file->d_name[0]=='.' || (file->d_name[0]=='.' && file->d_name[1]=='.')){
                continue;
		}
		real_path=(char *)malloc(strlen(dirname)+strlen(file->d_name)+ 2);
        path =(char *)malloc(strlen(dirname));
        sprintf(real_path,"%s/%s",dirname,file->d_name);
        sprintf(path,"%s",dirname);
		if(check_folder(real_path) == 1 ){
			i = scan_folder(real_path,i,list);
		}
		else{
      list[i] =string_create(string_length(real_path));
      string_append(list[i],real_path);
      i++;
		}
	}
	closedir(folder);
	return i;
}

/**************************************************************
* FUNCTION count_path
* count the number of file
***************************************************************/
int count_path(char* dirname,int cpt)
{
	DIR *folder;
	struct dirent *file;
	char *real_path=NULL;
	char *path = NULL;
    folder=opendir(dirname);
	while ((file = readdir(folder))){
		if(file->d_name[0]=='.'){
                continue;
		}
		real_path=(char *)malloc(strlen(dirname)+strlen(file->d_name)+ 2);
        path =(char *)malloc(strlen(dirname));
        sprintf(real_path,"%s/%s",dirname,file->d_name);
        sprintf(path,"%s",dirname);
		if( check_folder(real_path) == 1 ){
			count_path(real_path,cpt);
		}
		else{
      cpt++;
		}
	}
	closedir(folder);
	return cpt;
}

/**************************************************************
* FUNCTION analyze
* analyze the first struct
***************************************************************/
int analyze(c_String** array1,c_String** array2,char* argv1,char* argv2,int cpt1,int cpt2){

		//printf("analyze\n");
    int i=0;
    int j=0;
    int c=0;
    int taille;
    int taille2=0;
    int exist=0;
    int length_argv1 = strlen(argv1);
    int length_argv2 = strlen(argv2);

    for(i=0;i<cpt1;i++){

        taille = ((array1[i]->length)-(length_argv1));
        //printf("passage %d\n",taille);
        char* sub1 = calloc(sizeof(char)*taille, sizeof(char));

        for(c=(length_argv1+1);c <array1[i]->length;c++){
            sub1[c-(length_argv1+1)] = array1[i]->datas[c];
        }
            //sub1[taille] = '/0';
        //printf("sub1 : %s\n",sub1);

    for(j=0;j<cpt2;j++){
        taille2 = (array2[j]->length)-(length_argv2);
        //printf("passage2 %d\n",taille2);
        char* sub2 = calloc(sizeof(char)*taille2, sizeof(char));
        //printf("len %d\n",array2[j]->length);
        for(c=(length_argv2+1);c <array2[j]->length;c++){
            //printf("char %c\n",array1[i]->datas[c]);
            sub2[c-(length_argv2+1)] = array2[j]->datas[c];
            //printf("charac2 %c index %d\n",sub2[c-(argv2+1)],c-(argv2+1));
        }
        //sub2[taille2] = '/0';

        if(strcmp(sub1,sub2) == 0){
						//analyzeAndPrint(array1[i]->datas, array2[j]->datas,"");
            exist=3;
        }
					free(sub2);
    }

    if(exist==0){

      printf("Only in %s : %s\n",argv1, sub1);
    }
     exist=0;
		 free(sub1);
}
    return 0;
}

/**************************************************************
* FUNCTION analyzereverse
* analyze the second struct
***************************************************************/
int analyzereverse(c_String** array1,c_String** array2,char* argv1,char* argv2,int cpt1,int cpt2){

		//printf("analyzereverse\n");
    int i=0;
    int j=0;
    int c=0;
    int taille=0;
    int taille2=0;
    int exist=0;
    int length_argv1 = strlen(argv1);
    int length_argv2 = strlen(argv2);

    for(i=0;i<cpt2;i++){
        taille = (array2[i]->length+1)-(length_argv2+1);
        //printf("passage %d\n",taille);
        char* sub1 = calloc(sizeof(char)*taille, sizeof(char));
        //printf("len %d\n",array1[i]->length);
        for(c=(length_argv2+1);c <array2[i]->length;c++){
            //printf("char %c\n",array1[i]->datas[c]);
            sub1[c-(length_argv2+1)] = array2[i]->datas[c];
        }
            //sub1[taille] = '/0';

    for(j=0;j<cpt1;j++){
				//printf("DEBUG: %d\n", array1[j]->length);
        taille2 = (array1[j]->length)-(length_argv1);

        char* sub2 = calloc(sizeof(char)*taille2, sizeof(char));

        for(c=(length_argv1+1);c <array1[j]->length;c++){

            sub2[c-(length_argv1+1)] = array1[j]->datas[c];
        }

        if(strcmp(sub1,sub2)==0){

            exist=3;;
        }
				free(sub2);

    }
    //printf("Exist : %d\n", exist);
    if(exist==0){
			//printf("length = %d\n", strlen(sub1));
      printf("Only in %s : %s\n", argv2,sub1);
    }
     exist=0;
		 free(sub1);
}
    return 0;
}

enum bool {FALSE, TRUE};

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
    //printf("DEBUG: s = %d\ty = %d\tw = %d\n", s, y, w);
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
  results = subsequence_research(myCustomFile->lines_content, myCustomFile2->lines_content, myCustomFile->lines_count, myCustomFile2->lines_count, options);


  if(results[0]->length - 2 == myCustomFile->lines_count && results[1]->length - 2 == myCustomFile2->lines_count && myCustomFile->end == myCustomFile2->end){
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
t_list** subsequence_research(char** lines_content1, char** lines_content2, int lines_count1, int lines_count2, char* options){

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

        if(compareString(str, lines_content1[j], options) == 0){
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
