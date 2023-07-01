#ifndef _PROFISSIONAIS_H
#define _PROFISSIONAIS_H

#include"pilha_nomes.h"

typedef struct 
{
	int expediente; 
	char nome[9];
	int tempo_trabalhado;
	int atendido_primeira[2];
	int atendido_segunda[2];
} atendente;

atendente criar_atendente(pilha *p, int posicao);
/*retorna um nome e um expediente*/

void gerencia_profissionais(int num_atendentes, atendente vet_atende[]);
/*retorna um vetor completo de atendentes*/

#endif
