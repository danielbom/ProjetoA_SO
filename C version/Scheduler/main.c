#include "ProcessManager.h"
#include "ListProcess.h"
#include <time.h>
#include <unistd.h> 

void fifo(ListProcess* lp)
{
    return ;
}

void priority(ListProcess* lp)
{
    int cmp_by_prio(const void *a, const void *b)
    {
        Process* pa = (Process*) a;
        Process* pb = (Process*) b;
        return pa->prio - pb->prio;
    }
    sort_List(lp->list, cmp_by_prio);
}

void shortest_first_job(ListProcess* lp)
{
    int cmp_by_time_cpu(const void *a, const void *b)
    {
        Process* pa = (Process*) a;
        Process* pb = (Process*) b;
        return pa->time_cpu - pb->time_cpu;
    }
    sort_List(lp->list, cmp_by_time_cpu);
}

ListProcess* random_ListProcess()
{
    int n = 10;
    int n_arrived = 50;
    int *arrived_map = calloc(n_arrived, sizeof(int));
    arrived_map[0] = 1;

    ListProcess* lp = new_ListProcess();
    for(int id = 0; id < n; id++)
    {
        int time_cpu = 1 + rand() % 10;
        int prio = rand() % 15;
        int arrived = rand() % n_arrived;
        while(arrived_map[arrived])
            arrived = rand() % n_arrived;
        arrived_map[arrived] = 1;
        List* io = NULL;
        if (time_cpu != 1)
            io = new_random_int_List(1, time_cpu-1, rand() % (time_cpu-1));
        else
            io = new_List(sizeof(int));
        
        Process* p = new_Process(id, prio, id == 0 ? 0 : arrived, time_cpu, io);
        add_ListProcess(lp, p);
        usleep(10);
    }
    free(arrived_map);
    return lp;
}

int main(int argc, char *argv[])
{
    // ListProcess    
    ListProcess* list_process ;
    if(argc < 2)
    {
        list_process = random_ListProcess();
    }
    else
    {
        list_process = new_ListProcess();
        load_file_ListProcess(list_process, argv[1]);
    }

    // ProcessManager
    ProcessManager* manager = new_ProcessManager(list_process);
    //set_scheduler_ProcessManager(manager, shortest_first_job);
    set_round_robin_mode_ProcessManager(manager, 5);
    run_ProcessManager(manager);
    
    delete_ProcessManager(&manager);
    return 0;
}