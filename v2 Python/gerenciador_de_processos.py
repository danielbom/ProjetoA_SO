from processo import processo
from escalonadores import *
from time import sleep

class gerenciador_de_processos(object):
    def __init__(self, processos, quantum, tempo_de_execucao_de_io):
        self.processos = processos
        self.quantum = quantum
        self.tempo_de_execucao_de_io = tempo_de_execucao_de_io
        self.T1 = None
        self.T2 = None
        self.espera_do_sistema = 0
        self.pos_execucao = None

    def TTE(self):
        t = [i.espera for i in self.pos_execucao]
        return (sum(t)) + self.espera_do_sistema

    def escalonar(self, algoritmo):
        if True:
            processos = []
            IO_Bound = True
            for i in self.processos:
                if not len(i[4]):
                    IO_Bound = False
                processos.append(processo(i[0],i[1],i[2],i[3],i[4]))

            if algoritmo == "FIFO":
                fila_de_prontos = escalonador_fifo()
            elif algoritmo == "PRIO":
                fila_de_prontos = escalonador_prio()
            elif algoritmo == "SJF":
                fila_de_prontos = escalonador_sjf()
            elif algoritmo == "RR":
                fila_de_prontos = escalonador_rr()

            fila_de_bloquiados = []
            executando = None

            pc = 0
            count_quantum = 0 #################### NOVO

            qtde_finalizados = 0
            qtde_total_de_processos = len(processos)

            timeline1 = ""
            timeline2 = []

            sistema      = processo(id=-1, duracao=self.tempo_de_execucao_de_io, prioridade=0, chegada=pc, io=[])
            sistema.tipo = "S"
            espera_total_do_sistema = 0

        while True:
            # Se preemptivo ou não-preemptivo, quando um novo processo é executado
            # o escalonador é acionado
            for i in processos:
                if i.chegada == pc:
                    # Adiciona na lista de forma escalonada
                    fila_de_prontos.add(i)
                    break
            
            # Selecionando o processo
            if executando == None:
                executando = fila_de_prontos.prioritario()
                if executando != None:
                    if executando.saida == -1:
                        executando.espera += (pc - executando.chegada)
                    else:
                        executando.espera += (pc - executando.saida)
                
                    if executando.tipo == "S":
                        espera_total_do_sistema += executando.espera
            
            elif executando != fila_de_prontos.prioritario():
                count_quantum = 0 #################### NOVO
                executando.estado = "P"
                executando.saida = pc
                executando = fila_de_prontos.prioritario()

            # Executando o processo
            if executando != None:
                ''' TIMELINES '''
                timeline1 += "%2.0d " % (pc)
                #print("%2.0d " % (pc), end="")
                timeline1 += str(fila_de_prontos) + "\n"
                #print(fila_de_prontos)
                timeline2.append(executando.id)
                ''' FIM TIMELINE '''
                executando.exe()
                pc += 1
                count_quantum += 1  #################### NOVO

                # Bloquiando processo
                if executando.check_io():
                    fila_de_bloquiados.append(executando)
                    executando.estado = "B"

                # Mantendo o sistema ativo para desbloquiar os processos bloquiados
                if len(fila_de_bloquiados):
                    if sistema not in fila_de_prontos.lista:
                        sistema.estado = "P"
                        sistema.chegada = pc
                        sistema.espera = 0
                        sistema.saida = -1
                        sistema.rest = sistema.duracao
                        fila_de_prontos.add(sistema)

                # Verificando se o processo já terminou
                if not executando.check_exe():
                    if executando.tipo == "S":
                        fila_de_bloquiados[0].estado = "P"
                        fila_de_bloquiados.pop(0)
                        fila_de_prontos.remover(sistema)
                    else:
                        qtde_finalizados += 1

                    executando.estado = "F"
                    fila_de_prontos.prioritario()
                    
                if executando.estado in ("B", "F"):
                    count_quantum = 0       #################### NOVO
                    executando.saida = pc

                    # TESTANDO OPTIMIZAÇÂO
                    ''' TESTE '''
                    if executando.estado == "F" and executando.tipo == "N":
                        fila_de_prontos.lista.remove(executando) 
                    ''' ----- '''

                    executando = None
                    
            
            ''' ###################### IF NOVO '''
            if algoritmo == "RR" and count_quantum == self.quantum:
                fila_de_prontos.rotacionar()
                count_quantum = 0

            if qtde_finalizados == qtde_total_de_processos:
                break

        self.T1 = timeline1
        self.T2 = timeline2
        self.espera_do_sistema = espera_total_do_sistema
        self.pos_execucao = processos

        tte = self.TTE()
        if IO_Bound:
            print("Execução IO-Bound")
        else:
            print("Execução CPU-Bound")
        print("Quantidade de processos:                   " + str(qtde_total_de_processos))
        if IO_Bound:
            print("Tempo total de espera dos processos(TTE):  " + str(tte - self.espera_do_sistema))
            print("Tempo total de espera do sistema(TTE-sys): " + str(self.espera_do_sistema))
        print("Tempo total de espera:                     " + str(tte))
        if IO_Bound:
            print("Tempo médio de espera (TME):               " + str(tte / (qtde_total_de_processos+1) ))
        else:
            print("Tempo médio de espera (TME):               " + str(tte / (qtde_total_de_processos) ))
        print("Tamanho máximo da lista de espera (TMLE):  " + str(fila_de_prontos.tam_max))