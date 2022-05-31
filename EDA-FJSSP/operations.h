/**
 * @file operations.h
 * @author diogo miranda
 * @date 2022
 * @brief Operations - Definitions of Structs, Constants, and Function Signatures
 *
*/

//prevent double declaration of any identifiers (types, etc)
#ifndef OPERATIONS
#define OPERATIONS

#include <stdio.h>
#include <stdbool.h>
#include "machines.h"

//avoid MSG ERROS: _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996 ) 

#pragma region Structs

/**
 * @brief Struct to store an operation
 *
 * An operation contains an identifier (@@id), a job identifier (@@jobId),
 * a machine identifier (@@machineId), a execution time (@@executionTime), 
 * an operation state (@@finished) and a pointer (*next).
 */
typedef struct operation {
	int id;
	int type;
	int machineId;
	float executionTime;
	bool finished; //each operation should be executed to complete a job
	struct Operation* next;
} Operation;

#pragma endregion

#pragma region FunctionSignatures

//creates operation
Operation* CreateOperation(Operation* op, int id, int type, int maqId, int time, bool finished); 

//inserts operations in the operations list
Operation* InsertOperationEnd(Operation* h, Operation* n);

//removes operation from the operations list
Operation* RemoveOperation(Operation* h, int id);

Operation* UpdateOperation(Operation* h, int id, int type, int maqId, int time, bool finished);

Operation* SearchOperation(Operation* h, int id);

// gets operation with minimum time for a specific type of operation
Operation* GetOperationMinTime(Operation* h, int type);

// gets operation with maximum time for a specific type of operation
Operation* GetOperationMaxTime(Operation* h, int type);

// calculates the maximum time for a specific opearation
float CalculateMaxTimeOperation(Operation* h, int opId);
 
void ShowAllOperations(Operation* h);

//cheks if an operation exists in the operations list
bool OperationExist(Operation* h, int id);

void ShowOperation(Operation* op, int id);

#pragma endregion


#endif

