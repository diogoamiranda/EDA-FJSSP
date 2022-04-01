/**
 * @file jobs.c
 * @author diogo miranda
 * @date 2022
 * @brief M�todos para manipular Lista Ligada Simples (Job)
*/

#include <stdio.h>
#include "data.h"


/**
*	@brief Cria novo Job.
*
*	Aloca mem�ria necess�ria para armazenar um job em mem�ria
*
*   @param id Identificador do Job
*	@param nome Nome do Job
*	@param operacoes Array de opera��es
*
*/
Job* CriaJob(int id, char* nome, Operacao operacoes[7])
{
	//alocar mem�ria tendo em conta o tamanho do bloco de mem�ria Job
	Job* newJob = (Job*)malloc(sizeof(Job));
	
	//pode n�o haver mem�ria!!!
	if (newJob == NULL) return NULL;	
	
	newJob->id = id;
	strcpy(newJob->nome, nome);

	newJob->next = NULL;
	return newJob;
}

/**
* @brief Remove opera��o de um job.
* 
* @param h Apontador para inicio da Lista
* @param jobId Identificador do job a alterar
* @param operacaoId Identificador da opera��o a remover
* @return Apontador para Lista
*/
Job* RemoveOperacao(Job* h, int jobId, int operacaoId) {
	//Lista vazia
	if (h == NULL) return NULL; 

	Job* aux = h;
	Job* auxAnt = aux;

	//procura job para remover opera��o
	while (aux && aux->id != jobId) {	
		aux = aux->next;
	}
	
	//se encontrou job, procura operacao a remover
	if (aux != NULL) {
		//percorrer opera��es
		//verificar se opera�ao corresponde, remove
		
	return h;
}