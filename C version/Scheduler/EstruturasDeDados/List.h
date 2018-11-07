/*
 * Listas são estruturas de dados que não é boa com buscas.
 * Se precisar fazer muitas buscas, utilize outra estrutura de dados.
*/
#ifndef LIST
#define LIST

#include "NoSent.h"
#include "../Util/tipos_primarios.h"

typedef struct
{
    NoSent *Sentinela;
    int qtde;
    size_t size;
} List;

/* CONSTRUTOR E DESTRUTOR */
List *new_List(size_t size);                                     // OK 18/06/2018
List *array_to_List(void *array, int length_array, size_t size); // OK 17/07/2018
void delete_List(List **self);                                   // OK 18/07/2018

/* FUNCOES DE BUSCA */
void *index_List(List *self, int pos);      // OK 24/06/2018
NoSent *index_no_List(List *self, int pos); // OK 18/06/2018

bool contains_List(List *self, void *elem, int (*cmp)(const void *, const void *));     // OK 24/06/2018
NoSent *search_no_List(List *self, void *elem, int (*cmp)(const void *, const void *)); // OK 24/06/2018

void *max_List(List *self, int (*cmp)(const void *, const void *));      // OK 18/07/2018
void *min_List(List *self, int (*cmp)(const void *, const void *));      // OK 18/07/2018
NoSent *max_no_List(List *self, int (*cmp)(const void *, const void *)); // OK 18/07/2018
NoSent *min_no_List(List *self, int (*cmp)(const void *, const void *)); // OK 18/07/2018

/* FUNCOES DE INSERCAO */
NoSent *push_no_List(List *self, void *elem, NoSent *pos); // OK 18/06/2018
bool push_back_List(List *self, void *elem);               // OK 18/06/2018
bool push_front_List(List *self, void *elem);              // OK 18/06/2018

bool insert_List(List *self, void *elem, int pos); // OK 18/06/2018

bool update_List(List *dest, const List *font);

/* FUNCOES DE REMOCAO */
NoSent *pop_in_List(List *self, NoSent *pos); // OK 18/06/2018
NoSent *pop_back_no_List(List *self);         // OK 24/06/2018
NoSent *pop_front_no_List(List *self);        // OK 24/06/2018
bool pop_back_List(List *self);               // OK 24/06/2018
bool pop_front_List(List *self);              // OK 24/06/2018
void *pop_back_data_List(List *self);         // OK 24/06/2018
void *pop_front_data_List(List *self);        // OK 24/06/2018

bool remove_List(List *self, void *elem, int (*cmp)(const void *, const void *)); // OK 24/06/2018
bool pop_List(List *self, int pos);                                               // OK 18/06/2018
void remove_if_List(List *self, bool (*condicao)(void *));                        // OK 18/06/2018

void clear_List(List *self); // OK 18/06/2018

/* FUNCOES AUXILIARES */
void copy_List(List *dest, const List *fonte);                             // OK 18/06/2018
void swap_List(List *L1, List *L2);                                        // OK 18/07/2018
void print_List(List *self, void (*print)(const void *));                  // OK 18/06/2018
bool empyt_List(List *self);                                               // OK 18/07/2018
void unique_List(List *self, int (*cmp)(const void *, const void *));      // OK 17/07/2018
bool is_sorted_List(List *self, int (*cmp)(const void *, const void *));   // OK 22/07/2018
bool is_reversed_List(List *self, int (*cmp)(const void *, const void *)); // OK 22/07/2018
void reverse_List(List *self);                                             // OK 17/07/2018
void *List_to_array(List *self);                                           // OK 17/07/2018
bool equals_List(const List *a, const List *b);                            // TODO

double sum_List(List *self, double (*cast)(const void *));  // TODO
double mult_List(List *self, double (*cast)(const void *)); // TODO

/* ITERADORES */
NoSent *begin_List(const List *self);  // OK 17/07/2018
NoSent *last_List(const List *self);   // OK 29/08/2018
NoSent *end_List(const List *self);    // OK 17/07/2018
void next_iter_List(NoSent **no);      // OK 17/07/2018
NoSent *rbegin_List(const List *self); // OK 29/08/2018
NoSent *rlast_List(const List *self);  // OK 29/08/2018
NoSent *rend_List(const List *self);   // OK 29/08/2018
void next_riter_List(NoSent **no);     // OK 29/08/2018

