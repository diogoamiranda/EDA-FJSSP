/**
 * @file jobs.c
 * @author diogo miranda
 * @date 2022
 * @brief M�todos para manipular Lista Ligada Simples (Job)
*/

#include <stdio.h>
#include <stdlib.h>
#include "jobs.h"


/**
*	@brief Cria novo Job.
*
*	Aloca mem�ria necess�ria para armazenar um job em mem�ria
*
*   @param id Identificador do Job
*	@param nome Nome do Job
*
*/
Job* CriaJob(int id, char* nome, int operacoes[]){
	//comprimento do array operacoes
	int opLength = sizeof(operacoes) / sizeof(int);

	//alocar mem�ria tendo em conta o tamanho do bloco de mem�ria Job
	Job* newJob = (Job*)malloc(sizeof(Job) + sizeof(operacoes));

	if (newJob == NULL) return NULL;

	newJob->id = id;
	strcpy(newJob->nome, nome);
	//define as operacoes do job
	for (int i = 0; i < opLength; i++){
		newJob->operacoes[i] = operacoes[i];
	}
	//�ltimo node por isso define apontador como NULL
	newJob->next = NULL;
	return newJob;
}

/**
* @brief Insere job no final da lista
* @param h Inicio da Lista
* @param novo Novo final a inserir
* @return Inicio da Lista
*/
Job* InsereJobFim(Job* h, Job* novo) {
	//Verificar se a novo job j� existe!!!
	if (ExisteJob(h, novo->id)) return h;	//se existir n�o insere!

	//lista vazia?
	if (h == NULL) {
		h = novo;
	}
	else
	{
		//Posicionar-se no fim da lista
		Job* aux = h;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//insere no fim da lista
		aux->next = novo;
	}
	return h;
}

/**
* @brief Preservar dados em ficheiro
* Grava todos os nodos da Lista em Ficheiro
*/
bool GravarJobBinario(char* nomeFicheiro, Job* h, int totalOperacoes) {
	FILE* fp;

	if (h == NULL) return false;
	if ((fp = fopen(nomeFicheiro, "wb")) == NULL) return false;

	//grava n registos no ficheiro
	Job* aux = h;
	JobFile auxJob;	//para gravar em ficheiro!
	while (aux) {		//while(aux!=NULL)
		//Colocar no registo de ficheiro a inf que est� no registo de mem�ria
		auxJob.id = aux->id;
		strcpy(auxJob.nome, aux->nome);
		auxJob.terminado = aux->terminado;
		//TODO: percorrer a lista de operacoes, comparar os ids e mostrar toda a informacao
		for (int i = 0; i < totalOperacoes; i++){
			auxJob.operacoes[i] = aux->operacoes[i];
		}
		fwrite(&auxJob, sizeof(auxJob), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}

/**
* @brief L� informa��o de ficheiro
*/
Job* LerJobBinario(char* nomeFicheiro, int operacoes[]) {
	FILE* fp;
	Job* h = NULL;
	Job* aux;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;
	//l� n� registos no ficheiro
	JobFile auxJogo;
	while (fread(&auxJogo, sizeof(JobFile), 1, fp)) {
		aux = CriaJob(auxJogo.id, auxJogo.nome, operacoes);
		h = InsereJobFim(h, aux);
	}
	fclose(fp);
	return h;
}

/**
* @brief Destroi todos os nodos da lista job
* @param h Apontador para inicio da Lista
*/

void DestroiListaJobs(Job** h) {
	if (h != NULL) {
		Job* aux;
		while (*h) {
			aux = *h;
			*h = (*h)->next;
			free(aux);
		}
	}
}

/**
* @brief Verifica se job existe.
* @param h Inicio da Lista
* @param id	Identificador a procurar
* @return True/False
*/
bool ExisteJob(Job* h, int id) {
	if (h == NULL) return false;
	Operacao* aux = h;
	while (aux != NULL) {
		if (aux->id == id)
			return true;
		aux = aux->next;
	}
	return false;
}

float CalculaMinTempoJob(int jobId) {
	return 0.2;
}

float CalculaMaxTempoJob(int jobId) {
	return 0.1;
}

float CalculaMediaTempoOperacoesJob(int jobId) {
	return 2;
}
/**
 2a fase
*/
/*Job* InsereOperacaoJob(Job* h, Operacao* o, int jobId) {
	// se lista vazia
	if (h == NULL) return NULL;	
	//se operacao n�o tem informa��o
	if (o == NULL) return h;	

	Job* aux = ProcuraJob(h, jobId);
	//se existe esse job
	
	return h;
}
*/