import gerenciador_de_processo as gdp
import sys
import math
# Para a estrutura de dados que representa o processo em execução, ou o Bloco de Controle de Processo (BCP)

# id         : identificador de processo
# Prioridade : prioridade do processo (Utilizado no algoritmo que considera prioridade
# Estado     : Estado do processo
# Tempos     : de chegada, de início, de uso da CPU

# Processos CPU-Bound : processos amarrados à CPU, fazem mais processamento do que E/S
# Processos IO-Bound  : fazem mais entrada e saída
# Misto               : mistura de processos CPU-Bound e IO-Bound

# Tempo Total de Espera(TEE) e Tempo Médio de Espera(TME) pelos processos para serem executados.
# Trhoughput do sistema: Quantos processos são/foram executados por unidade de tempo (h, min, s)
# Tamanho máximo, médio das filas de processos do sistema (carga do sistema).

# ID  : Identificação
# DF  : Duração da Fase de uso da CPU
# PRI : Prioridade
# TC  : Tempo de chegada
# FIO : Fila de Eventos de Entrada e Saída

# ID - DF - PRI - TC - FIO

def get_process(file_name):
    processos = []
    for i in open(file_name, 'r').read().splitlines():
        aux = i.split(" ")
        pross = [int(aux[0]), int(aux[1]), int(aux[2]), int(aux[3]), []]

        if len(aux) > 4 :
            pross[4] = [ int(i) for i in aux[4:] ]

        processos.append(pross)
    return processos

def print_ids(gp):
    d = 10
    print("     ", end = "")
    for i in range(d):
        print("%2d" % i, end = " ")
    print()
    print("     ", end = "")
    print("---"*d)
    for i in range( math.ceil(len(gp.ids_exe)/d)  ):
        print("%2d |" % (i*d), end=" ")
        if i*d + d < len(gp.ids_exe):
            for k in gp.ids_exe[i*d:(i*d)+d]:
                print("%2d" % k, end = " ")
            print()
        elif len(gp.ids_exe[i*d:]):
            for k in gp.ids_exe[i*d:]:
                print("%2d" % k, end = " ")
            print()

def debug(gp):
    print("TEMPO DE ESPERA / TEMPO DE CHEGADA / PRIMEIRA EXECUCAO")
    for p in gp.processos:
        print("%2d" % p.cheg, end = " ")
    print()
    for p in gp.processos:
        print("%2d" % p.Entra[0], end = " ")

    print("\nFIM TEMPO")

def print_tempo_de_espera(gp):
    print("ID |", end = "")
    for i in range(len(gp.processos)):
        print("%2d|" % i, end = " ")
    print("\nTE |", end = "")
    for p in gp.processos:
        print("%2d|" % p.tempo_de_espera(), end = " ")
    print()

def exe_escalonamento(gp, alg, pids=True, pte=True, pproc=False):
    print("Escalonamento " + alg)
    print()
    gp.escalonar(alg)
    if pids:
        print("Timeline de execução\n")
        print_ids(gp)
    if pte:
        print("\nTempo de espera de cada processo\n")
        print_tempo_de_espera(gp)
    if pproc:
        print(gp)
        print()
    print("Quantidade de processos: " + str( len(gp.processos)+len(gp.lista_de_sistema) ))
    print("Tamanho máximo da fila de processos: " + str(gp.tam_max_list_esp))
    print("Tempo Total de Espera(TTE): " + str(gp.TTE()))
    print("Tempo Médio de Espera(TME): " + str(gp.TME()) + "\n")
    print()

if __name__ == '__main__':
    if len(sys.argv) > 1:
        processos = get_process(sys.argv[1])
    else:
        processos = get_process("processos")
    q   = 4
    tse = 1
    gp = gdp.gerenciador_de_processos(processos,quantum=q, temp_sys_exe=tse)
    print("Gerenciador de processos")
    print("Quantum p/ o algoritmo RR: " + str(q))
    print("Tempo de execução da I/O de sistema: " + str(tse) + "\n")
    algoritmos = ("FIFO", "FIFO-P", "SJF", "PRIO", "RR")

    algo = 6
    if algo==1:
        exe_escalonamento(gp, "FIFO", False, False)
    elif algo==2:
        exe_escalonamento(gp, "FIFO-P", False, False)
    elif algo==3:
        exe_escalonamento(gp, "SJF", False, False)
    elif algo==4:
        exe_escalonamento(gp, "PRIO", False, False)
    elif algo==5:
        exe_escalonamento(gp, "RR", False, False)
    else:
        for a in algoritmos:
            exe_escalonamento(gp, a, True, True)
            print()