/* FUNCOES DE ORDENACAO */
void sort_List(List *self, int (*cmp)(const void *, const void *));                                            // OK 17/07/2018
static void _quick_sort_List(List *self, NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *)); // OK 17/07/2018
static NoSent *_partition_List(NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *));           // OK 17/07/2018
static NoSent *_partition_List2(NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *));

/* IMPLEMENTACOES LISTA */

/* CONSTRUTOR E DESTRUTOR */
List *new_List(size_t size)
{
    if (SizeError(size, "new_List"))
        return NULL;

    List *self = (List *)malloc(sizeof(List));
    self->Sentinela = create_Sent();
    self->qtde = 0;
    self->size = size;
    return self;
}
List *array_to_List(void *array, int length_array, size_t size)
{
    if (array == NULL)
    {
        printf("\nError. The array variable must not be null.\n");
        return NULL;
    }
    if (length_array <= 0)
    {
        printf("\nError. Variable length_array must be greater than zero (0).\n");
        return NULL;
    }
    if (SizeError(size, "array_to_List"))
        return NULL;

    List *self = new_List(size);
    void *it = array;
    for (int i = 0; i < length_array; i++, it += size){
        void* new = malloc(size);
        memcpy(new, it, size);
        push_back_List(self, new);
    }
    return self;
}

List *new_random_int_List(int begin, int end, int array_length)
{
    if (begin > end)
        swap(&begin, &end, sizeof(int));

    List *self = new_List(sizeof(int));

    int range = end - begin;
    int *a;
    srand((unsigned)time(NULL));
    for (int i = 0; i < array_length; i++)
    {
        a = (int *)malloc(sizeof(int));
        *a = (rand() % range) + begin;
        push_back_List(self, a);
    }

    return self;
}

void delete_List(List **self)
{
    if (NullPointerError(*self, "delete_List"))
        return;

    clear_List(*self);
    delete_NoSent(&((*self)->Sentinela));
    free(*self);
    *self = NULL;
}

/* FUNCOES DE BUSCA */
NoSent *index_no_List(List *self, int pos)
{
    if (NullPointerError(self, "index_no_List"))
        return NULL;
    if (IndexOutOfTheRangeError(pos, -self->qtde, self->qtde + 1, "index_no_List"))
        return NULL;
    if (empyt_List(self))
        return NULL;

    if (pos < 0)
        pos += self->qtde + 1;

    NoSent *aux;
    if (pos > self->qtde / 2)
    {
        aux = rbegin_List(self);
        for (int i = self->qtde; i > pos; i--)
            next_riter_List(&aux);
    }
    else
    {
        aux = begin_List(self);
        for (int i = 1; i < pos; i++)
            next_iter_List(&aux);
    }
    return aux;
}
void *index_List(List *self, int pos)
{
    NoSent *aux = index_List(self, pos);
    return aux != NULL ? aux->dado : NULL;
}

NoSent *search_no_List(List *self, void *elem, int (*cmp)(const void *, const void *))
{
    if (NullPointerError(self, "search_no_List"))
        return NULL;

    NoSent *aux = begin_List(self);
    while (aux != end_List(self))
    {
        if (EQUAL_TO(cmp(elem, aux->dado)))
            return aux;
        next_iter_List(&aux);
    }
    return NULL;
}
bool contains_List(List *self, void *elem, int (*cmp)(const void *, const void *))
{
    return search_no_List(self, elem, cmp) != NULL;
}

NoSent *max_no_List(List *self, int (*cmp)(const void *, const void *))
{
    if (NullPointerError(self, "max_no_List"))
        return NULL;
    if (empyt_List(self))
        return NULL;

    NoSent *aux = begin_List(self);
    NoSent *max = aux;
    while (aux != end_List(self))
    {
        if (GREATER_THAN(cmp(aux->dado, max->dado)))
            max = aux;
        next_iter_List(&aux);
    }
    return max;
}
void *max_List(List *self, int (*cmp)(const void *, const void *))
{
    NoSent *aux = max_no_List(self, cmp);
    if (aux != NULL)
    {
        return aux->dado;
    }
    return NULL;
}

