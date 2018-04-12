import gerenciador_de_processo as gdp
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

def exe_escalonamento(gp, alg):
    print("Escalonamento " + alg)
    gp.escalonar(alg)
    print(gp.ids_exe)
    print("Tempo Médio de Espera(TME): " + str(gp.TME()) + "\n")

if __name__ == '__main__':
    processos = get_process("processos.txt")
    gp = gdp.gerenciador_de_processos(processos)
    algoritmos = ("FIFO", "SFJ", "PRIO", "RR")
    for a in algoritmos:
        exe_escalonamento(gp, a)
    