from Process import Process
from ListProcess import ListProcess
from color import *

def print_ids(ids_exe):
    import math

    d = 10
    print()
    print("     ", end = "")
    for i in range(d):
        print("%3d" % i, end = " ")
    print()
    print("     ", end = "")
    print("---"* int(d*1.5))
    for i in range( math.ceil(len(ids_exe)/d)  ):
        print("%3d |" % (i*d), end=" ")
        if i*d + d < len(ids_exe):
            for k in ids_exe[i*d:(i*d)+d]:
                formate = YELLOW_COLOR + "{:^3}" + END_COLOR if k < 0 else "{:^3}"
                print(formate.format(k), end = " ")
            print()
        elif len(ids_exe[i*d:]):
            for k in ids_exe[i*d:]:
                formate = YELLOW_COLOR + "{:^3}" + END_COLOR if k < 0 else "{:^3}"
                print(formate.format(k), end = " ")
            print()    

class ManagerProcess(object):
    def __init__(self):
        self.process  = ListProcess()
        self.complete = ListProcess()
        self.scheduler = None
        self.quantum = 1

        self.time = 0
        self.quantum_time = 0

    def add_processes(self, list_processes):
        for i in list_processes:
            self.process.add(Process(i[0], i[1], i[2], i[3], i[4]))
        self.process.list.sort(key=lambda x: x.arrived)
    
    def set_scheduler(self, scheduler):
        self.scheduler = scheduler

    def set_quantum(self, quantum):
        self.quantum = quantum

    def reset_quantum(self):
        self.quantum_time = 0

    def clock_time(self):
        self.time += 1
        self.quantum_time += 1

    def system_process(self, id):
        system_id = id
        system_prio = 0
        system_time_cpu = 2
        system_arrived = -1
        system_io = []
        return Process(system_id, system_time_cpu, system_prio, system_arrived, system_io)

    def total_waiting_time(self, dict_list):
        return sum(dict_list.values())
    
    def average_wait_time(self, dict_list):
        return sum(dict_list.values()) / len(dict_list)

    def statistical_graphs(self, title_plus=''):
        import matplotlib.pyplot as plt
        import seaborn as sns
        import pandas as pd 
        sns.set()
        #plt.style.use('classic')
        
        process_times = self.complete.times_waiting_process()
        #system_times = self.complete.times_waiting_system()
        x = list(process_times.keys())
        y = list(process_times.values())

        colors = ['#2300A8', '#00A658']

        plt.xticks(range(len(process_times)), x)
        plt.bar(range(len(process_times)), y, align='center', color=colors)
        
        plt.plot(x, y, 'ro--', linewidth=2, markersize=12)

        plt.title('Duration of process running in CPU core.' + title_plus)
        plt.ylabel('Time (clock cicle)')
        plt.xlabel('Process (id)')
        plt.show()

    def run(self):
        queue_ready    = ListProcess()
        queue_block    = ListProcess()

        ids_executed = []

        executing = None
        # Header
        print(BOLD_MAGENTA_COLOR + "{:-^80}".format('-') + END_COLOR)
        print(BOLD_MAGENTA_COLOR + "{:-^80}".format("Begin timestamp of execution") + END_COLOR)
        print(BOLD_MAGENTA_COLOR + "{:-^80}".format('-') + END_COLOR)
        for i in range(100):
            print(BOLD_BLUE_COLOR + "Time: {:2}".format(self.time) + ": " + END_COLOR, end=' ') # TIMESTAMP
            # Se existem processos para chegar, verifico se alguem chegou
            if(not self.process.empty() and self.process.get().arrived_now(self.time)):
                queue_ready.add(self.process.pop())
                if self.quantum == 0:
                    self.scheduler(queue_ready)
            
            # Escalonamento do round robin
            if(self.quantum == self.quantum_time):
                self.scheduler(queue_ready)

            # Se as listas de pronto ou bloquiado nao esta vazia, existem processos a serem executados
            if(not queue_ready.empty() or not queue_block.empty()):
                # O sistema possui prioridade sobre qualquer outro processo
                executing = queue_ready.get() if queue_block.empty() else queue_block.get() 

                # Se existem entradas e saidas para serem executadas, faco uma chamada de sistema
                if(executing.check_io()):
                    system_process = self.system_process(-executing.id - 1)
                    queue_block.add(system_process) 

                # Executando o processo
                executing.execute(self.time)
                ids_executed.append(executing.id)

                # Se o processo terminou de ser executado, removo das listas de execucao
                if(executing.completed(self.time)):
                    if(queue_ready.get() == executing):
                        print(GREEN_COLOR + "Process completed: ", executing, END_COLOR, end='') # TIMESTAMP
                    else:
                        print(YELLOW_COLOR + "Process system:    ", executing, END_COLOR, end='') # TIMESTAMP

                    if(queue_block.get() == executing):
                        self.complete.add(queue_block.pop())
                    else:
                        self.complete.add(queue_ready.pop())
                        # Se preemptivo, o escalonador e chamado quando o processo e concluido
                        self.scheduler(queue_ready)
                    
                # Caso o processo nao terminou ainda, entao resolvo as execucoes dele
                elif(queue_ready.get() == executing):
                    print("Process executing: ", executing, "", end='') # TIMESTAMP
                else:
                    print(YELLOW_COLOR + "Process system:    ", executing, END_COLOR, end='') # TIMESTAMP               
            
            print(" Queue ready: ", end='') # TIMESTAMP
            queue_ready.print_ids()         # TIMESTAMP
            print()                         # TIMESTAMP

            # Criterio de parada: Listas de processos, prontos e bloquiados vazias
            if(self.process.empty() and queue_ready.empty() and queue_block.empty()):
                break
            
            # Pulsando clock do sistema 
            self.clock_time()
        print(BOLD_MAGENTA_COLOR + "{:-^80}".format('-') + END_COLOR)
        print(BOLD_MAGENTA_COLOR + "{:-^80}".format("End timestamp of execution") + END_COLOR)
        print(BOLD_MAGENTA_COLOR + "{:-^80}".format('-') + END_COLOR)
        return ids_executed
        '''
        print(i)
        print(*list(filter(lambda x: x.id >= 0, queue_complete.list)), sep='\n')
        print()
        print(*list(filter(lambda x: x.id < 0, queue_complete.list)), sep='\n')
        print()
        print_ids(ids_executed)

        waiting_times = queue_complete.times_waiting_process()

        print(self.total_waiting_time(waiting_times))
        print(self.average_wait_time(waiting_times))
        '''