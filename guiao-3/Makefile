COMPILER = gcc 
INCLUDE = -I include
LDLIBS = -lncurses
HEADER = include
G1 = guiao-1
G2 = guiao-2
SRC = src
CFLAGS = -Wall -g -O2 $(LDLIBS)
OUT = guiao-3
FILTER = entrada/users-g3-filter.csv entrada/repos-g3-filter.csv entrada/commits-g3-filter.csv
FILTERG1 = $(G1)/saida/commits-ok.csv $(G1)/saida/users-ok.csv $(G1)/saida/repos-ok.csv 
QUERIESP = saida/outputs/*.txt saida/query7/*.txt saida/query8/*.txt catalogo/*.csv saida/query1/*.txt saida/query2/*.txt saida/query3/*.txt saida/query4/*.txt saida/query5/*.txt saida/query6/*.txt saida/query9/*.txt saida/query10/*.txt

#Guiao-1
OBJG1 = exercicio1.o exercicio2.o guiao1.o
OBJG1P = $(G1)/obj/exercicio1.o $(G1)/obj/exercicio2.o $(G1)/obj/guiao1.o 

#Guiao-2
OBJI = data.o aux.o totalstats.o typesstats.o abin.o commessage.o stringarray.o quadruplo.o hashint.o
OBJIP = obj/data.o $(G2)/obj/aux.o $(G2)/obj/totalstats.o $(G2)/obj/typesstats.o $(G2)/obj/abin.o $(G2)/obj/commessage.o $(G2)/obj/stringarray.o $(G2)/obj/quadruplo.o $(G2)/obj/hashint.o
OBJG2 = user.o repo.o commit.o tuplo.o triplo.o connection.o $(OBJI) 
OBJPG2 = $(G2)/obj/user.o  $(G2)/obj/repo.o $(G2)/obj/commit.o $(G2)/obj/triplo.o $(G2)/obj/tuplo.o $(G2)/obj/connection.o $(G2)/$(OBJIP)

OBJ = $(OBJG1) $(OBJG2) queries.o menu.o
OBJP = $(OBJG1P) $(OBJPG2) obj/queries.o obj/menu.o

#Ficheiros Guião-1
EX1 = $(G1)/src/exercicio1.c $(G1)/$(HEADER)/exercicio1.h 
EX2 = $(G1)/src/exercicio2.c $(G1)/$(HEADER)/exercicio1.h $(G1)/obj/exercicio1.o $(G1)/$(HEADER)/exercicio2.h 
GU1 = $(G1)/$(SRC)/exercicio1.c $(G1)/$(HEADER)/exercicio1.h $(G1)/$(SRC)/exercicio2.c $(G1)/$(HEADER)/exercicio2.h

#Ficheiros independentes de outros ficheiros.
UT = $(G2)/$(SRC)/typesstats.c $(G2)/$(HEADER)/typesstats.h
D = $(G2)/$(SRC)/data.c $(G2)/$(HEADER)/data.h
A = $(G2)/$(SRC)/aux.c $(G2)/$(HEADER)/aux.h
AB = $(G2)/$(SRC)/abin.c $(G2)/$(HEADER)/abin.h
TU = $(G2)/$(SRC)/tuplo.c $(G2)/$(HEADER)/tuplo.h
TR = $(G2)/$(SRC)/triplo.c $(G2)/$(HEADER)/triplo.h
QUO = $(G2)/$(SRC)/quadruplo.c $(G2)/$(HEADER)/quadruplo.h
HI = $(G2)/$(SRC)/hashint.c $(G2)/$(HEADER)/hashint.h

#Ficheiro dependentes de outros ficheiros.
P = $(G2)/$(SRC)/connection.c $(G2)/$(HEADER)/connection.h 
USO = $(G2)/$(SRC)/user.c $(G2)/$(HEADER)/user.h
CO = $(G2)/$(SRC)/commit.c $(G2)/$(HEADER)/commit.h
RO = $(G2)/$(SRC)/repo.c $(G2)/$(HEADER)/repo.h
CM = $(G2)/$(SRC)/commessage.c $(G2)/$(HEADER)/commessage.h
SA = $(G2)/$(SRC)/stringarray.c $(G2)/$(HEADER)/stringarray.h
TS = $(G2)/$(SRC)/totalstats.c $(G2)/$(HEADER)/totalstats.h

#Ficheiros guiao3
Q = $(SRC)/queries.c $(HEADER)/queries.h
GO = $(SRC)/guiao3.c 
M = $(SRC)/menu.c $(HEADER)/menu.h

# Ficheiros executavel teste
T = $(SRC)/teste.c

all: guiao3 teste

guiao3: $(OBJ) guiao3.o
	$(COMPILER) $(OBJP)  obj/guiao3.o $(CFLAGS) $(INCLUDE) -o $(OUT) $(LDLIBS) 
 
guiao3.o: $(GO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/guiao3.c -o obj/guiao3.o

queries.o: $(Q)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/queries.c -o obj/queries.o  

menu.o: $(M)  
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/menu.c -o obj/menu.o 

connection.o: $(P) 
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/connection.c -o $(G2)/obj/connection.o

commessage.o : $(CM)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/commessage.c -o $(G2)/obj/commessage.o

user.o: $(UO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/user.c -o $(G2)/obj/user.o

repo.o: $(RO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/repo.c -o $(G2)/obj/repo.o

commit.o: $(CO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/commit.c -o $(G2)/obj/commit.o

stringarray.o: $(SA)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/stringarray.c -o $(G2)/obj/stringarray.o

totalstats.o: $(TS)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/totalstats.c -o $(G2)/obj/totalstats.o

triplo.o: $(TRO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/triplo.c -o $(G2)/obj/triplo.o

tuplo.o: $(TUO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/tuplo.c -o $(G2)/obj/tuplo.o

quadruplo.o: $(QUO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/quadruplo.c -o $(G2)/obj/quadruplo.o

typesstats.o: $(UT)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/typesstats.c -o $(G2)/obj/typesstats.o

data.o: $(D)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/data.c -o $(G2)/obj/data.o

aux.o: $(A)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/aux.c -o $(G2)/obj/aux.o

abin.o: $(AB)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/abin.c -o $(G2)/obj/abin.o

hashint.o: $(HI)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G2)/$(SRC)/hashint.c -o $(G2)/obj/hashint.o

# Guiao-1
guiao1.o: $(GU1)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G1)/$(SRC)/guiao1.c -o $(G1)/obj/guiao1.o

exercicio2.o: $(EX2)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G1)/$(SRC)/exercicio2.c -o $(G1)/obj/exercicio2.o
  
exercicio1.o: $(EX1)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(G1)/$(SRC)/exercicio1.c -o $(G1)/obj/exercicio1.o 

#Teste

teste: teste.o $(OBJ)
	$(COMPILER) $(OBJP) obj/teste.o  $(CFLAGS) $(INCLUDE) -o tests	

teste.o:
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/teste.c -o obj/teste.o 

clean: 
	rm -rf $(G1)/obj/*.o $(G2)/obj/*.o obj/*.o guiao-3 tests $(QUERIESP) $(FILTERG1) $(FILTER) entrada/testes_queries.txt