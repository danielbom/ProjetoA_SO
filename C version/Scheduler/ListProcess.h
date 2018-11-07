
#include <stdio.h>
#include <stdlib.h>
#include "Process.h"
#include "EstruturasDeDados/List.h"

#ifndef LIST_PROCESS
#define LIST_PROCESS
// Facede to store process with List

typedef struct list_process{
    List* list;
} ListProcess;

// Constructor and destructor
ListProcess* new_ListProcess();
void delete_ListProcess(ListProcess **self);

// Methods
void add_ListProcess(ListProcess* self, Process* process);
Process* pop_ListProcess(ListProcess* self);
Process* get_ListProcess(ListProcess* self);

// Auxiliar methods
void printListProcess(ListProcess* self);
void load_file_ListProcess(ListProcess* self, char* file_name);

ListProcess* new_ListProcess()
{
    ListProcess* new = (ListProcess*) malloc(sizeof(ListProcess));
    new->list = new_List(sizeof(Process));
    return new;
}

void delete_ListProcess(ListProcess **self)
{
    NoSent *aux = pop_back_no_List((*self)->list);
    while (aux != NULL)
    {
        Process* auxp = ((Process*)aux->dado);
        delete_Process(&auxp);
        aux->dado = malloc(1);
        delete_NoSent(&aux);
        aux = pop_front_no_List((*self)->list);
    }
    
    delete_List(&((*self)->list));

    free(*self);
    *self = NULL;
}

void load_file_ListProcess(ListProcess* self, char* file_name)
{
    List* ios = NULL;
    int id, time_cpu, prio, arrived, *io;
    char io_iter;

    FILE* file = fopen(file_name, "r");
    Process* process;
    while(!feof(file))
    {
        id = time_cpu = prio = arrived = 0;
        fscanf(file, "%d %d %d %d", &id, &time_cpu, &prio, &arrived);

        ios = new_List(sizeof(int));

        io_iter = fgetc(file);
        if(io_iter == ' ')
        {
            int length_io = 1;
            int gap = 0;
            while(io_iter != EOF && io_iter != '\n')
            {
                gap++;
                io_iter = fgetc(file);
                length_io += io_iter == ' ';
            }
            
            fseek(file, -gap, SEEK_CUR);

            for(int i = 0; i < length_io; i++)
            {
                io = malloc(sizeof(int));
                fscanf(file, "%d", io);
                push_back_List(ios, io);
            }
        }

        process = new_Process(id, prio, arrived, time_cpu, ios);
        add_ListProcess(self, process);
    }

    fclose(file);
}

void add_ListProcess(ListProcess* self, Process* process)
{
    if(process != NULL)
        push_back_List(self->list, process);
}

Process* pop_ListProcess(ListProcess* self)
{
    return (Process*)pop_front_data_List(self->list);
}

Process* get_ListProcess(ListProcess* self)
{
    return (Process*)begin_List(self->list)->dado;
}

void printListProcess(ListProcess* self)
{
    print_List(self->list, printProcess);
}

void printTabularProcess(ListProcess* self)
{
    NoSent* iter;
    char buf[1000];
    memset(buf, '=', self->list->qtde*6 + 12);
    buf[ self->list->qtde*6 + 12 ] = '\0';
    
    printf("%s\n", buf);
    printf("|%10s|", "id");
    for(iter = begin_List(self->list); iter != end_List(self->list); next_iter_List(&iter))
    {
        Process* aux = (Process*) iter->dado;
        printf("%5d|", aux->id);
    }
    printf("\n%s\n", buf);
    printf("|%10s|", "arrived");
    for(iter = begin_List(self->list); iter != end_List(self->list); next_iter_List(&iter))
    {
        Process* aux = (Process*) iter->dado;
        printf("%5d|", aux->arrived);
    }
    printf("\n%s\n", buf);
    printf("|%10s|", "time cpu");
    for(iter = begin_List(self->list); iter != end_List(self->list); next_iter_List(&iter))
    {
        Process* aux = (Process*) iter->dado;
        printf("%5d|", aux->time_cpu);
    }
    printf("\n%s\n", buf);
    printf("|%10s|", "priority");
    for(iter = begin_List(self->list); iter != end_List(self->list); next_iter_List(&iter))
    {
        Process* aux = (Process*) iter->dado;
        printf("%5d|", aux->prio);
    }
    printf("\n%s\n", buf);
    printf("|%10s|", "begin");
    for(iter = begin_List(self->list); iter != end_List(self->list); next_iter_List(&iter))
    {
        Process* aux = (Process*) iter->dado;
        printf("%5d|", aux->begin);
    }
    printf("\n%s\n", buf);
    printf("|%10s|", "end");
    for(iter = begin_List(self->list); iter != end_List(self->list); next_iter_List(&iter))
    {
        Process* aux = (Process*) iter->dado;
        printf("%5d|", aux->end);
    }
    printf("\n%s\n", buf);
    printf("\n");
}
#endif