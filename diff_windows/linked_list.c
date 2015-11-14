#include "linked_list.h"
#include <stdlib.h>
#include <stdio.h>
/* Implements your functions here.*/

t_maillon* new_maillon(int line_index, char first_char){
  t_maillon *t;
  t = (t_maillon*)malloc(sizeof(t_maillon));
  t->first_char = first_char;
  t->line_index = line_index;
  t->next = NULL;
  printf("cr\212ation pointeur %p de fc %c\n", t, t->first_char);
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
    return new_t->line_index;
  }else{
    *find = 0;
    return 0;
  }
}

int linked_list_get_by_line_index(t_maillon* t, int line_index){
  t_maillon* new_t;
  new_t = t;
  int pos = 0;

  while(new_t->line_index != line_index){
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
    printf("Display: line_index: %d, char: %c\n",new_t->line_index, new_t->first_char);
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
    printf("lib\212ration dynamique %p de valeur %c et pointe sur %p\n", t_remove, t_remove->first_char, t_remove->next);
    //free(t_remove->datas);
    new_t = new_t->next;
    free(t_remove);
  }
  return;
}

/*Add an s_maillon at the end of the linked_list */
void linked_list_append(t_maillon** list, int line_index, char fc){
  //printf("list_append\n");

  t_maillon* t = *list;
  if(!t){
    t = malloc(sizeof(t_maillon));
    t->line_index = line_index;
    t->first_char = fc;
    t->next = NULL;
    *list = t;
    return;
    //printf("append pointer %p avec valeur %d\n", t, t->data);
    //system("pause");
  }else{
    t_maillon* new_t = malloc(sizeof(t_maillon));
    new_t->line_index = line_index;
    new_t->first_char = fc;
    new_t->next = NULL;
    while(t->next){
      //printf("boucle append\n");
      t = t->next;
    }
    t->next = new_t;
    return;
  }
}

int linked_get_insert_pos(t_maillon* t, int line_index){
  t_maillon* new_t;
  new_t = t;
  int pos = 0;
  if(new_t == NULL){
    return (-1);
  }

  while(new_t->line_index < line_index){
    pos++;
    new_t = new_t->next;
    if(new_t == NULL){
      return (-1);
    }
  }
  return pos;
}

/*Insert at any place between 0 and linked_list_size() */
void linked_list_insert(t_maillon** list, int line_index, char fc, int pos){
  //printf("list_insert\n");

  //printf("size %u", linked_list_size(*list));

  t_maillon* t = *list;

  if(pos == 0){
    if(!t){ linked_list_append(list, line_index, fc);return;}
    else{
      t_maillon* t_insert = malloc(sizeof(t_maillon));
      t_insert->line_index = line_index;
      t_insert->first_char = fc;
      t_insert->next = t;
      *list = t_insert; //le nouvel élément est tête de liste pointée par list
      return;
    }
  }else if(pos == linked_list_size(*list)){
    linked_list_append(list, line_index, fc);
    return;
  }else if(0 < pos && pos < linked_list_size(*list)){

    t_maillon* t_before = *list;
    t_maillon* t_insert = malloc(sizeof(t_maillon));
    t_insert->line_index = line_index;
    t_insert->first_char = fc;
    int i;
    for(i = 0; i < pos-1; i++){
      t_before = t_before->next;
      //printf("incrémentation insert");
    }
    //printf("insertion %p a l'pos %d\n", t_insert, i+1);
    //system("pause");
    t_maillon* t_after = t_before->next;
    t_before->next = t_insert;
    t_insert->next = t_after;
    return;
  }
}
