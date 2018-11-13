#include "Process.h"

int main()
{
    int io[2] = {5, 2};
    List* lio = array_to_List(io, 2, sizeof(int));

    Process* p = new_Process(0, 10, 0, 10, lio);

    printProcess(p);

    return 0;
}