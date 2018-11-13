#ifndef LIST_PROCESS
#define LIST_PROCESS

#include <iomanip> 
#include "Process.hpp"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

class ListProcess{
    private:
        std::list<Process*> list;
    
    public:
        // Constructor and destructor
        ListProcess(){}
        ~ListProcess(){
            this->list.clear();
        }

        // Methods
        void add(Process* process)
        {
            this->list.push_back(process);
        }
        Process* pop()
        {
            Process* process = this->list.front();
            this->list.pop_front();
            return process;
        }
        Process* get()
        {
            return this->list.front();
        }
        void resize(int length)
        {
            this->list.resize(length);
        }

        void print()
        {
            std::cout << "[ ";
            for(std::list<Process*>::iterator it = this->list.begin(); it != this->list.end(); it++)
            {
                (*it)->print();
                std::cout << ", ";
            }
            std::cout << "]";
        }

        void print_tabular()
        {
            size_t size = this->list.size()*6 + 12;
            char line[300];
            memset(line, '=', size);
            line[ size ] = '\0';

            std::list<Process*>::iterator iter;

            printf("%s\n", line);
            printf("|%10s|", "id");

            for(iter = this->list.begin(); iter != this->list.end(); iter++)
                printf("%5d|", (*iter)->get_id());

            printf("\n%s\n", line);
            printf("|%10s|", "arrived");

            for(iter = this->list.begin(); iter != this->list.end(); iter++)
                printf("%5d|", (*iter)->get_arrived());

            printf("\n%s\n", line);
            printf("|%10s|", "time cpu");

            for(iter = this->list.begin(); iter != this->list.end(); iter++)
                printf("%5d|", (*iter)->get_time_cpu());

            printf("\n%s\n", line);
            printf("|%10s|", "priority");

            for(iter = this->list.begin(); iter != this->list.end(); iter++)
                printf("%5d|", (*iter)->get_priority());

            printf("\n%s\n", line);
            printf("|%10s|", "begin");

            for(iter = this->list.begin(); iter != this->list.end(); iter++)
                printf("%5d|", (*iter)->get_begin());

            printf("\n%s\n", line);
            printf("|%10s|", "end");
            
            for(iter = this->list.begin(); iter != this->list.end(); iter++)
                printf("%5d|", (*iter)->get_end());

            printf("\n%s\n", line);
            printf("\n");
        }
};

#endif