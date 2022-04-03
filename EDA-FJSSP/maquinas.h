/**
 * @file data.h
 * @author diogo miranda
 * @date 2022
 * @brief Maquinas - Defini��es de Structs, Constantes e Assinaturas de Fun��es
 *
*/

//prevenir declara��o dupla de quaisquer identificadores (tipos, etc)
#ifndef MAQUINAS
#define MAQUINAS

#include <stdio.h>
#include <stdbool.h>

//evita MSG ERROS: _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996 ) 

#pragma region Structs

/**
 * @brief Estrutura para armazenar uma m�quina.
 *
 * Uma maquina contem um identificador (@@id),
 * um boolean (@@disponivel) que identifica se a maquina est�
 * ou n�o disponivel para ser usada e um apontador para a proxima maquina (next).
 * 
 * Todas as m�quinas est�o dispon�veis no instante t = 0.
 */
typedef struct {
	int id;
	bool disponivel;
	struct Maquina* next;
} Maquina;

#pragma endregion

#pragma region AssinaturasFun��es

// cria maquina(reservar memoria)
Maquina* CriaMaquina(int id, bool disponivel);

// insere maquinas na lista de maquinas
Maquina* InsereMaquinaFim(Maquina* h, Maquina* n);

//verifica se existe maquina na lista
bool ExisteMaquina(Maquina* h, int id);

#pragma endregion

#endif
