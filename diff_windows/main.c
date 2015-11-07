#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"

void line_comp();
void dealingWithArg(char*);
void printOutput();
void displayHelp();

//GESTION DES ERREURS

typedef struct file_parameters{
  int lines_nbr;
  int* nbr_char_per_line;
  FILE* fp;
}file_params;

file_params* new_file_params();
file_params* set_lines_nbr(file_params*, int nbr);
int get_lines_nbr(file_params*, int nbr);
file_params* set_nbr_char_per_line(file_params*, int nbr, int line);
int get_nbr_char_per_line(file_params*, int line);

int main(int argc, char* argv[])
{
    if(argc < 3){
        printf("Nombre d 'arguments insuffisant");
        return 1;
    }

    int lines_nbr1, lines_nbr2, nbr_char1, nbr_char2;
    int i,j;


    lines_nbr2 = lines_nbr1 = 1 ;
    nbr_char1 = nbr_char2 = 0;

    char **lines1, **lines2;
    int *nbr_char_per_line1, *nbr_char_per_line2;
    FILE *fp1, *fp2;

    fp1 = fopen(argv[1], "r");
    fp2 = fopen(argv[2], "r");

    char c;

    // COMPTE DU NOMBRE DE LIGNES ET STOCKAGE DS lines_nbr1
    while((c = fgetc(fp1)) != EOF){
      //printf(" ligne %d: ", lines_nbr1);
      //printf(" char %c\n", c);
      if(c == 10){
         lines_nbr1++;
      }
    }

    //printf("nbr lignes: %d\n", lines_nbr1);
    lines1 = malloc(sizeof(char*)*lines_nbr1);
    nbr_char_per_line1 = malloc(sizeof(int)*lines_nbr1);
    rewind(fp1);

    // COMPTE DU NOMBRE DE CARACTERE PAR LIGNE ET STOCKAGE DS nb_char_per_line
    i = 0; //représente l'index de ligne

    while((c = fgetc(fp1)) != EOF){
      nbr_char1++;
      if(c == 10){
        nbr_char_per_line1[i] = ++nbr_char1;
        //printf("nbr char ligne %d: %d\n",i, nbr_char1);
        i++;
        nbr_char1 = 0;
      }
    }
    nbr_char_per_line1[i] = ++nbr_char1;
    //printf("nbr char ligne %d: %d\n",i, nbr_char1);

    rewind(fp1);

    for(i = 0; i < lines_nbr1; i++){
      //printf("i: %d\n", i);
      lines1[i] = malloc(sizeof(char)*nbr_char_per_line1[i]);
      for(j = 0; j < nbr_char_per_line1[i]-1; j++){
        if((c = fgetc(fp1)) != EOF){
          /*if(c == '\n')
            printf("j: %d, char: \\n\n", j);
          else
            printf("j: %d, char: %c\n", j, c);*/
          lines1[i][j] = c;
        }
      }
      lines1[i][nbr_char_per_line1[i]-1] = '\0';

      if(lines1[i][nbr_char_per_line1[i]-2])
    }

    for(i = 0; i < )


    fclose(fp1);
    fclose(fp2);
    return 0;
}

//FILE *tmpfile(void);
//int setvbuf(FILE *stream, char* buf, int mode, size_t size);
/*
*   mode:   _IOFBF tamponnage complet
*           _IOLBF tamponnage par lignes de fichier
*           _IONBF ne provoque pas de tamponnage
*/
//int fseek ( FILE * stream, long int offset, int origin ); Reposition stream position indicator
//long int ftell ( FILE * stream ); Get current position in stream
//size_t fread ( void * ptr, size_t size, size_t count, FILE * stream ); Read block of data from stream
//void rewind ( FILE * stream ); Set position of stream to the beginning
