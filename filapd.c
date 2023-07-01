#include<stdlib.h>
#include<stdio.h>
#include"filapd.h"

int verificar_vazia(t_fila *fila) 
/*Retorna 1 se a fila está vazia e zero caso contrário;*/
{
	if ((fila->inicio == NULL) && (fila->tamanho == 0))
		return 1;
	return 0;
}

int inicializar_filap(t_fila *fila)
/*Cria uma fila vazia, isto é, aponta para NULL e contém tamanho zero; Retorna 1 se a operação foi bem sucedida e zero caso contrário;*/ 
{
	fila->inicio = NULL;
	fila->tamanho = 0;
	if (verificar_vazia(fila))
		return 1;
	return 0;
}

int inserir_elemento(int dado, t_fila *fila) 
/*Insere o elemento dado na fila de maneira que ela fique em ordem crescente, do inı́cio para o final dela; Retorna 1 se a operação foi bem sucedida e zero caso contrário;*/
{
	t_nodo *nodo = fila->inicio;
	t_nodo *aux = NULL;
	t_nodo *novo_nodo;
	int verificador = 1;
	int cont = 1;
	novo_nodo = calloc(1, sizeof(t_nodo));
	if (novo_nodo == NULL)
		return 0;
	novo_nodo->dado = dado;	
	novo_nodo->prox_nodo = NULL;
	if(fila->inicio == NULL)
	{
		fila->inicio = novo_nodo;
		fila->tamanho++;
		return 1;
	}
	while((cont <= fila->tamanho) && (verificador == 1))
	{
		if (dado > nodo->dado)
			verificador = 0;
		else
		{
			aux = nodo;
			nodo = nodo->prox_nodo;
		}
		novo_nodo->prox_nodo = nodo;
		cont++;
	}
	if(aux == NULL)
	{
		fila->inicio = novo_nodo;
	}
	else
	{ 
		aux->prox_nodo = novo_nodo;
	}
	fila->tamanho++;
	return 1;	
}

int remover_primeiro_elemento(int *item, t_fila *fila) 
/*Remove o primeiro elemento da lista e o retorna em *item; Retorna 1 se a operação foi bem sucedida e zero caso contrário;*/
{
	t_nodo *nodo;
	if(fila->inicio == NULL)
		return 0;
	nodo = fila->inicio;
	*item = nodo->dado;
	fila->inicio = nodo->prox_nodo;
	free(nodo);
	nodo = NULL;
	fila->tamanho--;
	return 1;
}

int remover_elemento(int *elemento, t_fila *fila) 
/*Remove o ultimo elemento da fila e o retorna em *item; Retorna 1 se a operação foi bem sucedida e zero caso contrário;*/
{
	t_nodo *nodo;
	t_nodo *aux;
	int contador = 1;
	if(fila->inicio == NULL)
		return 0;
	nodo = fila->inicio;
	while(contador <= fila->tamanho)
	{
		aux = nodo;
		nodo = nodo->prox_nodo;
		contador++;
	}
	*elemento = aux->dado;
	free(aux);
	fila->tamanho--;
	if(fila->tamanho == 0)
		fila->inicio = NULL;
	return 1;
}

int remove_item_lista(int chave, int *item, t_fila *fila) 
/*Se o elemento chave existir na lista, o retorna em *item; Retorna 1 se a operação foi bem sucedida e zero caso contrário (elemento não encontrado também retorna zero);*/
{
	t_nodo *nodo = fila->inicio;
	t_nodo *aux = NULL;
	int contador = 1;
	if(fila->inicio == NULL)
		return 0;
	if(nodo->dado == chave)
	{
		remover_primeiro_elemento(item, fila);
		return 1;
	} 
	while((contador <= fila->tamanho) && (nodo->dado != chave))
	{
		aux = nodo;
		nodo = nodo->prox_nodo;
		contador++;
	}
	if(nodo == NULL)
	{
		return 0;
	}
	*item = nodo->dado;
	aux->prox_nodo = nodo->prox_nodo;
	free(nodo);
	fila->tamanho--;
	return 1;
}

void mostrar_fila(t_fila *fila)
/*Imprime os elementos da fila, do inı́cio ao final. Se ela for vazia não imprime nada, nem um \n;*/
{
	t_nodo *nodo;
	nodo = (t_nodo*)fila->inicio;
	int contador = 1;
	while(contador <= fila->tamanho)
	{
		printf("%d ", nodo->dado);
		nodo = (t_nodo*)nodo->prox_nodo;
		contador++;
	}
	printf("\n");
}

void destroir_fila(t_fila *fila) 
/*Remove todos os elementos da fila e faz com que ela aponte para NULL;*/
{
	t_nodo *nodo;
	t_nodo *aux;
	if(verificar_vazia(fila))
	{
		return;
	}
	int contador = 1;
	nodo = (t_nodo*)fila->inicio;
	while(contador <= fila->tamanho)
	{
		aux = (t_nodo*)nodo->prox_nodo;
		free(nodo);
		nodo = aux;
		contador++;
	}
	fila->inicio = NULL;
	fila->tamanho = 0;
}

int topo(t_fila *fila) 
/*retorna o valor do topo da fila*/
{
	t_nodo *nodo;
	if(fila->inicio == NULL)
		return 0;
	nodo = fila->inicio;
	return nodo->dado;
}

int conta20(t_fila *fila)
/*conta quantas pessoas sao de prioridade 20*/
{
	t_nodo *nodo;
	int cont = 0;
	if(fila->inicio == NULL)
		return 0;
	nodo = fila->inicio;
	while ((nodo->dado == 20) && (nodo->prox_nodo != NULL))
	{
		cont += 1;
		nodo = nodo->prox_nodo;
	}
	return cont;
}
