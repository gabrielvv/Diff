#include <stdio.h>
#include <stdlib.h>
#include "contiguous_list.h"
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
    printContent(myCustomFile);

    fp2 = fopen(argv[2], "r");
    c_file *myCustomFile2 = new_c_file(fp2);
    setParams(myCustomFile2);
    printContent(myCustomFile2);


    t_maillon** tab = malloc(sizeof(t_maillon*)*2);

    tab = getEqualLines(myCustomFile, myCustomFile2, tab);

    printf("Display tab0\n");
    linked_list_display(tab[0]);
    printf("Display tab1\n");
    linked_list_display(tab[1]);

  fclose(fp1);
  fclose(fp2);
  return 0;
}
