from Observer import Observer

class SchedulerRR(Observer):
    def __init__(self, obj, quantum):
        self.observable = obj
        self.observable.set_quantum(quantum)
        if(quantum < 2):
            print("Quantum not be less than 2. Default value is 5.")

        self.observable.attach(self)
    
    def update(self, list_process):
        if(len(list_process) > 1):
            list_process.add(list_process.pop())