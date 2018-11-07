// Preciso pesar em como iterar sobre o array...

#ifndef ARRAYLIST
#define ARRAYLIST

#include "../Util/tipos_primarios.h"
#include "../Util/array.h"

typedef struct
{
    void *array; // vetor de ponteiros
    int qtde;
    int tam;
    size_t size;
} arraylist;

/* CONSTRUTOR E DESTRUTOR */
arraylist *new_arraylist(size_t size, int tam);                        // TODO
arraylist *new_random_arraylist(int begin, int end, int array_length); // TODO
arraylist *new_zeros_arraylist(int array_length);                      // TODO
void realloc_arraylist(arraylist *ar, int tam);                        // TODO
void delete_arraylist(arraylist **ar);                                 // TODO

/* FUNCOES DE BUSCA */
void *index_arraylist(arraylist *ar, int pos);                                              // TODO
bool conteins_arraylist(arraylist *ar, void *elem, int (*cmp)(const void *, const void *)); // TODO
int find_arraylist(arraylist *ar, void *elem, int (*cmp)(const void *, const void *));      // TODO

void *max_arraylist(arraylist *ar, int (*cmp)(const void *, const void *)); // TODO
void *min_arraylist(arraylist *ar, int (*cmp)(const void *, const void *)); // TODO

// Preciso pensar no caso das funcoes de insercao e remocao

/* FUNCOES DE INSERCAO */
bool push_back_arraylist(arraylist *ar, void *elem);  // TODO
bool push_front_arraylist(arraylist *ar, void *elem); // TODO

bool insert_arraylist(arraylist *ar, void *elem, int pos); // TODO

bool update_arraylist(const arraylist *dest, const arraylist *font); // TODO

/* FUNCOES DE REMOCAO */
bool pop_back_arraylist(arraylist *ar);        // TODO
bool pop_front_arraylist(arraylist *ar);       // TODO
void *pop_back_dado_arraylist(arraylist *ar);  // TODO
void *pop_front_dado_arraylist(arraylist *ar); // TODO

bool remove_arraylist(arraylist *ar, void *elem, int (*cmp)(const void *, const void *)); // TODO
bool pop_arraylist(arraylist *ar, int pos);                                               // TODO
void remove_if_arraylist(arraylist *ar, bool (*condicao)(void *));                        // TODO

void clear_arraylist(arraylist *ar); // TODO

/* FUNCOES AUXILIARES */
void print_arraylist(arraylist *ar, void (*print)(const void *));                                    // OK 03/08/2018
void print_if_arraylist(arraylist *ar, void (*print)(const void *), bool (*condicao)(const void *)); // OK 03/08/2018

bool is_sorted_arraylist(arraylist *ar, int (*cmp)(const void *, const void *));   // TODO
bool is_reversed_arraylist(arraylist *ar, int (*cmp)(const void *, const void *)); // TODO

void dup_arraylist(arraylist *fonte); // TODO

void unique_arraylist(arraylist *ar, int (*cmp)(const void *, const void *)); // OK 03/08/2018

bool empyt_arraylist(arraylist *ar); // OK 25/07/2018

void reverse_arraylist(arraylist *ar); // OK 03/08/2018

void *arraylist_to_array(arraylist *ar); // OK 03/08/2018

void swap_arraylist(arraylist *ar1, arraylist *ar2); // OK 03/08/2018

bool equals_arraylist(arraylist *ar1, arraylist *ar2); // OK 03/08/2018

/* FUNCOES DE ORDENACAO */
void sort_arraylist(arraylist *ar, int (*cmp)(const void *, const void *)); // 25/07/2018

/* IMPLEMENTACOES ARRAYLIST */

/* CONSTRUTOR E DESTRUTOR */
arraylist *new_arraylist(size_t size, int tam)
{
    arraylist *ar = (arraylist *)malloc(sizeof(arraylist));

    ar->dado = (void **)calloc(tam, size);

    ar->qtde = 0;
    ar->tam = tam;
    ar->size = size;

    return ar;
}
void realloc_arraylist(arraylist *ar, int tam) {}
void delete_arraylist(arraylist **ar) {}

/* FUNCOES AUXILIARES */
void print_arraylist(arraylist *ar, void (*print)(const void *))
{
    print_array(ar->array, ar->qtde, ar->size, print);
}

void print_if_arraylist(arraylist *ar, void (*print)(const void *), bool (*condicao)(const void *))
{
    print_if_array(ar->array, ar->qtde, ar->size, print, condicao);
}

void unique_arraylist(arraylist *ar, int (*cmp)(const void *, const void *))
{
    unique_array(ar->array, ar->qtde, ar->size, cmp);
}

bool empyt_arraylist(arraylist *ar)
{
    return ar->qtde == 0;
}

void reverse_arraylist(arraylist *ar)
{
    reverse_array(ar->array, ar->qtde, ar->size);
}

void *arraylist_to_array(arraylist *ar)
{
    return ar->array;
}

void swap_arraylist(arraylist *ar1, arraylist *ar2)
{
    pswap(ar1->array, ar2->array);
    swap(ar1->qtde, ar2->qtde, sizeof(int));
    swap(ar1->tam, ar2->tam, sizeof(int));
    swap(ar1->size, ar2->size, sizeof(size_t));
}

bool equals_arraylist(arraylist *ar1, arraylist *ar2, int (*cmp)(const void *, const void *))
{
    if (ar1->qtde != ar2->qtde)
        return false;
    return equals_array(ar1->array, ar2->array, ar1->qtde, ar1->size, cmp);
}
/* FUNCOES DE ORDENACAO */
void sort_arraylist(arraylist *ar, int (*cmp)(const void *, const void *))
{
    qsort(ar->array, ar->qtde, ar->size, cmp);
}
#endif