CFLAGS = -std=c99 -Wall
objs = ortografia.o dicionario.o

all: ortografia

# ligacao
ortografia: $(objs)

# compilacao
ortografia.o: ortografia.c dicionario.h
dicionario.o: dicionario.c dicionario.h


clean:
	-rm -f *.o

purge: clean
	-rm -f ortografia
