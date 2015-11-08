#include <stdio.h>
#include <stdlib.h>
#include "stringfile.h"
#include "diffoption.h"

/**************************************************
* Program        : command diff                  *
* Description    :                               *
* Author         : Fournier David                *
*                  Gabriel Vautrin               *
*                  Bordage Mickael               *
* Date           : 07/11/2015                    *
* Version        : V1.0                          *
*************************************************/


int main()
{
    FILE* fichier1;
    FILE* fichier2;
    fichier1 = fopen("Test1.txt", "r");
    fichier2 = fopen("Test2.txt","r");
    char chaine1[20]="";
    char chaine2[20]="";
    int i=0;
    c_String* list1[line_count(fichier1)];
    fseek(fichier1,0, SEEK_SET);
    c_String* list2[line_count(fichier2)];
    fseek(fichier2,0, SEEK_SET);

    if (fichier1 != NULL)
    {
        while (fgets(chaine1, 100, fichier1) != NULL)
        {
            i++;
            list1[i] = string_create(string_lenght(chaine1));
            string_append(list1[i],chaine1);
            string_display(list1[i]);
        }
    }
    else
        printf("Impossible d'ouvrir le fichier Test1.txt\n");

    if (fichier2 != NULL)
    {
        i=0;
        while (fgets(chaine2, 100, fichier2) != NULL) // On lit le fichier tant qu'on ne reçoit pas d'erreur (NULL)
        {
            i++;
            list2[i] = string_create(string_lenght(chaine2));

            string_append(list2[i],chaine2);
            string_display(list2[i]);

        }
    }
    else
        printf("Impossible d'ouvrir le fichier Test2.txt\n");

        defaultmode(*&list1,*&list2);
    return 0;
}
