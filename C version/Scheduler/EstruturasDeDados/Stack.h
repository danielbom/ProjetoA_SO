/*

Pilhas são estruturas de dados utilizadas para simular algumas situações reais.

Todas as funções foram testadas pelo menor uma vez.

*/

#include "NoSent.h"

typedef struct
{
    NoSent *Topo;
    int tam;
    size_t size;
} stack;

/* CONSTRUTOR E DESTRUTOR */
stack *new_stack(size_t size);   // OK
void delete_stack(stack **self); // OK

/* FUNCOES DE INSERCAO */
NoSent *push_stack(stack *self, void *elem);                         // OK
static NoSent *push_ant_stack(stack *self, void *elem, NoSent *pos); // OK

/* FUNCOES DE REMOCAO */
void *pop_stack(stack *self);
NoSent *pop_no_stack(stack *self);                     // OK
static NoSent *pop_in_stack(stack *self, NoSent *pos); // OK

void clear_stack(stack *self); // OK

/* FUNCOES AUXILIARES */
void reverse_stack(stack **self);                           // OK
void copy_stack(stack *dest, const stack *fonte);           // OK
void swap_stack(stack *P1, stack *P2);                      // OK
void print_stack(stack *self, void (*print)(const void *)); // OK

/* IMPLEMENTACOES PILHA */
stack *new_stack(size_t size)
{
    stack *self = (stack *)malloc(sizeof(stack));
    self->Topo = create_Sent();
    self->tam = 0;
    self->size = size;
    return self;
}
void delete_stack(stack **self)
{
    clear_stack(*self);
    delete_NoSent(&((*self)->Topo));
    free(*self);
    *self = NULL;
}

NoSent *push_stack(stack *self, void *elem)
{
    return push_ant_stack(self, elem, self->Topo);
}

static NoSent *push_ant_stack(stack *self, void *elem, NoSent *pos)
{
    if (pos == NULL)
        return NULL;
    if (elem == NULL)
        return NULL;
    if (self == NULL)
        return NULL;

    void *dado = calloc(1, self->size);
    NoSent *novo = new_NoSent(memcpy(dado, elem, self->size), self->size);

    novo->prox = pos->prox;
    novo->ant = pos;
    pos->prox->ant = novo;
    pos->prox = novo;

    self->tam++;

    return novo;
}

NoSent *pop_no_stack(stack *self)
{
    return pop_in_stack(self, self->Topo->prox);
}

void *pop_stack(stack *self)
{
    NoSent *aux = pop_no_stack(self);
    if (aux != NULL)
    {
        void *dado = malloc(aux->size);
        memcpy(dado, aux->dado, aux->size);
        delete_NoSent(&aux);
        return dado;
    }
    return NULL;
}

static NoSent *pop_in_stack(stack *self, NoSent *pos)
{
    if (self == NULL)
        return NULL;
    if (pos == NULL)
        return NULL;
    if (pos == self->Topo)
        return NULL;

    pos->ant->prox = pos->prox;
    pos->prox->ant = pos->ant;

    pos->prox = pos->ant = NULL;

    self->tam--;

    return pos;
}

void clear_stack(stack *self)
{
    NoSent *aux = pop_no_stack(self);
    while (aux != NULL)
    {
        delete_NoSent(&aux);
        aux = pop_no_stack(self);
    }
}

void reverse_stack(stack **self)
{
    NoSent *aux = pop_no_stack(*self);
    stack *T = new_stack((*self)->size);
    while (aux != NULL)
    {
        push_ant_stack(T, aux->dado, T->Topo);
        delete_NoSent(&aux);
        aux = pop_no_stack(*self);
    }
    delete_stack(self);
    *self = T;
}

void copy_stack(stack *dest, const stack *fonte)
{
    if (dest == NULL || fonte == NULL)
        return;
    if (dest->size != fonte->size)
        return;
    if (dest->tam != 0)
    {
        clear_stack(dest);
    }
    NoSent *aux = fonte->Topo->ant;
    while (aux != fonte->Topo)
    {
        push_stack(dest, aux->dado);
        aux = aux->ant;
    }
}

void swap_stack(stack *P1, stack *P2)
{
    if (P1 == NULL || P2 == NULL)
        return;
    if (P1->size != P2->size)
        return;
    stack *aux = new_stack(P1->size);
    copy_stack(aux, P1);
    copy_stack(P1, P2);
    copy_stack(P2, aux);
}

void print_stack(stack *self, void (*print)(const void *))
{
    NoSent *aux = self->Topo->prox;
    printf("( ");
    while (aux != self->Topo)
    {
        print(aux->dado);
        printf(", ");
        aux = aux->prox;
    }
    printf(")");
}
