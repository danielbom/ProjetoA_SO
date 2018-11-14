class Observable(object):
    observers = None
    
    def attach(self, obj):
        self.observers = obj
    
    def detach(self, obj):
        self.observers = None
    
    def notify(self):
        for observer in self.observers:
            observer.update()
    
