
#include <stdlib.h>
#include "ListProcess.h"

typedef struct process_manager{
    ListProcess* all;
    ListProcess* ready;
    ListProcess* blocks;

    void (*scheduler)(ListProcess*);
    int quantum;
    bool is_round_robin;
} ProcessManager;

ProcessManager* new_ProcessManager(ListProcess* all)
{
    ProcessManager* new = malloc(sizeof(ProcessManager));
    new->all = all;
    new->ready = new_ListProcess();
    new->blocks = new_ListProcess();

    new->quantum = 0;
    new->is_round_robin = false;

    return new;
}

void delete_ProcessManager(ProcessManager** self)
{   
    ListProcess* aux = (*self)->all;
    delete_ListProcess(&aux);
    aux = (*self)->ready;
    delete_ListProcess(&aux);
    aux = (*self)->blocks;
    delete_ListProcess(&aux);

    free(*self);
}

void set_scheduler_ProcessManager(ProcessManager* self, void (*scheduler)(ListProcess*))
{
    self->scheduler = scheduler;
}

static void round_robin(ListProcess* lp)
{
    // Rotate only
    Process* rotating = pop_ListProcess(lp);
    add_ListProcess(lp, rotating);
}

void set_round_robin_mode_ProcessManager(ProcessManager* self, int quantum)
{
    if(quantum <= 1)
        quantum = -1;

    self->is_round_robin = true;
    self->quantum = quantum;
    self->scheduler = round_robin;
}
void init_ProcessManager(ProcessManager* self)
{
    int cmp_by_arrived(const void *a, const void *b)
    {
        Process* pa = (Process*) a;
        Process* pb = (Process*) b;
        return pa->arrived - pb->arrived;
    }
    sort_List(self->all->list, cmp_by_arrived);
}

Process* pop_in_time_ListProcess(ListProcess* self, int time)
{
    Process* p = (Process*) begin_List(self->list)->dado;
    if(p->arrived == time)
        return pop_ListProcess(self);
    return NULL;
}

Process* pop_in_time_ProcessManager(ProcessManager* self, int time)
{
    Process* p = (Process*) begin_List(self->all->list)->dado;
    if(p->arrived == time)
        add_ListProcess(self->ready, pop_ListProcess(self->all));
    return NULL;
}

void run_ProcessManager(ProcessManager* self)
{
    if(self->scheduler == NULL)
        return ;

    init_ProcessManager(self);
    int clock_time = 0;
    int quantum_count = 0;

    printf(GREEN_COLOR "%60s\n" END_COLOR, "Geral vision of all process (Initial)");
    printTabularProcess(self->all);
    printf("\n");

    Process* to_execute = NULL;
    ListProcess* completed = new_ListProcess();

    while( (self->all->list->qtde || self->ready->list->qtde || self->blocks->list->qtde) && clock_time < 200)
    {
        printf(BLUE_COLOR "Time: %2d " END_COLOR, clock_time);

        // Verficando se alguém chegou neste momento
        int length_t1 = self->ready->list->qtde;

        if(self->all->list->qtde)
            pop_in_time_ProcessManager(self, clock_time);

        // Executo o escalonador (preemptivo)
        if(!self->is_round_robin && length_t1 != self->ready->list->qtde)
        {
            if(!self->is_round_robin)
                self->scheduler(self->ready);
        }
        else if(self->is_round_robin && self->quantum == quantum_count)
        {
            quantum_count = 0;
            self->scheduler(self->ready);
        }

        // Pego o processo que deve ser executado
        Process* last_executing = to_execute;
        to_execute = get_ListProcess(self->ready);

        // Se não tem quem executar, pulo a execução
        if(to_execute == NULL)
        {
            printf(YELLOW_COLOR "Time ocious of CPU.\n" END_COLOR);
            clock_time++;
            continue;
        }

        printf("Executing: %2d ", to_execute->id);
        printf("TotalTime: %2d ", to_execute->time_cpu);

        if(to_execute->executed == 0 || last_executing != to_execute)
            printf(MAGENTA_COLOR "TimeExec : %2d\n" END_COLOR, to_execute->executed);
        else if(to_execute->executed != to_execute->time_cpu - 1)
            printf("TimeExec : %2d\n", to_execute->executed);
        else
            printf(RED_COLOR "TimeExec : %2d\n" END_COLOR, to_execute->executed);
        
        // Executando o processo
        execute_Process(to_execute, clock_time);

        // Verificando se o processo terminou
        if(finalized_Process(to_execute, clock_time))
        {

            Process* deleted = pop_ListProcess(self->ready);
            add_ListProcess(completed, deleted);
            quantum_count = 0;
            to_execute = NULL;
        }

        clock_time++;
        quantum_count++;
    }

    printf(GREEN_COLOR "\n\n%60s\n" END_COLOR, "Geral vision of all process (Final)");
    printTabularProcess(completed);
    delete_ListProcess(&completed);
}
