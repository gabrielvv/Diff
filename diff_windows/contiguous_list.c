#include "contiguous_list.h"
#include <stdlib.h>
#include <stdio.h>
#include <stdarg.h>

void list_append(t_list* tl,char c){

    if(tl->length < tl->max && tl){
        tl->datas[tl->length++] = c;
        printf("Append %c\n", c);
    }else{
        printf("Erreur list_append\n");
    }

}

void list_datas_copy(t_list* from, t_list* to){

  if(from->length <= to->length){
    printf("datas copy");
    int i;
    for(i = 0; i < from->length; i++){
      to->datas[i] = from->datas[i];
    }
  }
}

t_list* list_create(unsigned int max){
    t_list* tl = malloc(sizeof(t_list));
    tl->datas = malloc(max*(sizeof(int)));
    tl->length = 0;
    tl->max = max;
    return tl;
}

void list_display(t_list* tl){
    //printf("display :\n");;
    if(tl && tl->length > 0){
        //printf("display :\n");;
        int i;
        for(i = 0; i < (tl->length-1); i++)
            printf("%c, ", tl->datas[i]);
        printf("%c\n", tl->datas[i]);
    }
}

void list_insert(t_list* tl,int index,char value)
{

    if(tl && (tl->length < tl->max) && index <= tl->max)
    {
        //OU partir de la fin  du tableau +1
        //printf("passage dans insert\n");
        int datas[tl->length+1];
        int i;
        for(i=0;i<tl->length+1;i++){
            if(i == index){
                datas[i] = value;
            }
            else if(i<index){
                datas[i] = tl->datas[i];
            }
            else{
                datas[i] = tl->datas[i-1];
            }
        }
        for(i=0;i<tl->length+1;i++){
            tl->datas[i] = datas[i];
        }
        tl->length++;

    }

}

void list_remove(t_list* tl, int index){

    if(tl && (tl->length <= tl->max) && (index <= tl->length-1))
    {
      int i = index;
      for(;i < tl->length-1; i++){
        tl->datas[i] = tl->datas[i+1];
      }
      tl->length--;
    }
}

//Remove all element from index to the end of datas
void list_remove_all_from(t_list* tl, int index){

    if(tl && (tl->length <= tl->max) && (index <= tl->length-1))
    {
        int i = tl->length-1;
        for(;i >= index; i--){
          tl->length--;
        }
    }
}

t_list* list_concat(t_list* tl,...){

    va_list pa;

    t_list* list = malloc(sizeof(t_list));
    va_start(pa, tl); //pointe sur le premier argument NON nommé

    int length = 0;
    length += tl->length;

    while((list = va_arg(pa, t_list*))){
        //list_display(list);
        length+=list->length;
    }

    va_end(pa);

    //printf("Total length = %d", length);
    t_list* concatList = list_create(length);


    va_start(pa, tl);

    int i = 0;
    int j;
    for(j=0;j<tl->length;j++){
        //printf("boucle\n");
        concatList->datas[i] = tl->datas[j];
        concatList->length++;
        i++;
    }

    while((list = va_arg(pa, t_list*))){
        for(j=0;j<list->length;j++){


            concatList->datas[i] = list->datas[j];
            //printf("boucle index %d, data: %d\n", i, concatList->datas[i]);
            concatList->length++;
            i++;
        }
        //list_display(concatList);
    }
    va_end(pa);
    /* traitement des param�tres selon la fonction */

    return concatList;
}
