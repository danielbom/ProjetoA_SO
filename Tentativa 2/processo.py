class processo(object):
    def __init__(self, id, duracao, prioridade, chegada, io):
        self.id = id
        self.chegada = chegada
        self.duracao = duracao
        self.prioridade = prioridade
        
        self.io = []
        for i in io:
            if i < duracao and i >= 0:
                self.io.append(i)

        self.espera  = 0
        self.saida   = -1
        self.rest    = duracao
        # estados E(executando), P(pronto), B(bloquiado) e F(finalizado)
        self.estado  = "P"
        # tipo N(normal) e S(sistema)
        self.tipo    = "N"
        

    def exe(self):
        self.rest -= 1
    
    def __str__(self):
        if self.tipo == "S":
            if self.estado == "E":
                return "[S-EXE] PS-[%2.0d/%2.0d]-%2.0d" % (self.rest, self.duracao, self.prioridade)
            return "[ SYS ] PS-[%2.0d/%2.0d]-%2.0d" % (self.rest, self.duracao, self.prioridade)
        if self.estado == "E":
            return "[ EXE ] P%d-[%2.0d/%2.0d]-%2.0d" % (self.id, self.rest, self.duracao, self.prioridade)
        if self.estado == "B":
            return "[BLOCK] P%d-[%2.0d/%2.0d]-%2.0d" % (self.id, self.rest, self.duracao, self.prioridade)
        if self.estado == "F":
            return "[  OK ] P%d-[%2.0d/%2.0d]-%2.0d" % (self.id, self.rest, self.duracao, self.prioridade)
        return "[  P  ] P%d-[%2.0d/%2.0d]-%2.0d" % (self.id, self.rest, self.duracao, self.prioridade)
    
    
    def check_io(self):
        return self.duracao-self.rest in self.io
    
    def check_exe(self):
        return self.rest

'''
p = processo(1, 0, 10, 0, [1])

print(p)

count = 0
while p.check_exe():
    p.exe()
    count += 1

print(count)
'''