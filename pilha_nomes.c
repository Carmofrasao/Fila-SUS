#include"pilha_nomes.h"

void inicializar_pilha(pilha *p)
/*inicializa a estrutura.*/
{
	p->ini = -1;
	for (int cont = 0; cont < 5; cont++)
		for (int cont2 = 0; cont2 < 9; cont2++)
			p->v[cont][cont2] = '\0';
}

void empilhar(const char nome[], pilha *p)
/*insere x no inicio da pilha*/
{
	p->ini = p->ini + 1;
	int cont = 0;
	while(nome[cont] != 0)
	{
		p->v[p->ini][cont] = nome[cont];
		cont++;
	}
}

void desempilhar(pilha *p, char nome[])
/*retorna o elemento do inicio da pilha e o remove dela*/
{
	int cont = 0;
	while(p->v[p->ini][cont] != '\0')
	{
		nome[cont] = p->v[p->ini][cont];
		cont++;
	}
	p->ini = p->ini - 1;
	return ;
}
