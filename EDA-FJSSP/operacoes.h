/**
 * @file data.h
 * @author diogo miranda
 * @date 2022
 * @brief Operações - Definições de Structs, Constantes e Assinaturas de Funções
 *
*/

//prevenir declaração dupla de quaisquer identificadores (tipos, etc)
#ifndef OPERACOES
#define OPERACOES

#include <stdio.h>
#include <stdbool.h>
#include "maquinas.h"

//evita MSG ERROS: _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996 ) 

#pragma region Structs

/**
 * @brief Estrutura para armazenar uma operação.
 *
 * Uma operação contem um identificador (@@id)
 * e um apontador (*next).
 */
typedef struct {
	int id;
	int maquinaId;
	int tempo;
	bool terminada; //Cada operação deve ser executada para completar o job
	struct Operacao* next;
} Operacao;

#pragma endregion

#pragma region AssinaturasFunções

// cria operação(reservar memoria)
Operacao* CriaOperacao(int id, int maq_id, int tempo, bool terminada); 

// insere operação na lista de operações
Operacao* InsereOperacaoFim(Operacao* h, Operacao* n);

//remove operação da lista de operações
Operacao* RemoveOperacao(Operacao* h, int id);

//altera operação
Operacao* AlteraOperacao(Operacao* h, int id, int tempo, bool terminada);

//procura operaçao
Operacao* ProcuraOperacao(Operacao* h, int id);

//mostra todas as operações
void ListaOperacoes(Operacao* h);

//verifica se existe operação na lista
bool ExisteOperacao(Operacao* h, int id);

#pragma endregion


#endif
