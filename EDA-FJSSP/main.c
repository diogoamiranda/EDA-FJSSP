/**
 * @file main.c
 * @author diogo miranda
 * @date 2022
 * @brief Manipulação da lista de Jobs
*/

#include<stdio.h>
#include "data.h"

/**
* Função main (main thread)
*/
int main() {
	// criar maquinas, produtos, operaçoes e inserir jobs (se houver tempo)
	// inserir novas operaçoes para o job x (percorrer linked list e inserir no array)
	// remover operaçoes para o job x (percorrer linked list e remover do array de operaçoes)


#pragma region CriaListas
	//maquinas
	Maquina maq1, maq2;
	maq1.id = 0;
	maq2.id = 1;

	//produtos
	Produto prod1 = { 1, "prod1" };

	//operacoes
	Operacao op1 = { 0, maq1.id, 12 };

	//jobs
	Job* job1 = criaJob(7, "Jogo1", "A");

#pragma endregion

#pragma region ImprimeDados
	printf("Job id %d", job1->id);
	printf("Job %s", job1->nome);
	
	return 0;
}