/**
 * @file data.h
 * @author diogo miranda
 * @date 2022
 * @brief Jobs - Definições de Structs, Constantes e Assinaturas de Funções
 *
*/

//prevenir declaração dupla de quaisquer identificadores (tipos, etc)
#ifndef JOBS
#define JOBS

#include <stdio.h>
#include <stdbool.h>
#include "operacoes.h"

//evita MSG ERROS: _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996 ) 

#pragma region Structs

/**
 * @brief Estrutura dinâmica para armazenar um job.
 *
 * Um job contem um identificador (@@id), um nome (@@nome)
 * e um apontador (*next).
 */
typedef struct {
	int id;
	char nome[50];
	bool terminado;
	int operacoes[10]; // ids de operacoes associadas
	struct Job* next; // apontador para o proximo bloco de memoria/node do tipo Job
} Job;

/**
 * @brief Estrutura para armazenar um job em ficheiro
 *
 * Um job contem um identificador (@@id), um nome (@@nome),
 * um conjunto finito de operações (@@operacoes)
 */
typedef struct JobFile {
	int id;
	char nome[50];
	bool terminado;
	int operacoes[10]; // ids de operacoes associadas
}JobFile;

#pragma endregion

#pragma region AssinaturasFunções

// cria job(reservar memoria)
Job* CriaJob(int id, char* nome, int operacoes[]);

//insere job no final da lista de Jobs
Job* InsereJobFim(Job* h, Job* n);

//insere operações na lista de operações de um job
Job* InsereOperacaoJob(Job* h, Operacao* o, int jobId);

// calcular o minimo de tempo que um job demora a ser executado
float CalculaMinTempoJob(int jobId);

// calcular o maximo de tempo que um job demora a ser executado
float CalculaMaxTempoJob(int jobId);

// calcular quantidade média de tempo necessário para completar uma operação x do job
float CalculaMediaTempoOperacaoJob(int jobId);

// calcular quantidade média das médias para completar uma operacao x do job
float CalculaMediaTempoOperacoesJob(int jobId);

//gravar dados de um job em ficheiro
bool GravarJobBinario(char* nomeFicheiro, Job* h, int totalOperacoes);

// ler ficheiro com dados de um job
Job* LerJobBinario(char* nomeFicheiro, int operacoes[]);

//apaga todos os nodes da lista de jobs
void DestroiListaJobs(Job** h);

#pragma endregion


#endif

