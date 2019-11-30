from SchedulerPriority import SchedulerPriority
from SchedulerFifo import SchedulerFifo
from SchedulerSJF import SchedulerSJF
from SchedulerRR import SchedulerRR
from ManagerProcess import ManagerProcess

def get_process(file_name):
    with open(file_name, 'r') as reader_file:
        reader = reader_file.read().splitlines()
        processos = [list(map(int, i.split())) for i in reader]
        processos = [(i[0], i[1], i[2], i[3], i[4:]) for i in processos]
        return processos

if __name__ == '__main__':
    list_schedulers = [
        {"name": "FIFO", "alg": SchedulerFifo, "quantum":0},
        {"name": "SJF", "alg": SchedulerSJF, "quantum":0},
        {"name": "Priority", "alg": SchedulerPriority, "quantum":0},
    ]
    list_process = get_process("../resources/processos.txt")


    manager_process = ManagerProcess()
    manager_process.add_processes(list_process)
    SchedulerRR(manager_process, 1)
    manager_process.run()
    # manager_process.set_scheduler(sjf)
    # manager_process.set_scheduler(priority)
    
    # for scheduler in list_schedulers:
    # for scheduler in schedule_round_robin:
    for scheduler in []:
        manager_process = ManagerProcess()
        manager_process.set_scheduler(scheduler["alg"])
        manager_process.set_quantum(scheduler["quantum"])
        manager_process.add_processes(list_process)
        manager_process.run()
        manager_process.statistical_graphs(" With " + scheduler["name"] + ".")
    
