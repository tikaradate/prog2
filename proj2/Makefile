CC = gcc
CFLAGS = -Wall -std=c99

efeitos = wavinfo wavvol wavnor wavrev wavech wavwid wavcat wavmix
objs =    leitura.o analise_args.o
headers = leitura.h analise_args.h struct.h

all: $(efeitos)

wavinfo: wavinfo.o $(objs)
wavvol:  wavvol.o $(objs)
wavnorm: wavnorm.o $(objs)
wavrev:  wavrev.o $(objs)
wavecho: wavecho.o $(objs)
wavwide: wavwide.o $(objs)
wavcat:  wavcat.o $(objs)
wavmix:  wavmix.o $(objs)

wavinfo.o: wavinfo.c $(headers)
wavvol.o:  wavvol.c $(headers)
wavnorm.o: wavnorm.c $(headers)
wavrev.o:  wavrev.c $(headers)
wavecho.o: wavecho.c $(headers)
wavwide.o: wavwide.c $(headers)
wavcat.o:  wavcat.c $(headers)
wavmix.o:  wavmix.c $(headers)

leitura.o:      leitura.c leitura.h
analise_args.o: analise_args.c analise_args.h

clean:
	rm -f *.o

purge:
	rm -f $(efeitos)
	clean