/*
	Feito por Anderson Aparecido do Carmo Frasão para a diciplina CI1001 - Programação I
	Em 26/07/2021 (data de inicio)
	GRR 20204069
*/

#include<stdio.h>
#include<stdlib.h>
#include<unistd.h>
#include<time.h>
#include<pthread.h>
#include<string.h>
#include"filapd.h"
#include"profissionais.h"
#include"pilha_nomes.h"

pthread_mutex_t mutex = PTHREAD_MUTEX_INITIALIZER;
int vacinados_primeira; 
int vacinados_segunda;
int tempo_total_primeira; 
int tempo_total_segunda;
int saiu;
int passou;
t_fila fila_primeira_dose;
t_fila fila_segunda_dose;

atendente vet_atende[5];

int total_vacinados[2];

pthread_t thread[5];

void preenche_a_fila(t_fila *fila, int tam)
/* preenche a fila com elementos cuja prioridade é aleatoria e varia de 1 a 5 */
{
	for(int cont = 1; cont <= tam; cont++)
	{
		int prioridade;
		prioridade = 1 + (rand() % 10);
		
		if((prioridade >= 1) && (prioridade <= 3))
		{
			prioridade = 20;
		}
		if ((prioridade >= 4) && (prioridade <= 10))
		{
			prioridade = 10;
		}
		inserir_elemento(prioridade, fila);		
	} 
}

void *iniciar_atendimento(void *atende)
/*funcao da thread, o tratamento da fila e feito aqui*/
{
	atendente *atendente_atual = (atendente*)atende;
	int tempo_atendimento = 0;
	int cont = 0;
	int cont_prio = 0;
	int cont_n_prio = 0;
	int tempo_max = atendente_atual->expediente;
	/*iniciando variaveis de contagem*/
	while ((cont < tempo_max) && (!verificar_vazia(&fila_primeira_dose)))
	/*enquanto nao exceder o tempo maximo e a fila nao estar vazia, o processamento se mantem*/
	{		
		if(cont_prio > 1)
		/*if para tratar o starvation, caso ja tenha sido atendidos 2 prioritarios, um nao prioritario eh passado na frente*/
		{
			pthread_mutex_lock(&mutex);
			remove_item_lista(10, &tempo_atendimento, &fila_primeira_dose);
			total_vacinados[0] += 1;
			passou++;
			cont_prio = 0;
			cont_n_prio++;
			pthread_mutex_unlock(&mutex);
		}
		else
		/*caso menos que 3 prioritarios tenham sido atendidos*/
		{
			pthread_mutex_lock(&mutex);
			remover_primeiro_elemento(&tempo_atendimento, &fila_primeira_dose);
			total_vacinados[0] += 1;
			cont_prio++;
			pthread_mutex_unlock(&mutex);
		}
		sleep(tempo_atendimento/10);
		if(tempo_atendimento == 20)
		/*contabilizando os prioritarios que estao sendo atendidos*/
		{
			vacinados_primeira += 1;
			atendente_atual->atendido_primeira[1] += 1;
		}
		else
		/*contabilizando os nao prioritarios que estao sendo atendidos*/
		{
			atendente_atual->atendido_primeira[0] += 1;	
		}
		
		tempo_total_primeira += tempo_atendimento;
		
		if ((cont == (tempo_max/2) && (tempo_max > 240)))
		/*intervalo de almoco*/
		{
			sleep(1.5);
		}
		
		cont += tempo_atendimento;
		
		if ((cont_n_prio == 2) && (topo(&fila_primeira_dose) == 20))
		/*mau-humor: caso ja tenham passado 6 pessoas (4 prioritarios e 2 nao prioritarios) na frente de um prioritario, ele sai da fila*/
		{
			remover_primeiro_elemento(&tempo_atendimento, &fila_primeira_dose);
			saiu++;
			cont_n_prio = 0;
		}	
	}
	
	while ((cont < tempo_max) && (!verificar_vazia(&fila_segunda_dose)))
	/*enquanto nao exceder o tempo maximo e a fila nao estar vazia, o processamento se mantem*/
	{		
		if(cont_prio > 1)
		/*if para tratar o starvation, caso ja tenha sido atendidos 3 prioritarios, um nao prioritario eh passado na frente*/
		{
			pthread_mutex_lock(&mutex);
			remove_item_lista(10, &tempo_atendimento, &fila_segunda_dose);
			total_vacinados[1] += 1;
			cont_prio = 0;
			passou++;
			cont_n_prio++;
			pthread_mutex_unlock(&mutex);		}
		else
		/*caso menos que 3 prioritarios tenham sido atendidos*/
		{
			pthread_mutex_lock(&mutex);
			remover_primeiro_elemento(&tempo_atendimento, &fila_segunda_dose);
			total_vacinados[1] += 1;
			cont_prio++;
			pthread_mutex_unlock(&mutex);
		}
		sleep(tempo_atendimento/10);
		if(tempo_atendimento == 20)
		/*contabilizando os prioritarios que estao sendo atendidos*/
		{
			vacinados_segunda += 1;
			atendente_atual->atendido_segunda[1] += 1;
		}
		else
		/*contabilizando os nao prioritarios que estao sendo atendidos*/
		{
			atendente_atual->atendido_segunda[0] += 1;
		}
			
		tempo_total_segunda += tempo_atendimento;
		
		if ((cont == (tempo_max/2) && (tempo_max > 240)))
		/*intervalo de almoco*/
		{
			sleep(1.5);
		}
		
		cont += tempo_atendimento;
		
		if ((cont_n_prio == 2) && (topo(&fila_segunda_dose) == 20))
		/*mau-humor: caso ja tenham passado 6 pessoas (4 prioritarios e 2 nao prioritarios) na frente de um prioritario, ele sai da fila*/
		{
			remover_primeiro_elemento(&tempo_atendimento, &fila_segunda_dose);
			saiu++;
			cont_n_prio = 0;
		}
	}
	atendente_atual->tempo_trabalhado = cont; 
	pthread_exit(NULL);
}

