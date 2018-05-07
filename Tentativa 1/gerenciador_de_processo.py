import processo
import operator

class gerenciador_de_processos(object):
    def __init__(self, lista_de_processos, quantum = 5, temp_sys_exe = 1):
        self.n_processos        = len(lista_de_processos)
        self.lista_de_processos = lista_de_processos
        self.temp_sys_exe       = temp_sys_exe
        self.quantum            = quantum
        self.lista_de_sistema   = []
        self.processos          = []
        self.ids_exe            = []
        self.tam_max_list_esp   = 0

    def __str__(self):
        string = ""
        for i in self.processos:
            string += str(i) + "\n"
        for i in self.lista_de_sistema:
            string += str(i) + "\n"
        return string

    # sort = "FIFO" || "SJF" || "PRIO" || "RR" || "FIFO-P"
    def escalonar(self, sort="FIFO"):
        process               = [processo.processo(i[0],i[1],i[2],i[3],i[4]) for i in self.lista_de_processos]
        lim_sistema           = len(process)
        sys_cheg              = []
        finalizados           = []
        lista_de_espera       = []
        lista_ids_exe         = []
        self.lista_de_sistema = []
        sistema               = None
        exe                   = None
        time                  = 0
        count_quantum         = 0
        self.tam_max_list_esp = 0

        while True:
            # Busca processos que chegam no sistema
            for i in process:
                if i.cheg == time:
                    if sort == "FIFO":
                        lista_de_espera.append(i)
                    else:
                        lista_de_espera.insert(0, i)
            # Salvando o tamanho máximo da lista de espera
            if len(lista_de_espera) > self.tam_max_list_esp:
                self.tam_max_list_esp = len(lista_de_espera)

            # Fazendo as ordenações para cada algoritmo
            if sort == "SJF" :
                lista_de_espera.sort(key=operator.attrgetter("rest"))
            elif sort == "PRIO":
                lista_de_espera.sort(key=operator.attrgetter("prio"))

            # Para a lista de espera ordenada de acordo com o algoritmo
            # de escalonamento de execução, selecione o primeiro da lista
            # para executar
            if len(lista_de_espera):
                # Se exe == None e existem item na lista de espera, exe terminou
                # de ser executado
                if exe == None:
                    if sort == "FIFO":
                        lista_de_espera.sort(key=operator.attrgetter("rest"))
                    exe = lista_de_espera[0]
                    exe.Entra.append(time)
                # Se exe != None, porém o primeiro elemento da lista de espera
                # não é igual a exe, é pq entrou alguém com maior prioridade
                # para ser executado
                elif lista_de_espera[0] != exe:
                    exe.Sai.append(time)
                    exe = lista_de_espera[0]
                    exe.Entra.append(time)
                    

            # Executa o processo
            lista_ids_exe.append( exe.id )
            exe.exe()
            time          += 1
            count_quantum += 1

            # Verifica se existe entrada e saída
            if exe.check_io():
                # Cria-se um processo para a IO
                sistema = processo.processo(id=lim_sistema, temp=self.temp_sys_exe, prio=0, cheg=time, evio=[], tipo="Sistema")
                # Armazena esse processo numa lista para analizes posteriores
                self.lista_de_sistema.append(sistema)
                # Adiciona no início da lista de espera para ser executado em seguida
                lista_de_espera.insert(0, sistema)
                sys_cheg.append(time)
                lim_sistema   += 1
                count_quantum = 0

            # Verifica se o processo terminou
            if exe.check_exe():
                exe.Sai.append(time)
                if exe not in self.lista_de_sistema:
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

            if not (len(process) or len(lista_de_espera)):
                break

        self.processos = sorted(finalizados, key=operator.attrgetter("id"))
        self.ids_exe = lista_ids_exe

    def TTE(self):
        if len(self.ids_exe):
            return sum( [p.tempo_de_espera() for p in self.processos] ) + sum( [p.tempo_de_espera() for p in self.lista_de_sistema] )
        return -1
    def TME(self):
        Tempo_total = self.TTE()
        if Tempo_total+1 :
            return Tempo_total / (len(self.processos) + len(self.lista_de_sistema))
        return -1
