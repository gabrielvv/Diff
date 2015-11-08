#ifndef STRINGFILE_H_INCLUDED
#define STRINGFILE_H_INCLUDED

/**************************************************
* Program        : command diff                  *
* Description    :                               *
* Author         : Fournier David                *
*                  Gabriel Vautrin               *
*                  Bordage Mickael               *
* Date           : 07/11/2015                    *
* Version        : V1.0                          *
*************************************************/


typedef struct s_String{
    char* datas;
    unsigned int max;
    unsigned int lenght;
}c_String;


c_String* string_create(unsigned int);
void string_display(c_String*);
void string_append(c_String*,char*);
int line_count(FILE*);
int string_lenght(char* chaine);


/**************************************************************
* FUNCTION string_create
* Set the lenght of the Sring
***************************************************************/
c_String* string_create(unsigned int max){
    c_String* t = (c_String*) malloc(sizeof(c_String));
    char* ini = (char*) malloc(sizeof(char)*max);
    t->datas = ini;
    t->max = max;
    t->lenght = 0;
    return t;
}

/**************************************************************
* FUNCTION string_append
* fills the chain
***************************************************************/
void string_append(c_String* list, char* value){
    if(list->lenght > list-> max){
        printf("Liste trop petite\n");
    }
    else{
        int i =0;
        list->max++;
        while(value[i] != '\0')
        {
            list->datas[i] = value[i];
            i++;
            list->lenght++;
        }
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
* FUNCTION string_lenght
* return the lenght of a String
***************************************************************/
int string_lenght(char* chaine){
    int nb_character =0;
    char current_char =0;

    do{
        current_char = chaine[nb_character];
        nb_character++;
    }while(current_char != '\0');
    nb_character--;
    return nb_character;

}
/**************************************************************
* FUNCTION string_display
* display a String
***************************************************************/
void string_display(c_String* list){
    if (list && list->lenght){
        int i=0;
        for(i=0 ; i< list->lenght-1 ; i++){

          printf("%c",list->datas[i]);
        }
        printf("\n");
    }
}
#endif // STRING_H_INCLUDED
