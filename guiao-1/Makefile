COMPILER = gcc 
INCLUDE = -I include
CFLAGS = -Wall -g -O2
OUT= guiao-1
OBJ= guiao1.o exercicio2.o exercicio1.o

guiao1:  $(OBJ)
	$(COMPILER) obj/guiao1.o obj/exercicio2.o obj/exercicio1.o $(CFLAGS) $(INCLUDE) -o $(OUT) 
 
guiao1.o: src/exercicio1.c includes/exercicio1.h src/exercicio2.c includes/exercicio2.h
	$(COMPILER)    $(CFLAGS) $(INCLUDE) -c src/guiao1.c -o obj/guiao1.o

exercicio2.o: src/exercicio2.c includes/exercicio1.h exercicio1.o includes/exercicio2.h 
	$(COMPILER)    $(CFLAGS) $(INCLUDE)	-c src/exercicio2.c -o obj/exercicio2.o
  
exercicio1.o: src/exercicio1.c includes/exercicio1.h 
	$(COMPILER)    $(CFLAGS)  $(INCLUDE) -c src/exercicio1.c -o obj/exercicio1.o 

clean: 
	rm -rf obj/*.o guiao-1



