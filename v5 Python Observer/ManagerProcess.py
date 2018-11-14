from Observable import Observable
from Process import Process
from ListProcess import ListProcess
from color import *

class ManagerProcess(Observable):
    def __init__(self):
        self.process  = ListProcess()
        self.complete = ListProcess()
        self.scheduler = None
        self.quantum = -1

        self.time = 0
        self.quantum_time = 0
        self.time_io = 2
    
    def notify(self, list_process):
        self.observers.update(list_process)
    
    def add_processes(self, list_processes):
        for i in list_processes:
            process = Process(i[0], i[1], i[2], i[3], i[4])
            process.time_io = self.time_io 
            self.process.add(process)
        self.process.sort(key=lambda x: x.arrived)

    def set_quantum(self, quantum):
        self.quantum = quantum if quantum >= 2 else 5

    def reset_quantum(self):
        self.quantum_time = 0

    def clock_time(self):
        self.time += 1
        self.quantum_time += 1

    def run(self, title=''):
        self.quantum_time = 0
        self.time         = 0

        executing    = None
        ids_executed = []
        
        queue_ready    = ListProcess()
        queue_block    = ListProcess()

        i = 0
        # Criterio de parada --> Listas de processos, prontos e bloquiados vazias.
        while not (self.process.empty() and queue_ready.empty() and queue_block.empty()) and i < 150:
            # Se existem processos para chegar, verifico se alguem chegou
            if not self.process.empty() and self.process.get().arrived_now(self.time):
                queue_ready.add(self.process.pop())
                self.notify(queue_ready)
            
            # Escalonamento do round robin
            if self.quantum == self.quantum_time:
                self.notify(queue_ready)
            
            # Se a lista de pronto nao esta vazia, existem processos a serem executados
            if not queue_ready.empty():
                executing = queue_ready.get()
                # Executando o processo
                executing.execute(self.time)
                ids_executed.append(executing.id)

                # Se o processo terminou de ser executado, removo das listas de execucao
                if executing.completed(self.time):
                    self.complete.add(queue_ready.pop())

                # Verificando se chamada para entrada e saída
                if executing.check_io():
                    queue_block.add(queue_ready.pop())

            # Se a lista de bloqueio nao esta vazia, existem processos requisitando IO
            if not queue_block.empty():
                executing = queue_block.get()
                executing.execute_io(self.time)

                if executing.completed_io(self.time):
                    queue_ready.add(queue_block.pop())
            
            # Pulsando clock do sistema 
            self.clock_time()
            i += 1
        print(ids_executed)
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
