#ifndef LINKED_LIST
#define LINKED_LIST


typedef struct s_maillon{
  int line_index;
  char first_char;
  struct s_maillon* next;
}t_maillon;

t_maillon* new_maillon(int,char);

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

/*Add an s_maillon at the end of the linked_list */
void linked_list_append(t_maillon** list, int index, char fc);
/*Insert at any place between 0 and linked_list_size() */
void linked_list_insert(t_maillon** list, int line_index, char fc, int pos);
/* Remove the s_maillon at index position, if index is in [0, linked_list_size()] */
void linked_list_remove_indice(t_maillon** list, unsigned int index);
/* Remove first s_maillon containing the data value. */
void linked_list_remove_value(t_maillon** list, int data);
/* Remove all s_maillon containing the data value. */
void linked_list_remove_all(t_maillon** list, int data);

//Return pos for linked_list_insert in order to get an ordered list by t_maillon->line_index
int linked_get_insert_pos(t_maillon* t, int line_index);

#endif
