#ifndef _PILHA_NOMES_H
#define _PILHA_NOMES_H

typedef struct 
{
	int ini; 
	char v[5][9];
} pilha;

void inicializar_pilha(pilha *p);
/* cria uma pilha vazia*/

void empilhar(const char nome[], pilha *p);
/*insere x no inicio da pilha*/

void desempilhar(pilha *p, char nome[]);
/*retorna o elemento do inicio da pilha e o remove dela*/

#endif
