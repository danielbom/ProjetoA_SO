from collections import deque
from color import BLUE_COLOR, CYAN_COLOR, YELLOW_COLOR, GREEN_COLOR, RED_COLOR, END_COLOR


class ProcessManager(object):
    def __init__(self, process_list=[]):
        process_list.sort(key=lambda p: p.arrived, reverse=True)
        self.initial_list = process_list
        self.max_clock = sum(p.extimated_time() for p in process_list)
        self.scheduler = None
        self.running_cpu_process = None
        self.running_io_process = None

    # * UTILS
    def log(self, *args, **kargs):
        pass

    def enable_log(self, enable):
        def log(*args, **kargs):
            print(*args, **kargs)

        def no_log(*args, **kargs): pass
        self.log = log if enable else no_log

    def next_clock(self):
        self.clock += 1

    # * EACH ITERATION
    def check_arrived(self, clock):
        if self.process_list:
            process = self.process_list[-1]
            if process.arrived_now(clock):
                self.log(YELLOW_COLOR, "Arrived", clock, process, END_COLOR)
                self.scheduler(self.ready_queue, process)
                self.process_list.pop()

    def execute_cpu_process(self, clock):
        if self.ready_queue:
            cpu_process = self.ready_queue.popleft()

            if cpu_process.check_io():
                self.block_queue.appendleft(cpu_process)
            elif not cpu_process.completed():
                self.log(GREEN_COLOR, "Execute cpu process",
                         cpu_process, END_COLOR)
                cpu_process.execute()
                self.ready_queue.appendleft(cpu_process)
                self.depuration[cpu_process.id]["cpu"] += 1
                self.running_cpu_process = cpu_process
            else:
                self.log(BLUE_COLOR, "Process finish cpu",
                         cpu_process, END_COLOR)
                pass

    def execute_io_process(self, clock):
        if self.block_queue:
            io_process = self.block_queue[0]

            if io_process.completed_io():
                procs = [p.id for p in self.ready_queue]
                self.block_queue.popleft()
                self.ready_queue.append(io_process)
                io_process.execute()
                self.log(RED_COLOR, "Process finish io", procs, END_COLOR)
            else:
                io_process.execute_io()
                self.log(CYAN_COLOR, "Execute io process",
                         io_process, END_COLOR)
                self.depuration[io_process.id]["io"] += 1
                self.running_io_process = io_process

    # * BASE
    def begin_non_iterative(self):
        self.depuration = {p.id: {"cpu": 0, "io": 0}
                           for p in self.initial_list}

        for p in self.initial_list:
            p.reset()

        self.process_list = self.initial_list[:]
        self.log("Max extemated time: ", self.max_clock)

    def begin(self):
        self.ready_queue = deque()
        self.block_queue = deque()
        self.clock = 0

    def is_finish(self) -> bool:
        if self.clock >= self.max_clock:
            return True
        return not (self.process_list or self.block_queue or self.ready_queue)

    def execute(self, clock=None):
        if clock is None:
            clock = self.clock

        self.log("Execute", clock)
        self.check_arrived(clock)
        self.execute_io_process(clock)
        self.execute_cpu_process(clock)
        self.scheduler(self.ready_queue, self.running_cpu_process, clock)

    def end(self):
        self.log("Depuration")
        # for i, val in self.depuration.items():
        #     cpu, io = val.items()
        #     print(i, cpu, io)
        print(f"Clock: [{self.clock}, {self.max_clock}]")

        if self.process_list:
            print(*self.process_list, sep="\n")
            raise Exception("Process list is not empty when finish")
        if self.ready_queue:
            print(*self.ready_queue, sep="\n")
            raise Exception("Ready queue is not empty when finish")
        if self.block_queue:
            print(*self.block_queue, sep="\n")
            raise Exception("Block queue is not empty when finish")

    def run(self):
        self.begin_non_iterative()
        self.begin()
        while not self.is_finish():
            self.execute()
            self.next_clock()
        self.end()
