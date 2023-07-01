#ifndef _FILAPD_H
#define _FILAPD_H

typedef struct t_nodo
{
	int dado;
	struct t_nodo *prox_nodo;
}t_nodo;

typedef struct t_fila
{
	struct t_nodo *inicio;
	int tamanho;
}t_fila;

int verificar_vazia(t_fila *fila); 
/*Retorna 1 se a fila está vazia e zero caso contrário;*/

int inicializar_filap(t_fila *fila); 
/*Cria uma fila vazia, isto é, aponta para NULL e contém tamanho zero; Retorna 1 se a operação foi bem sucedida e zero caso contrário;*/

int inserir_elemento(int dado, t_fila *fila);
/*Insere o elemento dado na fila de maneira que ela fique em ordem crescente, do inı́cio para o final dela; Retorna 1 se a operação foi bem sucedida e zero caso contrário;*/  

int remover_primeiro_elemento(int *item, t_fila *fila);
/*Remove o primeiro elemento da lista e o retorna em *item; Retorna 1 se a operação foi bem sucedida e zero caso contrário;*/

int remover_elemento(int *elemento, t_fila *fila);
/*Remove o ultimo elemento da fila e o retorna em *item; Retorna 1 se a operação foi bem sucedida e zero caso contrário;*/

int remove_item_lista(int chave, int *item, t_fila *fila); 
/*Se o elemento chave existir na lista, o retorna em *item; Retorna 1 se a operação foi bem sucedida e zero caso contrário (elemento não encontrado também retorna zero);*/

void mostrar_fila(t_fila *fila); 
/*Imprime os elementos da fila, do inı́cio ao final. Se ela for vazia não imprime nada, nem um \n;*/

void destroir_fila(t_fila *fila); 
/*Remove todos os elementos da fila e faz com que ela aponte para NULL;*/

int topo(t_fila *fila);
/*retorna o valor do topo da fila*/

int conta20(t_fila *fila);
/*conta quantas pessoas sao de prioridade 20*/

#endif
