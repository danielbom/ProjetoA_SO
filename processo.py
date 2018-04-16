class processo(object):
    def __init__(self, id, temp, prio, cheg, evio, pc=0, tipo="Normal"):
        self.id    = id
        self.temp  = temp
        self.prio  = prio
        self.cheg  = cheg
        self.evio  = evio
        self.pc    = 0
        self.Entra = []
        self.Sai   = []
        self.rest  = temp
        self.tipo  = tipo

    def tempo_de_espera(self):
        soma = self.Entra[0] - self.cheg
        for i in range(1, len(self.Entra)):
            soma += (self.Entra[i] - self.Sai[i-1])
        return soma

    def exe(self):
        self.pc   += 1
        self.rest -= 1

    def __str__(self):
        string = "-> Processo Id: " + str(self.id) + " Tipo: " + self.tipo + " Prioridade: "
        string += str(self.prio) + "\nChegada: " + str(self.cheg) + " Duração: " + str(self.temp)
        string += "\nEventos de I/O: " + str(self.evio)
        string += "\nEntradas na CPU: " + str(self.Entra)
        string += "\nSaidas da CPU: " + str(self.Sai)
        return string

    def check_io(self):
        return self.pc in self.evio

    def check_exe(self):
        return self.pc >= self.temp
