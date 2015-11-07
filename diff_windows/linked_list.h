#ifndef LINKED_LIST
#define LINKED_LIST


typedef struct s_maillon{
  char* datas;
  struct s_maillon* next;
}t_maillon;

t_maillon* new_maillon(int charLength);

// renvoyer la taille de la liste
unsigned int linked_list_size(t_maillon*);

//afficher à l'écran le contenu de la liste chainée tel que dans l'exemple
void linked_list_display(t_maillon*);

//retournera la valeur à la position recherchée. attribuera a la variable *find : 1 si trouvé, 0 si non trouvé.( 0 <= position < size() )
int linked_list_get_by_position(t_maillon*, unsigned int, int* find);

//retourner la position de la première occurence de la valeur trouvée. -1 si non trouvé
int linked_list_get_by_value(t_maillon*, int);


//libérer l'espace occupé en mémoire par la liste chaînée (tous les maillons)
void linked_list_free(t_maillon**);

#endif
