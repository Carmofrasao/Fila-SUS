CFLAGS = -Wall -g -std=gnu99 

PACKAGEFLAGS = lpthread

objs = main.o pilha_nomes.o profissionais.o filapd.o

all: main

main: $(objs)
		gcc $(objs) -o main $$($(PACKAGEFLAGS) 
	
main.o:	main.c 
	cc -c main.c $(CFLAGS)
pilha_nomes.o: pilha_nomes.c 
	cc -c pilha_nomes.c $(CFLAGS)
profissionais.o: profissionais.c
	cc -c profissionais.c $(CFLAGS) 
filapd.o: filapd.c 
	cc -c filapd.c $(CFLAGS)
			
clean:
	-rm -f *.o *~ 
	
purge: clean
	-rm -f main