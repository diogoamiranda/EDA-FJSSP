/**
 * @file data.h
 * @author diogo miranda
 * @date 2022
 * @brief Definições de Structs, Constantes e Assinaturas de Funções
 *
*/

//prevenir declaração dupla de quaisquer identificadores (tipos, etc)
#ifndef DATA
#define DATA

#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

//evita MSG ERROS: _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996 ) 

#pragma region Structs

/**
 * @brief Estrutura para armazenar uma máquina.
 *
 * Uma maquina contem um identificador (@@id)
 */
typedef struct {
	int id;
} Maquina;

/**
 * @brief Estrutura para armazenar um produto.
 *
 * Um produto contem um identificador (@@id) e um nome (@@nome)
 */
typedef struct {
	int id;
	char nome[50];
} Produto;

/**
 * @brief Estrutura para armazenar uma operação.
 *
 * Uma operação contem um identificador (@@id),
 * uma máquina que executará a operação (@@maquina_id)
 * e o tempo total em unidades (@@tempoTotal) para executar a operação
 * com essa máquina.
 */
typedef struct {
	int id;
	Maquina maquinaId;
	int tempoTotal;
} Operacao;

/**
 * @brief Estrutura dinâmica para armazenar um job.
 *
 * Um job contem um identificador (@@id), um nome (@@nome),
 * um conjunto finito de operações (@@operacoes) para executar o job
 * e um apontador (*next).
 */
typedef struct {
	int id;
	char nome[50];
	Operacao operacoes[7];
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
	Operacao operacoes[7];
}JobFile;

#pragma endregion

#pragma region AssinaturasFunções

Job* CriaJob(int id, char* nome, Operacao operacoes[7]);
Job* RemoveOperacao(Job* h, int jobId, int operacaoId);


#pragma endregion


#endif