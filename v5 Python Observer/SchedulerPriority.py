from Observer import Observer

class SchedulerPriority(Observer):
    def __init__(self, obj):
        self.observable = obj
        self.observable.attach(self)
    
    def update(self, list_process):
        list_process.sort(key=lambda x: x.priority)