#ifndef CONTIGUOUS_LIST
#define CONTIGUOUS_LIST

typedef struct s_list{
    char* datas;
    unsigned int max;
    unsigned int length;
}t_list;

t_list* list_create(unsigned int);
void list_display(t_list*);
void list_remove(t_list*,int index);
void list_remove_all_from(t_list*,int index);
void list_append(t_list*,char);
void list_insert(t_list*,int index,char value);
t_list* list_concat(t_list*,...);
void list_datas_copy(t_list* from, t_list* to);


#endif
