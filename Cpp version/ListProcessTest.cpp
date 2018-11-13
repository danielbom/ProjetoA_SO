#include <iostream>
#include "ListProcess.hpp"

Process* fake_process(int id)
{
    std::list<int> ios;
    ios.push_back(2);
    ios.push_back(5);
    ios.push_back(8);
    return new Process(id, 3, 1, 10, ios);
}

int main()
{
    ListProcess* list_process = new ListProcess();
    
    list_process->add(fake_process(0));
    list_process->add(fake_process(1));
    list_process->add(fake_process(2));
    list_process->add(fake_process(3));

    std::cout << "list_process->print()" << std::endl;
    list_process->print();
    std::cout << std::endl << std::endl;

    std::cout << "list_process->print_tabular()" << std::endl;
    list_process->print_tabular();
    std::cout << std::endl;

    Process* front = list_process->get();
    std::cout << "list_process->get()" << std::endl;
    front->print();
    std::cout << std::endl;
    
    Process* pop = list_process->pop();
    std::cout << "list_process->pop()" << std::endl;
    pop->print();
    std::cout << std::endl;

    delete pop;
    delete list_process;

    return 0;
}