class Process(object):
    def __init__(self, id, duracao, prioridade, chegada, io):
        self.id = id
        self.arrived = chegada
        self.time_cpu = duracao
        self.priority = prioridade
        
        self.io = io[:]

        self.begin    = -1
        self.end      = -1
        self.executed = 0

        self.executed_io = 0
        self.time_io = 0

    def arrived_now(self, time):
        return self.arrived == time

    def execute(self, time):
        if(self.begin == -1): self.begin = time        
        self.executed += 1

    def completed(self, time):
        if(self.executed >= self.time_cpu):
            self.end = time
            return True
        return False
    
    def check_io(self):
        return self.executed in self.io
    
    def execute_io(self, time):
        self.executed_io += 1
    
    def completed_io(self, time):
        if self.executed_io == self.time_io:
            self.executed_io = 0
            return True
        return False

    def __str__(self):
        return "(<{:^3}>, +{:<3},{:^3},{:^3},{:^3})".format(
            self.id,
            self.executed,
            self.time_cpu,
            self.begin,
            self.end
            )
