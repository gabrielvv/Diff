#include "contiguous_list_int.h"
#include <stdlib.h>
#include <stdio.h>
#include <wchar.h>
#include <stdarg.h>

void list_append(t_list* tl,int c){
    printf("DEBUG: list append\t tl->length = %d\t tl->max = %d\t index: %d\n", tl->length, tl->max, c);
    if(tl->length < tl->max && tl){
        tl->datas[tl->length++] = c;
    }else{
        printf("Erreur list_append\n");
    }

}

wchar_t* convert_to_array(t_list* tl, wchar_t* array){

  int i;
  array = malloc(sizeof(wchar_t)*tl->length);
  for(i = 0; i < tl->length; i++){

  }
  return array;
}

void list_datas_copy(t_list* from, t_list* to){

  if(from->length <= to->length){
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

void list_free(t_list* tl){
  free(tl->datas);
  free(tl);
}

void list_display(t_list* tl){
    if(tl && tl->length > 0){
        int i;
        for(i = 0; i < (tl->length-1); i++)
            printf("%d, ", tl->datas[i]);
        printf("%d\n", tl->datas[i]);
    }
}

void list_insert(t_list* tl,int index,int value)
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
        length+=list->length;
    }

    va_end(pa);

    t_list* concatList = list_create(length);

    va_start(pa, tl);

    int i = 0;
    int j;
    for(j=0;j<tl->length;j++){
        concatList->datas[i] = tl->datas[j];
        concatList->length++;
        i++;
    }

    while((list = va_arg(pa, t_list*))){
        for(j=0;j<list->length;j++){

            concatList->datas[i] = list->datas[j];
            concatList->length++;
            i++;
        }
    }
    va_end(pa);

    return concatList;
}
