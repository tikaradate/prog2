# GRR20190367 Vinicius Tikara Venturi Date
CC = gcc
CFLAGS = -Wall -std=c99 -g

efeitos = wavinfo wavvol wavnorm wavrev wavecho wavwide wavcat wavmix
objs =    leitura_escrita.o analise_args.o wavaux.o
headers = leitura_escrita.h analise_args.h wavaux.h

all: $(efeitos)

wavinfo: wavinfo.o $(objs)
wavvol:  wavvol.o $(objs)
wavnorm: wavnorm.o $(objs)
wavrev:  wavrev.o $(objs)
wavecho: wavecho.o $(objs)
wavwide: wavwide.o $(objs)
wavcat:  wavcat.o $(objs)
wavmix:  wavmix.o $(objs)

leitura_escrita.o: leitura_escrita.c leitura_escrita.h
analise_args.o:    analise_args.c analise_args.h
wavaux.o:		   wavaux.c wavaux.h

clean:
	rm -f *.o

purge: clean
	rm -f $(efeitos)