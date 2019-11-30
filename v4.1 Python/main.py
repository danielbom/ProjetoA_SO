from ManagerProcess import ManagerProcess

def priority(list_process):
    list_process.sort(key=lambda x: x.priority)
def sjf(list_process):
    list_process.sort(key=lambda x: x.time_cpu - x.executed)
def fifo(list_process):
    pass
def round_robin(list_process):
    if(len(list_process)>1):
        list_process.add(list_process.pop())

def get_process(file_name):
    with open(file_name, 'r') as reader_file:
        reader = reader_file.read().splitlines()
        processos = [list(map(int, i.split())) for i in reader]
        processos = [(i[0], i[1], i[2], i[3], i[4:]) for i in processos]
        return processos

if __name__ == '__main__':
    list_schedulers = [
        {"name": "FIFO", "alg": fifo, "quantum":0},
        {"name": "SJF", "alg": sjf, "quantum":0},
        {"name": "Priority", "alg": priority, "quantum":0},
        {"name": "Round Robin", "alg": round_robin, "quantum":2}
    ]
    schedule_round_robin = [{"name": "Round Robin", "alg": round_robin, "quantum":2}]
    list_process = get_process("../resources/processos.txt")


    manager_process = ManagerProcess()
    manager_process.add_processes(list_process)
    
    manager_process.set_scheduler(fifo)
    # manager_process.set_scheduler(sjf)
    # manager_process.set_scheduler(priority)
    
    manager_process.run()
    # for scheduler in list_schedulers:
    # for scheduler in schedule_round_robin:
    for scheduler in []:
        manager_process = ManagerProcess()
        manager_process.set_scheduler(scheduler["alg"])
        manager_process.set_quantum(scheduler["quantum"])
        manager_process.add_processes(list_process)
        manager_process.run()
        manager_process.statistical_graphs(" With " + scheduler["name"] + ".")
    
