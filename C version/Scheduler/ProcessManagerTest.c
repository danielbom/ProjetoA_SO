#include "ListProcess.h"
#include "ProcessManager.h"

int main()
{
    // ListProcess
    ListProcess* lp = new_ListProcess();
    for(int id = 0; id < 10; id++)
    {
        int time_cpu = 1 + rand() % 10;
        int arrived = rand() % 30;
        int prio = rand() % 10;
        List* io = NULL;
        if (time_cpu != 1)
            io = new_random_int_List(1, time_cpu-1, rand() % (time_cpu-1));
        else
            io = new_List(sizeof(int));
        
        Process* p = new_Process(id, prio, arrived, time_cpu, io);
        add_ListProcess(lp, p);
    }

    // ProcessManager
    ProcessManager* pm = new_ProcessManager(lp);
    
    
    
    
    
    delete_ProcessManager(&pm);
    //delete_ListProcess(&lp);
    return 0;
}