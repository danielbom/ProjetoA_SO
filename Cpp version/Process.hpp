#ifndef PROCESS
#define PROCESS

#include <list>
#include "color.h"

class Process {
    private:
        int id;
        int priority;
        int arrived;
        int time_cpu;

        std::list<int> io_list;

        int executed;
        int begin;
        int end;
    
    public:
        // Constructor and Destructor
        Process(
            int id,
            int priority,
            int arrived,
            int time_cpu, 
            std::list<int> & io_list)
        {
            this->id       = id;
            this->priority = priority;
            this->arrived  = arrived;
            this->time_cpu = time_cpu;
            this->io_list  = io_list;

            this->executed = 0;
            this->begin    = -1;
            this->end      = -1;
        }

        void print()
        {
            std::cout << BOLD_GREEN_COLOR << ">>>"  << END_COLOR;
            std::cout << " id( " <<  this->id << " )" ;
            std::cout << " prio( " << this->priority << " )" ;
            std::cout << " arrived( " << this->arrived << " )" ;
            std::cout << " time( " << this->time_cpu << " )" << std::endl ;
            std::cout << " *  Lista de IO: ( " ;
            
            for (std::list<int>::iterator it = this->io_list.begin(); it != this->io_list.end(); it++)
                std::cout << *it << ", ";
            std::cout << ")";

            std::cout << YELLOW_COLOR ;
            std::cout << "\n *  executed( " << this->executed ; 
            std::cout << " ) begin( " << this->begin ;
            std::cout << " )  end( " << this->end ;
            std::cout << " )\n\n" << END_COLOR;

        }

        void execute(int time)
        {
            if(this->begin == -1)
                this->begin = time;
            this->executed++;
        }

        bool finalized(int time)
        {
            if(this->executed == this->time_cpu)
            {
                this->end = time;
                return true;
            }
            return false;
        }

        int get_id()
        {
            return this->id;
        }
        int get_priority()
        {
            return this->priority;
        }
        int get_arrived()
        {
            return this->arrived;
        }
        int get_time_cpu()
        {
            return this->time_cpu;
        }
        int get_executed()
        {
            return this->executed;
        }
        int get_begin()
        {
            return this->begin;
        }
        int get_end()
        {
            return this->end;
        }

};

#endif