/**
 * @file data.h
 * @author diogo miranda
 * @date 2022
 * @brief Maquinas - Definições de Structs, Constantes e Assinaturas de Funções
 *
*/

//prevenir declaração dupla de quaisquer identificadores (tipos, etc)
#ifndef MAQUINAS
#define MAQUINAS

#include <stdio.h>
#include <stdbool.h>

//evita MSG ERROS: _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996 ) 

#pragma region Structs

/**
 * @brief Estrutura para armazenar uma máquina.
 *
 * Uma maquina contem um identificador (@@id),
 * um boolean (@@disponivel) que identifica se a maquina está
 * ou não disponivel para ser usada e um apontador para a proxima maquina (next).
 * 
 * Todas as máquinas estão disponíveis no instante t = 0.
 */
typedef struct {
	int id;
	bool disponivel;
	struct Maquina* next;
} Maquina;

#pragma endregion

#pragma region AssinaturasFunções

// cria maquina(reservar memoria)
Maquina* CriaMaquina(int id, bool disponivel);

// insere maquinas na lista de maquinas
Maquina* InsereMaquinaFim(Maquina* h, Maquina* n);

//verifica se existe maquina na lista
bool ExisteMaquina(Maquina* h, int id);

#pragma endregion

#endif
