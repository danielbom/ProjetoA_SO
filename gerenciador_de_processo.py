import processo
import operator

class gerenciador_de_processos(object):
    def __init__(self, lista_de_processos, quantum = 5, temp_sys_exe = 1):
        self.n_processos        = len(lista_de_processos)
        self.lista_de_processos = lista_de_processos
        self.temp_sys_exe       = temp_sys_exe
        self.quantum            = quantum
        self.processos          = []
        self.ids_exe            = [] 

    def __str__(self):
        string = ""
        for i in self.processos:
            string += str(i) + "\n"
        return string

    # sort = "FIFO" || "SJF" || "PRIO" || "RR"
    def escalonar(self, sort="FIFO"):
        process         = [processo.processo(i[0],i[1],i[2],i[3],i[4]) for i in self.lista_de_processos]
        sistema         = len(process)
        finalizados     = []
        lista_de_espera = []
        lista_ids_exe   = []
        exe             = None
        time            = 0
        count_quantum   = 0
        
        while len(process):
            # Busca processos que chegam no sistema
            for i in process:
                if i.cheg == time:
                    lista_de_espera.append(i)
            if sort == "SJF" :
                lista_de_espera.sort(key=operator.attrgetter("rest"))
            elif sort == "PRIO":
                lista_de_espera.sort(key=operator.attrgetter("prio"))

            # Para a lista de espera ordenada de acordo com o algoritmo
            # de escalonamento de execução, selecione o primeiro da lista
            # para executar
            if len(lista_de_espera) and exe == None:
                if sort == "FIFO":
                    lista_de_espera.sort(key=operator.attrgetter("rest"))
                exe = lista_de_espera[0]
                exe.Entra.append(time)
            elif len(lista_de_espera) and exe != None:
                if lista_de_espera[0] != exe:
                    exe.Sai.append(time)
                    exe = lista_de_espera[0]
                    exe.Entra.append(time)

            # Executa o processo
            lista_ids_exe.append(exe.id)
            exe.exe()
            time          += 1
            count_quantum += 1

            if exe.check_io():
                lista_ids_exe.append(sistema)
                # Simula entrada/saida
                time          += self.temp_sys_exe
                count_quantum += 1

            if exe.check_exe():
                exe.Sai.append(time)
                process.remove(exe)
                finalizados.append(exe)
                lista_de_espera.pop(0)
                exe           = None
                count_quantum = 0
            
            if sort == "RR" and count_quantum == self.quantum:
                exe.Sai.append(time)
                lista_de_espera.pop(0)
                lista_de_espera.append(exe)
                exe           = None
                count_quantum = 0

        self.processos = sorted(finalizados, key=operator.attrgetter("id"))
        self.ids_exe = lista_ids_exe

    def TME(self):
        if len(self.ids_exe):
            soma = 0
            for p in self.processos:
                entra = p.Entra[:]
                sai   = p.Sai[:]
                soma += (entra[0] - p.cheg)
                entra.pop(0)
                while len(entra):
                    soma += (entra[0] - sai[0])
                    entra.pop(0)
                    sai.pop(0)
            return soma / self.n_processos

        return -1