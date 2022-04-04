/**
 * @file jobs.c
 * @author diogo miranda
 * @date 2022
 * @brief M�todos para manipular Lista Ligada Simples (Maquinas)
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "maquinas.h"

/**
*	@brief Cria nova maquina.
*
*	Aloca mem�ria necess�ria para armazenar uma maquina em mem�ria
*
*   @param id Identificador da maquina
*	@param disponivel Se a maquina esta a ser utilizada ou nao
*
*/
Maquina* CriaMaquina(int id, bool disponivel)
{
	//alocar mem�ria tendo em conta o tamanho do bloco de mem�ria Job
	Maquina* newMaquina = (Maquina*)malloc(sizeof(Maquina));

	if (newMaquina == NULL) return NULL;

	newMaquina->id = id;
	newMaquina->disponivel = disponivel;
	//�ltimo node por isso define apontador como NULL
	newMaquina->next = NULL;
	return newMaquina;
}

/**
* @brief Insere maquina no final da lista
* @param h Inicio da Lista
* @param novo Nova maquina a inserir
* @return Inicio da Lista
*/
Maquina* InsereMaquinaFim(Maquina* h, Maquina* novo) {
	//Verificar se a nova maquina j� existe!!!
	if (ExisteMaquina(h, novo->id)) return h;	//se existir n�o insere!

	//lista vazia?
	if (h == NULL) {
		h = novo;
	}
	else
	{
		//Posicionar-se no fim da lista
		Maquina* aux = h;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//insere no fim da lista
		aux->next = novo;
	}
	return h;
}

/**
* @brief Verifica se maquina existe.
* @param h Inicio da Lista
* @param id	Identificador a procurar
* @return True/False
*/
bool ExisteMaquina(Maquina* h, int id) {
	if (h == NULL) return false;
	Maquina* aux = h;
	while (aux != NULL) {
		if (aux->id == id)
			return true;
		aux = aux->next;
	}
	return false;
}