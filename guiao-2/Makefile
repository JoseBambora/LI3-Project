COMPILER = gcc 
INCLUDE = -I include
HEADER = include
SRC = src
CFLAGS = -Wall -g -O2
OUT = guiao-2
OBJI = data.o aux.o totalstats.o typesstats.o abin.o commessage.o stringarray.o quadruplo.o
OBJIP = obj/data.o obj/aux.o obj/totalstats.o obj/typesstats.o obj/abin.o obj/commessage.o obj/stringarray.o obj/quadruplo.o
OBJ = guiao2.o user.o queries.o repo.o commit.o tuplo.o triplo.o connection.o $(OBJI)
OBJP = obj/guiao2.o obj/user.o obj/queries.o obj/repo.o obj/commit.o obj/triplo.o obj/tuplo.o obj/connection.o $(OBJIP)

#Ficheiros independentes de outros ficheiros.
UT = $(SRC)/typesstats.c $(HEADER)/typesstats.h
D = $(SRC)/data.c $(HEADER)/data.h
A = $(SRC)/aux.c $(HEADER)/aux.h
AB = $(SRC)/abin.c $(HEADER)/abin.h
TU = $(SRC)/tuplo.c $(HEADER)/tuplo.h
TR = $(SRC)/triplo.c $(HEADER)/triplo.h
QUO = $(SRC)/quadruplo.c $(HEADER)/quadruplo.h

#Ficheiro dependentes de outros ficheiros.
GO = $(SRC)/guiao2.c
P = $(SRC)/connection.c $(HEADER)/connection.h 
Q = $(SRC)/queries.c $(HEADER)/queries.h
USO = $(SRC)/user.c $(HEADER)/user.h
CO = $(SRC)/commit.c $(HEADER)/commit.h
RO = $(SRC)/repo.c $(HEADER)/repo.h
CM = $(SRC)/commessage.c $(HEADER)/commessage.h
SA = $(SRC)/stringarray.c $(HEADER)/stringarray.h
TS = $(SRC)/totalstats.c $(HEADER)/totalstats.h

guiao2:  $(OBJ)
	$(COMPILER) $(OBJP) $(CFLAGS) $(INCLUDE) -o $(OUT) 
 
guiao2.o: $(GO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/guiao2.c -o obj/guiao2.o

queries.o: $(Q)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/queries.c -o obj/queries.o

connection.o: $(P) 
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/connection.c -o obj/connection.o

commessage.o : $(CM)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/commessage.c -o obj/commessage.o

user.o: $(UO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/user.c -o obj/user.o

repo.o: $(RO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/repo.c -o obj/repo.o

commit.o: $(CO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/commit.c -o obj/commit.o

stringarray.o: $(SA)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/stringarray.c -o obj/stringarray.o

totalstats.o: $(TS)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/totalstats.c -o obj/totalstats.o

triplo.o: $(TRO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/triplo.c -o obj/triplo.o

tuplo.o: $(TUO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/tuplo.c -o obj/tuplo.o

quadruplo.o: $(QUO)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/quadruplo.c -o obj/quadruplo.o

typesstats.o: $(UT)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/typesstats.c -o obj/typesstats.o

data.o: $(D)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/data.c -o obj/data.o

aux.o: $(A)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/aux.c -o obj/aux.o

abin.o: $(AB)
	$(COMPILER) $(CFLAGS) $(INCLUDE) -c $(SRC)/abin.c -o obj/abin.o

clean: 
	rm -rf obj/*.o saida/*.txt guiao-2
