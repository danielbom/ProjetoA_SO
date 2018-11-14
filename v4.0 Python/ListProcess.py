class ListProcess(object):
    def __init__(self):
        self.list = []
    
    def add(self, process):
        self.list.append(process)
    
    def pop(self):
        return self.list.pop(0)
    
    def get(self):
        return self.list[0] if self.list else None
    
    def empty(self):
        return len(self.list) == 0

    def print_ids(self):
        print("(", end=' ')
        for i in reversed(self.list):
            print(i.id, end=' ')
        print(")", end='')

    def times_waiting_process(self):
        return {i.id: i.end - i.begin for i in filter(lambda x: x.id >= 0,self.list)}

    def times_waiting_system(self):
        return {-1: sum([i.end - i.begin for i in filter(lambda x: x.id < 0,self.list)])}

    def __str__(self):
        return str(self.list)
    
    def __iter__(self):
        return iter(self.list)