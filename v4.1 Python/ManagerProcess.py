from Process import Process
from ListProcess import ListProcess
from color import *

class ManagerProcess(object):
    def __init__(self):
        self.process  = ListProcess()
        self.complete = ListProcess()
        self.scheduler = None
        self.quantum = -1

        self.time = 0
        self.quantum_time = 0
        self.time_io = 2

    def add_processes(self, list_processes):
        for i in list_processes:
            process = Process(i[0], i[1], i[2], i[3], i[4])
            process.time_io = self.time_io 
            self.process.add(process)
        self.process.sort(key=lambda x: x.arrived)
    
    def set_scheduler(self, scheduler):
        self.scheduler = scheduler

    def set_quantum(self, quantum):
        self.quantum = quantum

    def reset_quantum(self):
        self.quantum_time = 0

    def clock_time(self):
        self.time += 1
        self.quantum_time += 1

    def run(self, title=''):
        self.quantum_time = 0
        self.time = 0
        queue_ready    = ListProcess()
        queue_block    = ListProcess()

        ids_executed = []

        executing = None
        # Header
        FORMAT = "{:-^120}"
        print(BOLD_MAGENTA_COLOR + FORMAT.format('-') + END_COLOR)
        print(BOLD_MAGENTA_COLOR + FORMAT.format("Begin timestamp of execution" + title) + END_COLOR)
        print(BOLD_MAGENTA_COLOR + FORMAT.format('-') + END_COLOR)
        # Criterio de parada --> Listas de processos, prontos e bloquiados vazias.

        i = 0
        while not (self.process.empty() and queue_ready.empty() and queue_block.empty()) and i < 150:
            # Se existem processos para chegar, verifico se alguem chegou
            flag_arrived = False
            flag_scheduled = False
            if not self.process.empty() and self.process.get().arrived_now(self.time):
                queue_ready.add(self.process.pop())
                self.scheduler(queue_ready)
                flag_scheduled = True
                flag_arrived = True
            
            # Escalonamento do round robin
            if self.quantum == self.quantum_time:
                self.scheduler(queue_ready)
                flag_scheduled = True
            
            
            # Se a lista de pronto nao esta vazia, existem processos a serem executados
            if not queue_ready.empty():
                executing = queue_ready.get()
                # Executando o processo
                executing.execute(self.time)
                ids_executed.append(executing.id)

                print(BOLD_BLUE_COLOR + "\tCPU - Time: {:2}".format(self.time) + ": ", end='')
                print("Process executing: " + END_COLOR + str(executing) , end='')

                # Se o processo terminou de ser executado, removo das listas de execucao
                if executing.completed(self.time):
                    print(BOLD_GREEN_COLOR + "[Completed]" + END_COLOR, end='')
                    self.complete.add(queue_ready.pop())
                else:
                    print("[Executing]", end='')
                # Verificando se chamada para entrada e saída
                if executing.check_io():
                    print(BOLD_MAGENTA_COLOR + "[ Req. IO ]" + END_COLOR, end='')
                    queue_block.add(queue_ready.pop())

                if flag_scheduled:
                    print(BOLD_RED_COLOR + "[Scheduler]" + END_COLOR, end='')
                
                if flag_arrived:
                    print(YELLOW_COLOR + "[Arriving] " + END_COLOR, end='')

                print()
            # Se a lista de bloqueio nao esta vazia, existem processos requisitando IO
            if not queue_block.empty():
                executing = queue_block.get()
                executing.execute_io(self.time)

                print(BOLD_YELLOW_COLOR + "\t IO - Time: {:2}".format(self.time) + ": ", end='')
                print(" System executing: " + END_COLOR + str(executing), end='')
                print(BOLD_YELLOW_COLOR + "[Exect. IO]" + END_COLOR, end='')
                
                if executing.completed_io(self.time):
                    queue_ready.add(queue_block.pop())
                    # Escalono aqui??
                print()
            # Pulsando clock do sistema 
            self.clock_time()
            i += 1
        print(BOLD_MAGENTA_COLOR + FORMAT.format('-') + END_COLOR)
        print(BOLD_MAGENTA_COLOR + FORMAT.format("End timestamp of execution" + title) + END_COLOR)
        print(BOLD_MAGENTA_COLOR + FORMAT.format('-') + END_COLOR)
        return ids_executed
        '''
        print(i)
        print(*list(filter(lambda x: x.id >= 0, queue_complete)), sep='\n')
        print()
        print(*list(filter(lambda x: x.id < 0, queue_complete)), sep='\n')
        print()
        print_ids(ids_executed)

        waiting_times = queue_complete.times_waiting_process()

        print(self.total_waiting_time(waiting_times))
        print(self.average_wait_time(waiting_times))
        '''
