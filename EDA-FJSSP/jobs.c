/**
 * @file jobs.c
 * @author diogo miranda
 * @date 2022
 * @brief Métodos para manipular Lista Ligada Simples (Job)
*/

#include <stdio.h>
#include "data.h"


/**
*	@brief Cria novo Job.
*
*	Aloca memória necessária para armazenar um job em memória
*
*   @param id Identificador do Job
*	@param nome Nome do Job
*	@param operacoes Array de operações
*
*/
Job* CriaJob(int id, char* nome, Operacao operacoes[7])
{
	//alocar memória tendo em conta o tamanho do bloco de memória Job
	Job* newJob = (Job*)malloc(sizeof(Job));
	
	//pode não haver memória!!!
	if (newJob == NULL) return NULL;	
	
	newJob->id = id;
	strcpy(newJob->nome, nome);

	newJob->next = NULL;
	return newJob;
}

/**
* @brief Remove operação de um job.
* 
* @param h Apontador para inicio da Lista
* @param jobId Identificador do job a alterar
* @param operacaoId Identificador da operação a remover
* @return Apontador para Lista
*/
Job* RemoveOperacao(Job* h, int jobId, int operacaoId) {
	//Lista vazia
	if (h == NULL) return NULL; 

	Job* aux = h;
	Job* auxAnt = aux;

	//procura job para remover operação
	while (aux && aux->id != jobId) {	
		aux = aux->next;
	}
	
	//se encontrou job, procura operacao a remover
	if (aux != NULL) {
		//percorrer operações
		//verificar se operaçao corresponde, remove
		
	return h;
}