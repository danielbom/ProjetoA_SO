class ListProcess(list):
    def add(self, process):
        self.append(process)
    
    def pop(self):
        return super(ListProcess, self).pop(0)
    
    def get(self):
        return self[0] if self else None
    
    def empty(self):
        return len(self) == 0

    def print_ids(self):
        print("(", end=' ')
        for i in reversed(self):
            print(i.id, end=' ')
        print(")", end='')

    def times_waiting_process(self):
        return {i.id: i.end - i.begin for i in filter(lambda x: x.id >= 0, self)}

    def times_waiting_system(self):
        return {-1: sum([i.end - i.begin for i in filter(lambda x: x.id < 0, self)])}