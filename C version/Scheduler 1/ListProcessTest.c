#include "ListProcess.h"
#include <time.h>
#include "Util/array.h"

void init_simples()
{
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

    printListProcess(lp);

    delete_ListProcess(&lp);
}

void init_from_file()
{
    ListProcess* lp = new_ListProcess();
    load_file_ListProcess(lp, "processos.txt");
    printListProcess(lp);
    delete_ListProcess(&lp);
}

int main()
{
    init_from_file();    

    return 0;
}
