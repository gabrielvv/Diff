#include "stringList.h"
#include <stdio.h>
#include <stdlib.h>

/**************************************************************
* FUNCTION string_create
* Set the length of the Sring
***************************************************************/
c_String* string_create(unsigned int max){
    c_String* t = (c_String*) malloc(sizeof(c_String));
    char* ini = (char*) malloc(sizeof(char)*max);
    t->datas = ini;
    t->max = max;
    t->length = 0;
    return t;
}

/**************************************************************
* FUNCTION string_append
* fills the chain
***************************************************************/
void string_append(c_String* list, char* value){
    if(list->length > list-> max){
        printf("Liste trop petite\n");
    }
    else{
        int i =0;
        list->max++;
        while(value[i] != '\0')
        {
            list->datas[i] = value[i];
            i++;
            list->length++;
        }
        value[i+1] = '\0';
    }
}

/**************************************************************
* FUNCTION line_count
* count the number of line
***************************************************************/
int line_count(FILE* fichier ){
    int nb_line = 0;
    char c;
    while ((c = getc(fichier)) != EOF){
    if (c == '\n')
        ++nb_line;
}
    return nb_line;
}

/**************************************************************
* FUNCTION string_length
* return the length of a String
***************************************************************/
int string_length(char* chaine){
    int nb_character =0;
    char current_char =0;

    do{
        current_char = chaine[nb_character];
        nb_character++;
    }while(current_char != '\0');
    //nb_character--;
    return nb_character;

}
/**************************************************************
* FUNCTION string_display
* display a String
***************************************************************/
void string_display(c_String* list){
    if (list && list->length){
        int i=0;
        //printf("length = %d\n", list->length);
        for(i=0 ; i< list->length ; i++){
          printf("%c",list->datas[i]);
        }
        printf("\n");
    }
}
