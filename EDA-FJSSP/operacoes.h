/**
 * @file data.h
 * @author diogo miranda
 * @date 2022
 * @brief Opera��es - Defini��es de Structs, Constantes e Assinaturas de Fun��es
 *
*/

//prevenir declara��o dupla de quaisquer identificadores (tipos, etc)
#ifndef OPERACOES
#define OPERACOES

#include <stdio.h>
#include <stdbool.h>
#include "maquinas.h"

//evita MSG ERROS: _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996 ) 

#pragma region Structs

/**
 * @brief Estrutura para armazenar uma opera��o.
 *
 * Uma opera��o contem um identificador (@@id)
 * e um apontador (*next).
 */
typedef struct {
	int id;
	int maquinaId;
	int tempo;
	bool terminada; //Cada opera��o deve ser executada para completar o job
	struct Operacao* next;
} Operacao;

#pragma endregion

#pragma region AssinaturasFun��es

// cria opera��o(reservar memoria)
Operacao* CriaOperacao(int id, int maq_id, int tempo, bool terminada); 

// insere opera��o na lista de opera��es
Operacao* InsereOperacaoFim(Operacao* h, Operacao* n);

//remove opera��o da lista de opera��es
Operacao* RemoveOperacao(Operacao* h, int id);

//altera opera��o
Operacao* AlteraOperacao(Operacao* h, int id, int tempo, bool terminada);

//procura opera�ao
Operacao* ProcuraOperacao(Operacao* h, int id);

//mostra todas as opera��es
void ListaOperacoes(Operacao* h);

//verifica se existe opera��o na lista
bool ExisteOperacao(Operacao* h, int id);

#pragma endregion


#endif
