class escalonador_rr(object):
    def __init__(self):
        # A lista armazena os valores ordenados em relação a prioridade
        self.lista = []
        # O controle armazena os valores ordenados em relação a chegada
        self.controle = []
        self.tam_max = 0

    def remover(self, x):
        self.lista.remove(x)
        self.controle.remove(x)

    def add(self, x):
        self.lista.append(x)
        self.controle.append(x)
        if len(self.lista) > self.tam_max :
            self.tam_max = len(self.lista)

    def rotacionar(self):
        x = None
        for i in self.lista:
            if i.estado not in ("F", "B"):
                x = i
                break
        if x != None:
            self.lista.remove(x)
            self.lista.append(x)
    
    # Prioritario retorna o processo que deve ser executado
    def prioritario(self):
        if len(self.lista):
            for i in self.lista:
                if i.estado in ("P", "E"):
                    i.estado = "E"
                    return i
        return None

    def __str__(self):
        if len(self.controle):
            string = ""
            for i in range(len(self.controle) - 1 ):
                string += str(self.controle[i]) + " || " 
            string += str(self.controle[-1])
            return string
        return "" 

class escalonador_sjf(object):
    def __init__(self):
        # A lista armazena os valores ordenados em relação a prioridade
        self.lista = []
        # O controle armazena os valores ordenados em relação a chegada
        self.controle = []
        self.tam_max = 0

    def remover(self, x):
        self.lista.remove(x)
        self.controle.remove(x)

    def add(self, x):
        if not len(self.lista):
            self.lista.append(x)
            pass
        
        count = 0
        for i in self.lista:
            if i.rest > x.rest:
                break
            count += 1
        self.lista[count:count] = [x]

        self.controle.append(x)

        if len(self.lista) > self.tam_max :
            self.tam_max = len(self.lista)

    # Prioritario retorna o processo que deve ser executado
    def prioritario(self):
        if len(self.lista):
            for i in self.lista:
                if i.estado in ("P", "E"):
                    i.estado = "E"
                    return i
        return None

    def __str__(self):
        if len(self.controle):
            string = ""
            for i in range(len(self.controle) - 1 ):
                string += str(self.controle[i]) + " || " 
            string += str(self.controle[-1])
            return string
        return ""
   
class escalonador_prio(object):
    def __init__(self):
        # A lista armazena os valores ordenados em relação a prioridade
        self.lista = []
        # O controle armazena os valores ordenados em relação a chegada
        self.controle = []
        self.tam_max = 0

    def remover(self, x):
        self.lista.remove(x)
        self.controle.remove(x)

    def add(self, x):
        if not len(self.lista):
            self.lista.append(x)
            pass
        
        count = 0
        for i in self.lista:
            if i.prioridade > x.prioridade:
                break
            count += 1
        self.lista[count:count] = [x]

        self.controle.append(x)

        if len(self.lista) > self.tam_max :
            self.tam_max = len(self.lista)

    # Prioritario retorna o processo que deve ser executado
    def prioritario(self):
        if len(self.lista):
            for i in self.lista:
                if i.estado in ("P", "E"):
                    i.estado = "E"
                    return i
        return None

    def __str__(self):
        if len(self.controle):
            string = ""
            for i in range(len(self.controle) - 1 ):
                string += str(self.controle[i]) + " || " 
            string += str(self.controle[-1])
            return string
        return ""

class escalonador_fifo(object):
    def __init__(self):
        self.lista = []
        self.controle = []
        self.tam_max = 0

    def remover(self, x):
        self.lista.remove(x)
        self.controle.remove(x)

    def add(self, x):
        self.lista.append(x)
        self.controle.append(x)
        if len(self.lista) > self.tam_max :
            self.tam_max = len(self.lista)

    # Prioritario retorna o processo que deve ser executado
    def prioritario(self):
        if len(self.lista):
            for i in self.lista:
                if i.estado in ("P", "E"):
                    i.estado = "E"
                    return i
        return None

    def __str__(self):
        if len(self.controle):
            string = ""
            for i in range(len(self.controle) - 1 ):
                string += str(self.controle[i]) + " || " 
            string += str(self.controle[-1])
            return string
        return ""



