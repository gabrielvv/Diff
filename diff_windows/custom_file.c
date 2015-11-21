#include "custom_file.h"
#include <stdlib.h>
#include <stdio.h>


c_file* new_c_file(FILE* fp){
  c_file* cf = malloc(sizeof(c_file));
  cf->file = fp;
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
    printf("Ligne %d de %d caracteres\n", i, cf->char_count_per_line[i]-1);//-1 on  ne compte pas le '\0'
    printf("<%s", str);
  }
  /*if(!cf->end)
    printf("\n\\ No newline at end of file\n");*/

  //printf("/*********************************** FIN ******************************************/\n");
}

void set_lines_count_and_alloc(c_file* cf){

  char c;
  FILE* fp = cf->file;
  rewind(fp);
  short previous = 0; //false si previous char is different from '\n'

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

void set_char_count_per_line(c_file* cf){

  int i, char_count;
  char c;
  FILE* fp = cf->file;
  rewind(fp);

  char_count = i = 0; //représente l'index de ligne

  while((c = fgetc(fp)) != EOF){
    char_count++;
    if(c == 10){
      cf->char_count_per_line[i] = ++char_count;
      i++;
      char_count = 0;
    }else if(c == 13){}

  }
  cf->char_count_per_line[i] = ++char_count;

}

void set_lines_content(c_file* cf){

  int i,j,h;
  char c;
  FILE* fp = cf->file;
  rewind(fp);

  for(i = 0; i < cf->lines_count; i++){

    if(i == cf->lines_count-1 && cf->end){
      char str[] = "\n\\ No newline at end of file\n";
      int totalChar = cf->char_count_per_line[i]+30;
      cf->lines_content[i] = malloc(sizeof(char)*totalChar);

      for(j = 0; j < cf->char_count_per_line[i]-1; j++){
        if((c = fgetc(fp)) != EOF){
          cf->lines_content[i][j] = c;
        }
      }

      for(h = cf->char_count_per_line[i]-1; h < totalChar-1; h++){
          cf->lines_content[i][h] = str[h-cf->char_count_per_line[i]];
      }

      cf->lines_content[i][totalChar-1] = '\0';
    }else{

      cf->lines_content[i] = malloc(sizeof(char)*cf->char_count_per_line[i]);
      for(j = 0; j < cf->char_count_per_line[i]-1; j++){
        if((c = fgetc(fp)) != EOF){
          cf->lines_content[i][j] = c;
        }
      }

      cf->lines_content[i][j] = '\0';
      //Permet de déterminer de quelle façon se termine le fichier
    }
  }

}

void setParams(c_file* cf){
  set_lines_count_and_alloc(cf);
  set_char_count_per_line(cf);
  set_lines_content(cf);

}

short line_comp(c_file* cf1, c_file* cf2, int index){
  if(index > cf1->lines_count || index > cf2->lines_count){
    return 1;
  }
  else if (cf1->char_count_per_line[index] != cf2->char_count_per_line[index]){
    return 1;
  }else{
    int i;
    rewind(cf1->file);
    rewind(cf2->file);
    for(i = 0; i < index; i++){
      if(fgetc(cf1->file) != fgetc(cf2->file))
        return 1;
    }
  }
  return 0;
}