void criando_filas(int tam)
/*inicializando e preenchendo as filas de vacinacao*/
{
	inicializar_filap(&fila_primeira_dose);
	inicializar_filap(&fila_segunda_dose);
	preenche_a_fila(&fila_primeira_dose, tam);
	preenche_a_fila(&fila_segunda_dose, tam);
}

void iniciar_variaveis()
/*inicializando variaveis de contagem*/
{
	vacinados_primeira = 0; 
	vacinados_segunda = 0;
	tempo_total_primeira = 0;
	tempo_total_segunda = 0;
	saiu = 0;
	passou = 0;
}

void iniciando_atendentes(int num_atendentes)
/*inicializando e preenchendo o vetor de atendentes*/
{
	for(int cont = 0; cont < num_atendentes; cont++)
	{
		vet_atende[cont].expediente = 0;
		memset(vet_atende[cont].nome, 0, sizeof(char));
	}
	gerencia_profissionais(num_atendentes, vet_atende);
}

int main(void)
{
	srand(time(NULL));
	
	int num_atendentes = 1 + (rand() % 5);
	int tam = 50;
	int status;
	
	iniciar_variaveis();
	criando_filas(tam);
	iniciando_atendentes(num_atendentes);
	
	for (int cont = 0; cont < num_atendentes; cont++)
	{
		vet_atende[cont].atendido_primeira[0] = 0;
		vet_atende[cont].atendido_segunda[0] = 0;
		vet_atende[cont].atendido_primeira[1] = 0;
		vet_atende[cont].atendido_segunda[1] = 0;
	}
	
	total_vacinados[0] = 0;
	total_vacinados[1] = 0;
	
	for (int cont2 = 0; cont2 < num_atendentes; cont2++)
	/*criando as threads*/
	{
		status = pthread_create(&thread[cont2], NULL, iniciar_atendimento, (void *)(&vet_atende[cont2]));
		if(status != 0)
		{
			printf("Erro ao criar o thread.\n");
			exit(EXIT_FAILURE);
		}
	}
	
	for (int cont3 = 0; cont3 < num_atendentes; cont3++)
	{
		status = pthread_join(thread[cont3], NULL);
		if(status != 0)
		{
			printf("Erro ao aguardar finalização da thread.\n");
			exit(EXIT_FAILURE);
		}
	}
	
	printf("\n+++ FIM DO EXPEDIENTE +++\n");
	printf("\n");
	
	printf("---------------------------------------------------\n");
	
	printf("ATENDIDOS (primeira dose):\n");
	printf("\n");
	
	printf("Total de pessoas vacinadas com a primeira dose: %d\n", total_vacinados[0]);
	printf("prioridade 10: %d pessoas\n", total_vacinados[0]-vacinados_primeira);
	printf("prioridade 20: %d pessoas\n", vacinados_primeira);
	printf("\n");
	
	printf("Total do expediente para a primeira dose: %d horas\n", tempo_total_primeira/60);
	
	printf("---------------------------------------------------\n");
	
	printf("ATENDIDOS (segunda dose):\n");
	printf("\n");
	
	printf("Total de pessoas vacinadas com a segunda dose: %d\n", total_vacinados[1]);
	printf("prioridade 10: %d pessoas\n", total_vacinados[1]-vacinados_segunda);
	printf("prioridade 20: %d pessoas\n", vacinados_segunda);
	printf("\n");
	
	printf("Total do expediente para a segunda dose: %d horas\n", tempo_total_segunda/60);
	
	printf("---------------------------------------------------\n");
		
	printf("total de atendentes que foram trabalhar: %d\n\n", num_atendentes);
	for(int cont4 = 0; cont4 < num_atendentes; cont4++)
	{
		printf("Atendente: ");
		printf("%s\n", vet_atende[cont4].nome);
		if(vet_atende[cont4].expediente == 240)
		{
			printf("Expediente: MEIO-PERÍODO\n");
		}
		else if(vet_atende[cont4].expediente == 360)
		{
			printf("Expediente: ESTAGIÁRIO\n");
		}
		else if(vet_atende[cont4].expediente == 480)
		{
			printf("Expediente: TURNO COMPLETO\n");
		}
		else if(vet_atende[cont4].expediente == 600)
		{
			printf("Expediente: TURNO EMERGENCIAL\n");
		}
		printf("Horas cumpridas: %d horas\n", vet_atende[cont4].tempo_trabalhado/60);
		printf("Pacientes atendidos:\n");
		printf("prioridade 10 para a primeira dose: %d pessoas\n", vet_atende[cont4].atendido_primeira[0]);
		printf("prioridade 20 para a primeira dose: %d pessoas\n", vet_atende[cont4].atendido_primeira[1]);
		printf("prioridade 10 para a segunda dose: %d pessoas\n", vet_atende[cont4].atendido_segunda[0]);
		printf("prioridade 20 para a segunda dose: %d pessoas\n", vet_atende[cont4].atendido_segunda[1]);
		printf("\n");
	}
	
	printf("---------------------------------------------------\n");
	
	printf("%d nao prioritarios passaram na frente!\n", passou);
	printf("%d prioritarios sairam da fila!\n\n", saiu);
		
	printf("Total de pessoas que não foram atendidas para a primeira dose: %d\n", fila_primeira_dose.tamanho);
	if(fila_primeira_dose.tamanho != 0)
	{
		printf("Numero de pessoas de prioridade 10 que não foram atendidas na fila da primeira dose: %d\n", fila_primeira_dose.tamanho-conta20(&fila_primeira_dose));
		printf("Numero de pessoas de prioridade 20 que não foram atendidas na fila da primeira dose: %d\n", conta20(&fila_primeira_dose));
	}
	printf("\n");
	
	printf("Total de pessoas que não foram atendidas para a segunda dose: %d\n", fila_segunda_dose.tamanho);
	if(fila_segunda_dose.tamanho != 0)
	{ 
		printf("Numero de pessoas de prioridade 10 que não foram atendidas na fila da primeira dose: %d\n", fila_segunda_dose.tamanho-conta20(&fila_segunda_dose));
		printf("Numero de pessoas de prioridade 20 que não foram atendidas na fila da primeira dose: %d\n", conta20(&fila_segunda_dose));
	}
	printf("\n");
	
	destroir_fila(&fila_primeira_dose); 
	destroir_fila(&fila_segunda_dose);
	
	pthread_mutex_destroy(&mutex);
	
	return 0;	
}
