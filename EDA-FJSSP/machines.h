/**
 * @file machines.h
 * @author diogo miranda
 * @date 2022
 * @brief Machines - Definitions of Structs, Constants, and Function Signatures
 *
*/

//prevent double declaration of any identifiers (types, etc)
#ifndef MACHINES
#define MACHINES

#include <stdio.h>
#include <stdbool.h>

//avoid MSG ERROS: _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996 ) 

#pragma region Structs

/**
 * @brief Struct to store a machine.
 *
 * A machine contains an identifier(@@id),
 * a boolean (@@available) that identifies whether or not the machine is available for use 
 * and a pointer to the next machine (@@next)
 * 
 * All machines are available at the same time (t = 0).
 */
typedef struct machine{
	int id;
	bool available;
	struct Machine* next;
} Machine;

#pragma endregion

#pragma region FunctionSignatures

// creates machine (allocates memory)
Machine* CreateMachine(int id, bool available);

// inserts machine in machine list
Machine* InsertMachineEnd(Machine* h, Machine* n);

// checks if the machine already exists in the list
bool MachineExist(Machine* h, int id);

#pragma endregion

#endif
