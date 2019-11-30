class Process(object):
    def __init__(self, i, time_cpu, priority, arrived, io):
        self.id = i
        self.time_cpu = time_cpu
        self.priority = priority
        self.arrived = arrived
        self.io = io[:]

        self.time_io = 1
    
    def reset(self):
        self.executed = 1
        self.executed_io = 0

    def extimated_time(self):
        return self.time_cpu + (len(self.io) * (self.time_io)) + 1

    def arrived_now(self, time):
        return self.arrived == time

    def execute(self):
        self.executed += 1

    def completed(self):
        return self.executed == (self.time_cpu + 1)

    def check_io(self):
        return self.executed in self.io

    def execute_io(self):
        self.executed_io += 1

    def completed_io(self):
        if self.executed_io == self.time_io:
            self.executed_io = 0
            return True
        return False

    def __str__(self):
        return f"Process(<{self.id},{self.arrived}> ({self.priority})" + \
            f" CPU[{self.executed}/{self.time_cpu}]" + \
            f" IO[{self.executed_io}/{self.time_io}]" + \
            f" {self.io})"
