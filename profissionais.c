#include<stdlib.h>
#include<stdio.h>
#include"profissionais.h"
#include"pilha_nomes.h"

#define MEIO_PERIODO 240
#define ESTAGIARIO 360
#define TURNO_COMPLETO 480
#define TURNO_EMERGENCIAL 600 

atendente criar_atendente(pilha *p, int posicao)
/*retorna um nome e um expediente*/
{
	atendente aux;
	for(int contador = 0; contador < 9; contador++)
		aux.nome[contador] = '\0';
	int vet_expediente[5] = {MEIO_PERIODO, ESTAGIARIO, TURNO_COMPLETO, TURNO_COMPLETO, TURNO_EMERGENCIAL};
	desempilhar(p, aux.nome);
	aux.expediente = vet_expediente[posicao];
	return aux;
}

void gerencia_profissionais(int num_atendentes, atendente vet_atende[])
/*retorna um vetor completo de atendentes*/ 
{
	pilha p;
	inicializar_pilha(&p);
	int vet[5];
	int contador = 0;
	int igual;
	do
	{
		vet[contador] = rand() % 5;
		igual = 0;
		for(int cont_aux = 0; cont_aux < contador; cont_aux++)
		{
			if(vet[cont_aux] == vet[contador])
				igual = 1;
		}
		if(igual == 0)
			contador++;
	}while(contador < 5);
	/*prenchendo um vetor com numeros de 1 a 5 de forma aleatoria*/
		
	const char pessoas[6][9] = {"Joao", "Maria", "Jose", "Gregio", "Castilho"};
	/*vetor com possiveis nomes*/
	
	for (int cont = 0; cont < 5; cont++)
	{
		empilhar(pessoas[vet[cont]], &p);
	}
	/*empilhando os nomes*/

	for(int cont = 0; cont < num_atendentes; cont++)
	{
		vet_atende[cont] = criar_atendente(&p, cont);
	}
	/*preenchendo o vetor de atendentes*/
}
