class Observer(object):
    def Update(self, list_process):
        raise NotImplementedError("Update() must be defined in subclass.")