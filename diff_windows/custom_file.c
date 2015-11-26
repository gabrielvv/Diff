#include "custom_file.h"
#include <stdlib.h>
#include <stdio.h>


c_file* new_c_file(){
  c_file* cf = malloc(sizeof(c_file));
  cf->lines_count = 1;
  cf->end = 0;
  return cf;
}


void printContent(c_file* cf){
  int i;
  printf("/**************************** PRINT CONTENT C_FILE ***********************************/\n");
  printf("Nombre de lignes: %d\n", cf->lines_count);
  for(i=0; i<cf->lines_count; i++){
    char* str = cf->lines_content[i];
    printf("Ligne %d de %d caracteres\n", i, cf->char_count_per_line[i]-1);//-1 because char_count_per_line[i] takes the final '\0' into account
    printf("<%s", str);
  }

}

void set_lines_count_and_alloc(c_file* cf, FILE* fp){

  char c;
  rewind(fp);
  short previous = 0; /* false if previous char is different from '\n' */

  while((c = fgetc(fp)) != EOF){
    if(c == 10){
      cf->lines_count++ ;
      previous = 1;
    }else{
      previous = 0;
    }
  }
  if(c == EOF && previous){
    cf->lines_count--;
    cf->end = 0 ;
  }else{
    cf->end =  1;
  }

  cf->lines_content = malloc(sizeof(char*)*cf->lines_count);
  cf->char_count_per_line = malloc(sizeof(int)*cf->lines_count);
}

void set_char_count_per_line(c_file* cf, FILE* fp){

  int i, char_count;
  char c;
  short previous = 0; /* true only if previous char is '\n' */

  rewind(fp);

  char_count = i = 0;

  /******* LE BOUT DE CODE QUI POSE PROBLEME ****************/
  while((c = fgetc(fp)) != EOF){
    char_count++;
    previous = 0;
    if(c == 10){
      cf->char_count_per_line[i] = ++char_count;
      i++;
      char_count = 0;
      previous = 1;
    }
  }
  if(!previous){cf->char_count_per_line[i] = ++char_count;}
  /***********************************************************/
  //printf("DEBUG: lines_count: %d\tchar_count[%d] = %d\n", cf->lines_count, i, char_count);
}

void set_lines_content(c_file* cf, FILE* fp){

  int i,j;
  char c;
  rewind(fp);

  for(i = 0; i < cf->lines_count; i++){

    if(i == cf->lines_count-1 && cf->end){
    /******************* "\ No newline at end of file" scenario **********************/
      int char_count = cf->char_count_per_line[i];
      char str[] = "\n\\ No newline at end of file\n"; // 29 characters
      int totalChar = char_count + 30;
      cf->lines_content[i] = malloc(sizeof(char)*totalChar);

      for(j = 0; j < char_count - 1; j++){
        if((c = fgetc(fp)) != EOF){
          //printf("DEBUG: %c\n",c);
          cf->lines_content[i][j] = c;
        }
      }
      //printf("DEBUG j = %d, cf->char_count_per_line[i] = %d\n",j,char_count);
      for(; j < totalChar - 1; j++){
          //printf("DEBUG: j = %d\n", j);
          cf->lines_content[i][j] = str[j - (char_count-1)];
      }

      cf->lines_content[i][totalChar-1] = '\0';
    }else{

      cf->lines_content[i] = malloc(sizeof(char)*cf->char_count_per_line[i]);
      for(j = 0; j < cf->char_count_per_line[i]-1; j++){
        if((c = fgetc(fp)) != EOF){
          //printf("DEBUG: %c\n",c);
          cf->lines_content[i][j] = c;
        }
      }

      cf->lines_content[i][j] = '\0';
    }
  }

}

void setParams(c_file* cf, FILE* fp){
  set_lines_count_and_alloc(cf,fp);
  set_char_count_per_line(cf,fp);
  set_lines_content(cf,fp);
}

void custom_file_free(c_file* cf){

  int i;
  for(i=0; i < cf->lines_count; i++){
    free(cf->lines_content[i]);
  }
  free(cf->lines_content);
  free(cf->char_count_per_line);
  free(cf);
}
