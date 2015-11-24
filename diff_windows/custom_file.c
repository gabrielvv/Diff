#include "custom_file.h"
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>


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
    wchar_t* str = cf->lines_content[i];
    printf("Ligne %d de %d caracteres\n", i, cf->wchar_t_count_per_line[i]-1);//-1 because wchar_t_count_per_line[i] takes the final '\0' into account
    wprintf(L"<%s", str);
  }

  //printf("/*********************************** FIN ******************************************/\n");
}

void set_lines_count_and_alloc(c_file* cf, FILE* fp){
  printf("DEBUG: set_lines_count_and_alloc\n");
  wchar_t c;
  rewind(fp);
  short previous = 0; //false if previous wchar_t is different from '\n'

  while((c = fgetwc(fp)) != WEOF){
    if(c == 10){
      cf->lines_count++ ;
      previous = 1;
    }else{
      previous = 0;
    }
  }
  if(c == WEOF && previous){
    cf->lines_count--;
    cf->end = 0 ;
  }else{
    cf->end =  1;
  }

  cf->lines_content = malloc(sizeof(wchar_t*)*cf->lines_count);
  cf->wchar_t_count_per_line = malloc(sizeof(int)*cf->lines_count);
}

void set_wchar_t_count_per_line(c_file* cf, FILE* fp){
  printf("DEBUG: set_wchar_t_count_per_line\n");
  int i, wchar_t_count;
  wchar_t c;
  rewind(fp);

  wchar_t_count = i = 0;

  while((c = fgetwc(fp)) != WEOF){
    wchar_t_count++;
    if(c == 10){
      cf->wchar_t_count_per_line[i] = ++wchar_t_count;
      i++;
      wchar_t_count = 0;
    }else if(c == 13){}

  }
  cf->wchar_t_count_per_line[i] = ++wchar_t_count;

}

void set_lines_content(c_file* cf, FILE* fp){
  printf("DEBUG: set_lines_content\n");
  int i,j;
  wchar_t c;
  rewind(fp);

  for(i = 0; i < cf->lines_count; i++){

    if(i == cf->lines_count-1 && cf->end){
    /******************* "\ No newline at end of file" scenario **********************/
      wchar_t str[] = L"\n\\ No newline at end of file\n"; // 29 characters

      int wchar_count = cf->wchar_t_count_per_line[i];
      int totalChar = (wchar_count+30);
      cf->lines_content[i] = malloc(sizeof(wchar_t)*totalChar);

      for(j = 0; j < wchar_count-1; j++){
        if((c = fgetwc(fp)) != WEOF){
          //printf("DEBUG: %lc\n",c);
          cf->lines_content[i][j] = c;
        }
      }
      //printf("DEBUG j = %d, cf->wchar_t_count_per_line[i] = %d\n",j,wchar_count);
      for(; j < totalChar-1; j++){
          //printf("DEBUG j: %d\n",j);
          cf->lines_content[i][j] = str[j - (wchar_count-1)];
      }

      cf->lines_content[i][totalChar-1] = L'\0';
      //wprintf("DEBUG last line: %d\n",j);
    }else{

      cf->lines_content[i] = malloc(sizeof(wchar_t)*cf->wchar_t_count_per_line[i]);
      for(j = 0; j < cf->wchar_t_count_per_line[i]-1; j++){
        if((c = fgetwc(fp)) != WEOF){
          //printf("DEBUG: %lc\n",c);
          cf->lines_content[i][j] = c;
        }
      }

      cf->lines_content[i][j] = '\0';
    }
  }

}

void setParams(c_file* cf, FILE* fp){
  set_lines_count_and_alloc(cf,fp);
  set_wchar_t_count_per_line(cf,fp);
  set_lines_content(cf,fp);
}

void custom_file_free(c_file* cf){

  int i;
  for(i=0; i < cf->lines_count; i++){
    free(cf->lines_content[i]);
  }
  free(cf->lines_content);
  free(cf->wchar_t_count_per_line);
  free(cf);
}