NoSent *min_no_List(List *self, int (*cmp)(const void *, const void *))
{
    if (NullPointerError(self, "min_no_List"))
        return NULL;
    if (empyt_List(self))
        return NULL;

    NoSent *aux = begin_List(self);
    NoSent *min = aux;
    while (aux != end_List(self))
    {
        if (LESS_THAN(cmp(min->dado, aux->dado)))
            min = aux;
        next_iter_List(&aux);
    }
    return min;
}
void *min_List(List *self, int (*cmp)(const void *, const void *))
{
    NoSent *aux = min_no_List(self, cmp);
    return aux != NULL ? aux->dado : NULL;
}

/* FUNCOES DE INSERCAO */
NoSent *push_no_List(List *self, void *elem, NoSent *pos)
{
    // Coloca o elemento 'elem' apos o no 'pos' na Lista 'self'
    if (NullPointerError(self, "push_no_List"))
        return NULL;
    if (NullPointerError(elem, "push_no_List"))
        return NULL;

    if (pos == NULL)
        return NULL;

    NoSent *novo = new_NoSent(elem, self->size);

    novo->prox = pos->prox;
    novo->ant = pos;
    pos->prox->ant = novo;
    pos->prox = novo;

    self->qtde++;

    return novo;
}
bool push_back_List(List *self, void *elem)
{
    return push_no_List(self, elem, last_List(self)) != NULL;
}
bool push_front_List(List *self, void *elem)
{
    return push_no_List(self, elem, end_List(self)) != NULL;
}

bool insert_List(List *self, void *elem, int pos)
{
    NoSent *index = index_no_List(self, pos);
    return index != NULL ? push_no_List(self, elem, index) != NULL : false;
}

bool update_List(List *dest, const List *font)
{
    if (NullPointerError(dest, "push_no_List"))
        return false;
    if (NullPointerError(font, "push_no_List"))
        return false;
    if (dest->size != font->size)
    {
        printf("\nError. Size of the List must be equal.\n");
        return false;
    }

    NoSent *aux = begin_List(font);
    while (aux != font->Sentinela)
    {
        push_back_List(dest, aux->dado);
        next_iter_List(&aux);
    }
}

/* FUNCOES DE REMOCAO */
NoSent *pop_in_List(List *self, NoSent *pos)
{
    if (NullPointerError(self, "pop_in_List"))
        return NULL;
    if (NullPointerError(pos, "pop_in_List"))
        return NULL;
    if (pos == end_List(self))
        return NULL;

    // Desenlaçando os nós
    pos->ant->prox = pos->prox;
    pos->prox->ant = pos->ant;

    // Removendo as referências
    pos->prox = pos->ant = NULL;

    self->qtde--;

    return pos;
}

NoSent *pop_back_no_List(List *self)
{
    return pop_in_List(self, last_List(self));
}
bool pop_back_List(List *self)
{
    NoSent *aux = pop_back_no_List(self);
    if (aux != NULL)
    {
        delete_NoSent(&aux);
        return true;
    }
    return false;
}
void *pop_back_data_List(List *self)
{
    NoSent *aux = pop_back_no_List(self);
    void *dado = NULL;
    if (aux != NULL)
    {
        dado = memcpy(malloc(aux->size), aux->dado, aux->size);
        delete_NoSent(&aux);
    }
    return dado;
}

NoSent *pop_front_no_List(List *self)
{
    return pop_in_List(self, begin_List(self));
}
bool pop_front_List(List *self)
{
    NoSent *aux = pop_front_no_List(self);
    if (aux != NULL)
    {
        delete_NoSent(&aux);
        return true;
    }
    return false;
}
void *pop_front_data_List(List *self)
{
    NoSent *aux = pop_front_no_List(self);
    void *dado = NULL;
    if (aux != NULL)
    {
        dado = memcpy(malloc(aux->size), aux->dado, aux->size);
        delete_NoSent(&aux);
    }
    return dado;
}
bool remove_List(List *self, void *elem, int (*cmp)(const void *, const void *))
{
    NoSent *aux = pop_in_List(self, search_no_List(self, elem, cmp));
    if (aux != NULL)
    {
        delete_NoSent(&aux);
        return true;
    }
    return false;
}
bool pop_List(List *self, int pos)
{
    NoSent *aux = pop_in_List(self, index_no_List(self, pos));
    if (aux != NULL)
    {
        delete_NoSent(&aux);
        return true;
    }
    return false;
}
void remove_if_List(List *self, bool (*condicao)(void *))
{
    if (NullPointerError(self, "remove_if_List"))
        return;

    NoSent *aux = begin_List(self);
    while (aux != end_List(self))
    {
        if (condicao(aux->dado))
        {
            next_iter_List(&aux);
            NoSent *tmp = pop_in_List(self, aux->ant);
            delete_NoSent(&tmp);
        }
        else
            next_iter_List(&aux);
    }
}

