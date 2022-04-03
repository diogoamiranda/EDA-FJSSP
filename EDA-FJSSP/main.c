/**
 * @file main.c
 * @author diogo miranda
 * @date 2022
 * @brief Manipulação da lista de Jobs
*/

#include <stdio.h>
#include "jobs.h"
#include "operacoes.h"
#include "maquinas.h"

/**
* Função main (main thread)
*/
int main() {

#pragma region FASE1_CRIAR_LISTAS
	Maquina* m1 = CriaMaquina(0, true);
	Maquina* m2 = CriaMaquina(1, true);
	Maquina* m3 = CriaMaquina(2, true);

	Maquina* inicioListaMaq = NULL;
	inicioListaMaq = InsereMaquinaFim(inicioListaMaq, m1);
	inicioListaMaq = InsereMaquinaFim(inicioListaMaq, m2);
	inicioListaMaq = InsereMaquinaFim(inicioListaMaq, m3);

	Operacao* op1 = CriaOperacao(0, 0, 4, false);
	Operacao* op2 = CriaOperacao(1, 1, 1, false);
	Operacao* op3 = CriaOperacao(2, 2, 5, false);

	Operacao* inicioListaOperacao = NULL;
	inicioListaOperacao = InsereMaquinaFim(inicioListaOperacao, op1);
	inicioListaOperacao = InsereMaquinaFim(inicioListaOperacao, op2);
	inicioListaOperacao = InsereMaquinaFim(inicioListaOperacao, op3);

	int operacacoesJobs [] = {0,2};

	Job* job1 = CriaJob(0, "vitafilmar", operacacoesJobs);
	Job* inicioListaJob = NULL;
	inicioListaJob = InsereJobFim(inicioListaJob, job1);

#pragma endregion

#pragma region FASE1_2
	
	//TODO: O TOTAL DE OPERACOES NAO DEVE SER ESTATICO
	bool b = GravarJobBinario("jobs.bin", inicioListaJob, 2);

	if (b == true) {
		DestroiLista(&inicioListaJob);
		inicioListaJob = LerJobBinario("jobs.bin", operacacoesJobs);
	}

#pragma endregion

#pragma region FASE1_3
	Operacao* op4 = CriaOperacao(4, 5, 5, false);
	inicioListaOperacao = InsereOperacaoFim(inicioListaOperacao, op4);

#pragma endregion

#pragma region FASE1_4
	inicioListaOperacao = RemoveOperacao(inicioListaOperacao, 4);

#pragma endregion

#pragma region FASE1_5
	inicioListaOperacao = AlteraOperacao(inicioListaOperacao, 3, 6, true);

#pragma endregion

#pragma region FASE1_6
	 float tempo = CalculaMinTempoJob(0);
	 printf("tempo minimo de %.2f unidades para terminar job", tempo);

#pragma endregion

#pragma region FASE1_7
	tempo = CalculaMaxTempoJob(0);
	printf("tempo maximo de %.2f unidades para terminar job", tempo);

#pragma endregion

#pragma region FASE1_8
	tempo = CalculaMediaTempoOperacoesJob(0);
	printf("tempo medio de %.2f unidades para concluir qualquer operacao do job", tempo);

#pragma endregion

	return 0;
}