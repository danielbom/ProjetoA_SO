#include <iostream>
#include "Process.hpp"

int main()
{
    std::list<int> ios ;
    ios.push_back(2);
    ios.push_back(5);
    ios.push_back(8);

    // ------------------------------------------------ //
    Process process(1, 4, 0, 10, ios);

    process.print();

    // ------------------------------------------------ //
    Process* process2 = new Process(2, 3, 1, 10, ios);

    process2->print();

    delete process2;
    return 0;
}