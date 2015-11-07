#include <stdio.h>
#include <stdlib.h>
#include "linked_list.h"
#include "custom_file.h"

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
    //printContent(myCustomFile);

    fp2 = fopen(argv[2], "r");
    c_file *myCustomFile2 = new_c_file(fp2);
    setParams(myCustomFile2);
    //printContent(myCustomFile2);
    printf("%d", line_comp(myCustomFile2, myCustomFile, 0));
    printf("%d", line_comp(myCustomFile2, myCustomFile, 1));
    fclose(fp1);
    fclose(fp2);
    return 0;
}
