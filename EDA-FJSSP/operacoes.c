/**
 * @file jobs.c
 * @author diogo miranda
 * @date 2022
 * @brief Métodos para manipular Lista Ligada Simples (Operações)
*/

#include <stdio.h>
#include <stdlib.h>
#include "operacoes.h"

/**
*	@brief Cria nova Operacao.
*
*	Aloca memória necessária para armazenar uma operacao em memória
*
*   @param id Identificador da Operacao
*	@param maq_id Identificador da maquina a executar Operacao
*	@param tempo Unidades de tempo necessárias para a operação
*	@param terminada Se a operação está ou não terminada
*
*/
Operacao* CriaOperacao(int id, int maqId, int tempo, bool terminada)
{
	//alocar memória tendo em conta o tamanho do bloco de memória Job
	Operacao* newOperacao = (Operacao*)malloc(sizeof(Operacao));

	if (newOperacao == NULL) return NULL;

	newOperacao->id = id;
	newOperacao->maquinaId = maqId;
	newOperacao->tempo = tempo;
	newOperacao->terminada = terminada;
	//último node por isso define apontador como NULL
	newOperacao->next = NULL;
	return newOperacao;
}

/**
* @brief Insere Operacao no final da lista
* @param h Inicio da Lista
* @param novo Nova operacao a inserir
* @return Inicio da Lista
*/
Operacao* InsereOperacaoFim(Operacao* h, Operacao* novo) {
	//Verificar se a nova operacao já existe!!!
	if (ExisteOperacao(h, novo->id)) return h;	//se existir não insere!

	//lista vazia?
	if (h == NULL) {
		h = novo;
	}
	else
	{
		//Posicionar-se no fim da lista
		Operacao* aux = h;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//insere no fim da lista
		aux->next = novo;
	}
	return h;
}

/**
* @brief Verifica se operacação existe.
* @param h Inicio da Lista
* @param id	Identificador a procurar
* @return True/False
*/
bool ExisteOperacao(Operacao* h, int id) {
	if (h == NULL) return false;
	Operacao* aux = h;
	while (aux != NULL) {
		if (aux->id == id)
			return true;
		aux = aux->next;
	}
	return false;
}

/**
* @brief Remove Operacao
* @param h Apontador para inicio da Lista
* @param id Identificador da operacao a alterar
* @return Apontador para Lista
*/
Operacao* RemoveOperacao(Operacao* h, int id) {
	//Lista vazia?
	if (h == NULL) return NULL;			

	//remove no inicio da lista
	if (h->id == id) {		
		Operacao* aux = h;
		h = h->next;
		free(aux);
	}
	else
	{
		Operacao* aux = h;
		Operacao* auxAnt = aux;
		//procura id a remover
		while (aux && aux->id != id) {	
			auxAnt = aux;
			aux = aux->next;
		}
		//se encontrou, remove
		if (aux != NULL) {					
			auxAnt->next = aux->next;
			free(aux);
		}
	}
	return h;
}

/**
* @brief Altera Operacao
* @param h Apontador para inicio da Lista
* @param id Codigo da operacao a alterar
* @param tempo Novo tempo daoperacao
* @param terminada Estado da operacao
* @return Apontador para Lista
*/
Operacao* AlteraOperacao(Operacao* h, int id, int tempo, bool terminada) {
	Operacao* aux = ProcuraOperacao(h, id);
	//se encontrou o jogo
	if (aux != NULL)		
	{
		aux->tempo = tempo;
		aux->terminada = terminada;
	}
	return h;
}

/**
* @brief Verifica se operacao existe
* @param Inicio da Lista
* @param id Identificador da operacao a procurar
* @return Apontador para operacao encontrada
*/
Operacao* ProcuraOperacao(Operacao* h, int id) {
	//lista vazia ?
	if (h == NULL) return NULL;		
	else
	{
		Operacao* aux = h;
		while (aux != NULL) {
			if (aux->id == id) {
				return (aux);
			}
			aux = aux->next;
		}
		return NULL;
	}
}

/**
 *	@brief Mostra todos as operações existentes na lista
 *  @param h Inicio da Lista
 */
void ListaOperacoes(Operacao* h) {
	Operacao* aux = h;
	while (aux) {
		printf("\nLista de operacoes:\n");
		printf("ID de operacao = %d\n", aux->id);
		printf("ID de maquina a executar operacao = %d\n", aux->maquinaId);
		printf("Unidades de tempo necessarias = %d\n", aux->tempo);
		printf("Operacao terminada = %d\n", aux->terminada);
		aux = aux->next;
	}
}