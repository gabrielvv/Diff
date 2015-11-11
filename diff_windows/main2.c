#include <stdio.h>
#include <stdlib.h>
#include "contiguous_list.h"
#include "custom_file.h"
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

    /*FILE *fp1, *fp2;
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
    return 0;*/

    char tab1[8] = {'a','b','c','d','e','f','g','h'}; //contient seulement les lignes ordonnées de file 1 qu'on retrouve ds file2
    char tab2[8] = {'h','a','d','c','e','g','f','b'}; //contient seulement les lignes ordonnées de file2 qu'on retrouve ds file1
    t_list* result_list = list_create(8);
    t_list* tmp_list = list_create(8);

    int i, j, store, offset;
    char c;
    offset = 0;
    printf("tab1 de longueur: %d\ntab2 de longueur: %d\n", strlen(tab1), strlen(tab2));

    for(i = 0; i < strlen(tab1); i++){
      c = tab1[i];
      //if(i < index)
      //list_append(tmp_list, c);
      for(j = offset; j < strlen(tab2); j++){

        /*if(j < index){
          //inutile avec décalage!
          //index sauvegarde la position du dernier elmt ajouté à tmp_list
          break;*/
        if(c == tab2[j]){
          if(store){
            printf("Replace");
            tmp_list->datas[tmp_list->length-1] = c;
            store = 0;
          }else{
            list_append(tmp_list, c); //incrémente list->length
            store = (j == strlen(tab2)-1 ? 1 : 0);
            offset = j+1;
          }

          /*if(j == strlen(tab2)-1){
            replace = 1;
          }
          else{offset = j+1;replace = 0;}*/
          printf("break\n");
          break;
        }
        /*else{
          //index = j;
        }*/
      }

      if(store && tmp_list->length > result_list->length){
        result_list->length = tmp_list->length;
        result_list->datas = tmp_list->datas;
        printf("Storing new result_list:\n");
        list_display(result_list);
      }
    }
    printf("Final result_list:\n");
    list_display(result_list);
    return 0;
}
