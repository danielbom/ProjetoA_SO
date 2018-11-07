#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include "EstruturasDeDados/List.h"
#include "color.h"

#ifndef PROCESS
#define PROCESS
typedef struct process{
    int id;
    int prio;
    int arrived;
    int time_cpu;

    List* io_list;

    int executed;
    int begin;
    int end;
} Process;

// Apresentation methods
Process* new_Process(
    int id,
    int priority,
    int arrived,
    int time_cpu,
    List* io)
{
    if(time_cpu == 0)
        return NULL;
    Process* new = malloc(sizeof(Process));
    new->id = id;
    new->prio = priority;
    new->arrived = arrived;
    new->time_cpu = time_cpu;

    new->io_list = io;

    new->executed = 0;
    new->begin = -1;
    new->end = -1;

    return new;
}

void delete_Process(Process** self)
{
    delete_List(&((*self)->io_list));
    free(*self);
}

void printProcess(const void* selfv)
{
    Process* self = (Process*) selfv;
    printf(BOLD_GREEN_COLOR ">>>" END_COLOR);
    printf(" id( " INT_COLOR " ) prio( " INT_COLOR " ) arrived( " INT_COLOR " ) time( " INT_COLOR " )\n", self->id, self->prio, self->arrived, self->time_cpu);
    printf(" *  Lista de IO: ");
    print_List(self->io_list, printInt);
    printf(YELLOW_COLOR "\n *  executed( %d ) begin( %d ) end( %d )" END_COLOR, self->executed, self->begin, self->end);
    printf("\n");
}

// Behaviours methods
void execute_Process(Process *self, int time)
{
    if(self->begin == -1)
        self->begin = time;
    self->executed++;
}

bool finalized_Process(Process *self, int time)
{
    if(self->executed == self->time_cpu)
    {
        self->end = time;
        return true;
    }
    return false;
}


#endif