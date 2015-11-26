#ifndef CONTIGUOUS_LIST
#define CONTIGUOUS_LIST

/**************************************************************
* STRUCTURE s_list
* ------------------------------------------------------------
* a contiguous list's implementation
*
* max       : the maximum datas' length available in the contiguous list
* length    : the current datas' length
* datas     : data
*
***************************************************************/
typedef struct s_list{
    int* datas;
    unsigned int max;
    unsigned int length;
}t_list;



/**************************************************************
* FUNCTION list_create
* ------------------------------------------------------------
* contiguous list initialisation
*
* max : the maximum datas' length available in the contiguous list
*
***************************************************************/
t_list* list_create(unsigned int);

/**************************************************************
* FUNCTION list_free
* ------------------------------------------------------------
* free the memory occupied by the list
* Delete datas
*
* tl : the contiguous list to delete
*
***************************************************************/
void list_free(t_list* tl);

/**************************************************************
* FUNCTION list_display
* ------------------------------------------------------------
* Display the datas
*
* tl : the contiguous list to display
*
***************************************************************/
void list_display(t_list*);

/**************************************************************
* FUNCTION list_remove
* ------------------------------------------------------------
* Remove an element from the list according to its index
*
* tl    : the contiguous list whose element to remove
* index : the element's position
***************************************************************/
void list_remove(t_list*,int index);

/**************************************************************
* FUNCTION list_remove_all_from
* ------------------------------------------------------------
* Remove all elements from a position to the end of the list
*
* tl    : the contiguous list whose elements to remove
* index : the first element's position
***************************************************************/
void list_remove_all_from(t_list*,int index);
void list_append(t_list*,int);
void list_insert(t_list*,int index,int value);
t_list* list_concat(t_list*,...);

/**************************************************************
* FUNCTION list_datas_copy
* ------------------------------------------------------------
* Copy the datas from one list to another
*
* from    : the contiguous list whose elements to copy
* to      : the contiguous list which copies the other
***************************************************************/
void list_datas_copy(t_list* from, t_list* to);



#endif
