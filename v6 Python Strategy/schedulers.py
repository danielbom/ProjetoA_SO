from bisect import insort
from color import MAGENTA_COLOR, END_COLOR

def binary_search(array, elem, key=lambda x: x):
    def search(begin, end):
        if begin == end:
            return begin

        middle = (begin + end) // 2
        if key(array[middle]) > key(elem):
            return search(begin, middle)
        elif key(array[middle]) < key(elem):
            return search(middle + 1, end)

        return middle
    return search(0, len(array))

def fifo(list_process, process, clock=-1):
    if clock == -1:
        list_process.append(process)
        procs = [p.id for p in list_process]
        print(MAGENTA_COLOR, "FIFO Schedule", procs, END_COLOR)

def priority(list_process, process, clock=-1):
    if clock == -1:
        index = binary_search(list_process, process, lambda p: p.priority)
        list_process.insert(index, process)
        procs = [p.id for p in list_process]
        print(MAGENTA_COLOR, "Priority Schedule", procs, END_COLOR)

def sjf(list_process, process, clock=-1):
    if clock == -1:
        index = binary_search(list_process, process, lambda p: p.time_cpu - p.executed)
        list_process.insert(index, process)
        procs = [p.id for p in list_process]
        print(MAGENTA_COLOR, "Shortest Job First Schedule", procs, END_COLOR)

def build_round_robin(quantum, scheduler):
    def round_robin(list_process, process, clock=-1):
        if clock != -1 and list_process and (clock + 1) % quantum == 0:
            list_process.append(list_process.popleft())
            print(MAGENTA_COLOR, "Round Robin Schedule", len(list_process), END_COLOR)
        else:
            scheduler(list_process, process, clock)
    return round_robin