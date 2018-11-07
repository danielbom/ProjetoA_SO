/*

Filas(Queue) são estruturas de dados utilizadas para simular algumas situações reais.

*/

#include "NoSent.h"

typedef struct
{
    NoSent *Topo;
    int tam;
    size_t size;
} Queue;

/* CONSTRUTOR E DESTRUTOR */
Queue *new_Queue(size_t size); // OK
void delete_Queue(Queue **F);  // OK

/* FUNCOES DE INSERCAO */
NoSent *push_Queue(Queue *F, void *elem);                         // OK
static NoSent *push_ant_Queue(Queue *F, void *elem, NoSent *pos); // OK

/* FUNCOES DE REMOCAO */
NoSent *pop_Queue(Queue *F);                        // OK
static NoSent *pop_in_Queue(Queue *F, NoSent *pos); // OK

void clear_Queue(Queue *F); // OK

/* FUNCOES AUXILIARES */
void reverse_Queue(Queue **F);                                 // OK
void copy_Queue(Queue *dest, const Queue *fonte);              // OK
void swap_Queue(Queue *F1, Queue *F2);                         // OK
void print_Queue(const Queue *F, void (*print)(const void *)); // OK
bool is_empty_Queue(const Queue *F);

/* IMPLEMENTACOES Queue */
Queue *new_Queue(size_t size)
{
    if (SizeError(size, "new_Queue"))
        return NULL;
    Queue *F = (Queue *)malloc(sizeof(Queue));
    F->Topo = create_Sent();
    F->tam = 0;
    F->size = size;
    return F;
}
void delete_Queue(Queue **F)
{
    if (NullPointerError(F, "delete_Queue"))
        return;
    if (NullPointerError(*F, "delete_Queue"))
        return;
    clear_Queue(*F);
    delete_NoSent(&((*F)->Topo));
    free(*F);
    *F = NULL;
}

NoSent *push_Queue(Queue *F, void *elem)
{
    return push_ant_Queue(F, elem, F->Topo);
}

static NoSent *push_ant_Queue(Queue *F, void *elem, NoSent *pos)
{
    if (NullPointerError(F, "delete_Queue"))
        return NULL;
    if (NullPointerError(elem, "delete_Queue"))
        return NULL;
    if (NullPointerError(pos, "delete_Queue"))
        return NULL;

    NoSent *novo = new_NoSent(elem, F->size);

    novo->prox = pos->prox;
    novo->ant = pos;
    pos->prox->ant = novo;
    pos->prox = novo;

    F->tam++;

    return novo;
}

NoSent *pop_Queue(Queue *F)
{
    return pop_in_Queue(F, F->Topo->ant);
}

static NoSent *pop_in_Queue(Queue *F, NoSent *pos)
{
    if (NullPointerError(F, "delete_Queue"))
        return NULL;
    if (NullPointerError(pos, "delete_Queue"))
        return NULL;
    if (is_empty_Queue(F))
        return NULL;

    pos->ant->prox = pos->prox;
    pos->prox->ant = pos->ant;

    pos->prox = pos->ant = NULL;

    F->tam--;

    return pos;
}

void clear_Queue(Queue *F)
{
    if (NullPointerError(F, "clear_Queue"))
        return;
    NoSent *aux = pop_Queue(F);
    while (aux != NULL)
    {
        delete_NoSent(&aux);
        aux = pop_Queue(F);
    }
}

void reverse_Queue(Queue **F)
{
    if (NullPointerError(F, "reverse_Queue"))
        return;
    if (NullPointerError(*F, "reverse_Queue"))
        return;
    NoSent *aux = pop_Queue(*F);
    Queue *T = new_Queue((*F)->size);
    while (aux != NULL)
    {
        push_ant_Queue(T, aux->dado, T->Topo->ant);
        delete_NoSent(&aux);
        aux = pop_Queue(*F);
    }
    delete_Queue(F);
    *F = T;
}

void copy_Queue(Queue *dest, const Queue *fonte)
{
    if (NullPointerError(dest, "copy_Queue"))
        return;
    if (NullPointerError(fonte, "copy_Queue"))
        return;

    if (dest->tam != 0)
        clear_Queue(dest);

    NoSent *aux = fonte->Topo->ant;
    while (aux != fonte->Topo)
    {
        push_Queue(dest, aux->dado);
        aux = aux->ant;
    }
    dest->size = fonte->size;
}

void swap_Queue(Queue *F1, Queue *F2)
{
    if (NullPointerError(F1, "swap_Queue"))
        return;
    if (NullPointerError(F2, "swap_Queue"))
        return;
    if (F1->size != F2->size)
        return;
    Queue *aux = new_Queue(F1->size);
    copy_Queue(aux, F1);
    copy_Queue(F1, F2);
    copy_Queue(F2, aux);
}

void print_Queue(const Queue *F, void (*print)(const void *))
{
    if (NullPointerError(F, "print_Queue"))
        return;
    NoSent *aux = F->Topo->prox;
    printf("( ");
    while (aux != F->Topo)
    {
        print(aux->dado);
        printf(", ");
        aux = aux->prox;
    }
    printf(")");
}

bool is_empty_Queue(const Queue *F)
{
    if (NullPointerError(F, "is_empty_Queue"))
        return false;
    return F->tam == 0;
}