from gerenciador_de_processos import gerenciador_de_processos as gdp
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
def print_ids(ids_exe):
    d = 10
    print()
    print("     ", end = "")
    for i in range(d):
        print("%2d" % i, end = " ")
    print()
    print("     ", end = "")
    print("---"*d)
    for i in range( math.ceil(len(ids_exe)/d)  ):
        print("%2d |" % (i*d), end=" ")
        if i*d + d < len(ids_exe):
            for k in ids_exe[i*d:(i*d)+d]:
                print("%2d" % k, end = " ")
            print()
        elif len(ids_exe[i*d:]):
            for k in ids_exe[i*d:]:
                print("%2d" % k, end = " ")
            print()    

def get_process(file_name):
    processos = []
    for i in open(file_name, 'r').read().splitlines():
        aux = i.split(" ")
        pross = [int(aux[0]), int(aux[1]), int(aux[2]), int(aux[3]), []]
       
        if len(aux) > 4 :
            pross[4] = [ int(i) for i in aux[4:] ]
        
        processos.append(pross)
    return processos

if __name__ == '__main__':
    processos = get_process("processos.txt")
    algoritmos = ("FIFO", "SJF", "PRIO", "RR", "ALL")
    algoritmo = "ALL"
    quantum = 5
    tempo_de_execucao_de_io = 1
    printTimeline1 = False
    printTimeline2 = False
    exemplo0 = "Segue um exemplo de chamada de execução\n"
    exemplo1 = "python main.py 'algoritmo' 'quantum' 'duracao_io' 'printTimeline1' 'printTimeline2'\n"
    exemplo2 = "'algoritmo'     : FIFO ou SJF ou PRIO ou RR ou ALL \n"
    exemplo3 = "'quantum'       : qualquer valor entre [2, 100] \n"
    exemplo4 = "'duracao_io'    : qualquer valor entre [1, 100] \n"
    exemplo5 = "'printTimeline1': True ou False \n"
    exemplo6 = "'printTimeline2': True ou False \n\n"
    exemplo7 = "Por padrao      : python main.py ALL 5 1 False False"
    exemplo = exemplo0 + exemplo1 + exemplo2 + exemplo3 + exemplo4 + exemplo5 + exemplo6 + exemplo7
    # Recebendo entrada do sistema
    if len(sys.argv) > 1:
        algoritmo = sys.argv[1].upper()
        if len(sys.argv) > 2:
            quantum = int(sys.argv[2])
            if len(sys.argv) > 3:
                tempo_de_execucao_de_io = int(sys.argv[3])
                if len(sys.argv) > 4:
                    if sys.argv[4] == "False":
                        printTimeline1 = False
                    else :     
                        printTimeline1 = True
                    if len(sys.argv) > 5:
                        if sys.argv[5] == "False":
                            printTimeline2 = False
                        else :     
                            printTimeline2 = True
                        if len(sys.argv) > 6:
                            print("Numero de argumentos excedido!")
                            print(exemplo)
                            exit(0)
    
    # Verificando se as entradas são válidas
    if quantum < 2 and quantum > 100:
        print("Variável quantum deve possuir um valor mínimo de 2 e máximo de 100!")
        print(exemplo)
        exit(0)
    
    if tempo_de_execucao_de_io < 1 and tempo_de_execucao_de_io > 100:
        print("Variável tempo_de_execucao_de_io deve possuir um valor mínimo de 1!")
        print(exemplo)
        exit(0)

    if algoritmo not in algoritmos:
        print("Algoritmo não implementado!")
        print(exemplo)
        exit(0)
    
    # Executando os algoritmos
    q   = quantum
    tse = tempo_de_execucao_de_io
    gp = gdp(processos, quantum=q, tempo_de_execucao_de_io=tse)
    print("Gerenciador de processos")
    print("Quantum p/ o algoritmo RR: " + str(q))
    print("Tempo de execução da I/O do sistema: " + str(tse) + "\n")

    if algoritmo != "ALL":
        print("Algoritmo executando: " + algoritmo)
        gp.escalonar(algoritmo)
        if printTimeline1:
            print_ids(gp.T2)
        if printTimeline2:
            print(gp.T1)
    else:
        for i in algoritmos:
            if i != "ALL":
                print("Algoritmo executando: " + algoritmo)
                gp.escalonar(i)
                if printTimeline1:
                    print_ids(gp.T2)
                    print()
                if printTimeline2:
                    print(gp.T1)
                    print()
                print()
    
    
    
    