void clear_List(List *self)
{
    if (NullPointerError(self, "clear_List"))
        return;
    NoSent *aux = pop_back_no_List(self);
    while (aux != NULL)
    {
        delete_NoSent(&aux);
        aux = pop_front_no_List(self);
    }
}

/* FUNCOES AUXILIARES */
void copy_List(List *dest, const List *font)
{
    if (NullPointerError(dest, "copy_List"))
        return;
    if (NullPointerError(font, "copy_List"))
        return;

    if (dest->size != font->size)
    {
        printf("\nError. Size of the List must be equal.\n");
        return;
    }

    clear_List(dest);

    NoSent *aux = begin_List(font);
    while (aux != font->Sentinela)
    {
        push_back_List(dest, aux->dado);
        next_iter_List(&aux);
    }
}
void swap_List(List *L1, List *L2)
{
    if (NullPointerError(L1, "swap_List"))
        return;
    if (NullPointerError(L2, "swap_List"))
        return;

    NoSent *aux;
    int len2 = L2->qtde;
    while (!empyt_List(L1))
    {
        aux = pop_front_no_List(L1);
        push_back_List(L2, aux->dado);
        delete_NoSent(&aux);
    }
    while (len2--)
    {
        aux = pop_front_no_List(L2);
        push_back_List(L1, aux->dado);
        delete_NoSent(&aux);
    }
}
void print_List(List *self, void (*print)(const void *))
{
    if (NullPointerError(self, "print_List"))
        return;

    NoSent *aux = begin_List(self);
    printf("[");
    while (aux->prox != end_List(self))
    {
        printf(" ");
        print(aux->dado);
        printf(",");
        next_iter_List(&aux);
    }
    if (aux != end_List(self))
    {
        printf(" ");
        print(aux->dado);
        printf(" ");
    }
    printf("]");
}
bool empyt_List(List *self)
{
    if (NullPointerError(self, "empyt_List"))
        return true;
    return self->qtde == 0;
}
bool is_sorted_List(List *self, int (*cmp)(const void *, const void *))
{
    if (NullPointerError(self, "is_sorted_List"))
        return false;

    // A iteração é feita no sentido convencional ( Direita -> Esquerda )
    NoSent *aux = begin_List(self);
    while (aux->prox != end_List(self))
    {
        if (GREATER_THAN(cmp(aux->dado, aux->prox->dado)))
            return false;
        next_iter_List(&aux);
    }
    return true;
}
bool is_reversed_List(List *self, int (*cmp)(const void *, const void *))
{
    if (NullPointerError(self, "is_reversed_List"))
        return false;

    // A iteração é feita no sentido reverso ( Esquerda -> Direita  )
    NoSent *aux = last_List(self);
    while (aux->ant != end_List(self))
    {
        if (GREATER_THAN(cmp(aux->dado, aux->ant->dado)))
            return false;
        aux = aux->ant;
    }
    return true;
}
void unique_List(List *self, int (*cmp)(const void *, const void *))
{
    if (NullPointerError(self, "unique_List"))
        return;

    sort_List(self, cmp);
    NoSent *aux = begin_List(self); // Primeiro elemento da Lista
    while (aux->prox != end_List(self) && aux != end_List(self))
    {
        while (aux->prox != end_List(self) && EQUAL_TO(cmp(aux->dado, aux->prox->dado)))
        {
            pop_in_List(self, aux->prox);
        }
        next_iter_List(&aux);
    }
}
void reverse_List(List *self)
{
    if (NullPointerError(self, "reverse_List"))
        return;

    NoSent *esq = begin_List(self);
    NoSent *dir = last_List(self);
    if (IS_ODD(self->qtde))
    {
        while (esq != dir)
        {
            swap_NoSent(esq, dir);
            esq = esq->prox;
            dir = dir->ant;
        }
    }
    else
    {
        while (esq->ant != dir)
        {
            swap_NoSent(esq, dir);
            esq = esq->prox;
            dir = dir->ant;
        }
    }
}
void *List_to_array(List *self)
{
    if (NullPointerError(self, "List_to_array"))
        return NULL;
    void *r = calloc(self->qtde, self->size);
    NoSent *aux = begin_List(self);
    void *inc = r;
    for (int i = 0; i < self->qtde && aux != end_List(self); i++, inc += self->size)
    {
        memcpy(inc, aux->dado, self->size);
        next_iter_List(&aux);
    }
    return r;
}

