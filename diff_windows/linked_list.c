#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
/* Implements your functions here.*/

t_maillon* new_maillon(int charLength){
  t_maillon *t;
  t = (t_maillon*)malloc(sizeof(t_maillon));
  t->datas = malloc(sizeof(char)*charLength);
  t->next = NULL;
  printf("cr\212ation pointeur %p de valeur %s\n", t, t->datas);
  return t;
}

unsigned int linked_list_size(t_maillon* t){
  //printf("getSize\n");
  if(!t) return 0;
  unsigned int size = 1;
  t_maillon* new_t;
  new_t = t;
  while(new_t->next != NULL){
    size++;
    new_t = new_t->next;
  }
  return size;
}

int linked_list_get_by_position(t_maillon* t, unsigned int pos, int* find){
  //printf("ok1\n");
  int i;
  t_maillon* new_t;
  new_t = t;
  unsigned int size = linked_list_size(new_t);
  if(pos < size && pos >= 0){
    for(i = 0; i < pos; i++){
      //printf("boucle\n");
      new_t = new_t->next;
    }
    //printf("ok2\n");
    *find = 1;
    return new_t->datas;
  }else{
    *find = 0;
    return 0;
  }
}

int linked_list_get_by_value(t_maillon* t, int value){
  t_maillon* new_t;
  new_t = t;
  int pos = 0;

  while(new_t->datas != value){
    pos++;
    new_t = new_t->next;
    if(new_t == NULL){
      return (-1);
    }
  }
  return pos;
}

void linked_list_display(t_maillon* t){
  //printf("display\n");
  t_maillon* new_t;
  new_t = t;

  do{

  }while((new_t = new_t->next) != NULL);
  printf("\n");
  return;
}

void linked_list_free(t_maillon** t){
  printf("free\n");
  t_maillon** address = t;
  t_maillon* new_t = *address;
  t_maillon* t_remove;

  while((t_remove = new_t)){
    printf("lib\212ration dynamique %p de valeur %s et pointe sur %p\n", t_remove, t_remove->datas, t_remove->next);
    free(t_remove->datas);
    new_t = new_t->next;
    free(t_remove);
  }
  return;
}
