from Observer import Observer

class SchedulerFifo(Observer):
    def __init__(self, obj):
        self.observable = obj
        self.observable.attach(self)
    
    def update(self, list):
        pass