/* ITERADORES */
NoSent *rbegin_List(const List *self)
{
    return last_List(self);
}
NoSent *rend_List(const List *self)
{
    return end_List(self);
}
NoSent *rlast_List(const List *self)
{
    return begin_List(self);
}
void next_riter_List(NoSent **no)
{
    *no = (*no)->ant;
}
NoSent *begin_List(const List *self)
{
    return self->Sentinela->prox;
}
NoSent *last_List(const List *self)
{
    return self->Sentinela->ant;
}
NoSent *end_List(const List *self)
{
    return self->Sentinela;
}
void next_iter_List(NoSent **no)
{
    *no = (*no)->prox;
}

/* FUNCOES DE ORDENACAO */
void qsort_List(List *self, int (*cmp)(const void *, const void *))
{
    // Gasta o dobro de memória q o sort_List, porém é muito mais rapido
    // Para tamanho de Lista menores que 1e6, nao vale muito a pena
    if (NullPointerError(self, "qsort_List"))
        return;
    void *ar = List_to_array(self);
    qsort(ar, self->qtde, self->size, cmp);
    NoSent *aux = begin_List(self);
    void *inc = ar;
    for (int i = 0; i < self->qtde; i++, inc += self->size)
    {
        memcpy(aux->dado, inc, self->size);
        next_iter_List(&aux);
    }
    free(ar);
}
void sort_List(List *self, int (*cmp)(const void *, const void *))
{
    // Ordenação nao estavel dos elementos da Lista
    // * É possível fazer uma ordenação estável se a função de comparação contiver os critérios de desempates implementados
    if (NullPointerError(self, "sort_List"))
        return;
    // Fazer esta verificação impede um dos piores caso do quick_sort (quadratico)
    if (!is_sorted_List(self, cmp))
        _quick_sort_List(self, begin_List(self), last_List(self), cmp);
}

static void _quick_sort_List(List *self, NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *))
{
    /*
     * A função abaixo é a versão em python que baseou esta versão.
     * 
     * def quick_sort_(vet, i, f):
     *     if i < f:
     *         p = partition(vet, i, f)
     *         quick_sort_(vet, i, p-1)
     *         quick_sort_(vet, p+1, f)
    */
    if (inicio != fim)
    {
        NoSent *p = _partition_List(inicio, fim, cmp);

        if (p != inicio)
            _quick_sort_List(self, inicio, p->ant, cmp); // quick_sort para esquerda
        if (p != fim)
            _quick_sort_List(self, p->prox, fim, cmp); // quick_sort para direita
    }
}
static NoSent *_partition_List(NoSent *inicio, NoSent *fim, int (*cmp)(const void *, const void *))
{
    /*
     * A função abaixo é a versão em python que baseou esta versão.
     * 
     * def partition(vet, inicio, fim):
     *     pivo = vet[fim]
     *     i = inicio-1
     *     for j in range(inicio, fim):
     *         if vet[j] < pivo:
     *             i += 1
     *             vet[j], vet[i] = vet[i], vet[j]
     *     vet[fim], vet[i+1] = vet[i+1], vet[fim]
     *     return i + 1
    */
    // As tres proximas linhas tentam melhorar um pouquinho a eficiencia do algoritmo
    // mas, se mostram irrelevantes

    LESS_THAN(cmp(fim->ant->dado, fim)) ? swap_NoSent(fim, fim->ant) : 0;
    while (LESS_THAN(cmp(inicio->dado, fim->dado)))
        inicio = inicio->prox;

    NoSent *i = inicio->ant; // i: representa o ultimo menor elemento encontrado
    while (inicio != fim)
    {
        if (LESS_THAN(cmp(inicio->dado, fim->dado)))
        {
            i = i->prox;
            swap_NoSent(inicio, i);
        }
        inicio = inicio->prox;
    }
    swap_NoSent(fim, i->prox);
    return i->prox;
}

#endif