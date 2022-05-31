/**
 * @file operations.c
 * @author diogo miranda
 * @date 2022
 * @brief Methods for manipulating Singly Linked Lists (Operations)
*/

#include <stdio.h>
#include <stdlib.h>
#include "operations.h"

/**
* @brief Creates a new operation.
*
* Allocates necessary memory to store an operation in memory
*
* @param id Operation identifier
* @param type Operation type
* @param maqId Machine identifier
* @param time Time units required for the operation
* @param finished Whether the operation is finished or not
*
*/
Operation* CreateOperation(Operation* op, int id, int type, int maqId, int time, bool finished){
	Operation* newOperation = (Operation*)malloc(sizeof(Operation));
	if (newOperation == NULL) return NULL;

	newOperation->id = id;
	newOperation->type = type;
	newOperation->machineId = maqId;
	newOperation->executionTime = time;
	newOperation->finished = finished;
	//points to last operation
	newOperation->next = op;
	return newOperation;
}

/**
* @brief Inserts new operation at the end of the operations list
* @param h Head of the operations list
* @param n New operation to insert
* @return Head of the list
*/
Operation* InsertOperationEnd(Operation* h, Operation* n) {
	//check if new operation already exists
	if (OperationExist(h, n->id)) return h;	//if it exists, don't insert

	//empty list?
	if (h == NULL) {
		h = n;
	}
	else
	{
		//go to the end of the list
		Operation* aux = h;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//inserts at the end of the list
		aux->next = n;
	}
	return h;
}

/**
* @brief Check if operation exists.
* @param h Head of the list
* @param id	Identifier to be searched
* @return True/False
*/
bool OperationExist(Operation* h, int id) {
	if (h == NULL) return false;
	Operation* aux = h;
	while (aux != NULL) {
		if (aux->id == id)
			return true;
		aux = aux->next;
	}
	return false;
}

/**
* @brief Remove Operation
* @param h Head of the list
* @param id	Identifier to be removed
*/
Operation* RemoveOperation(Operation* h, int id) {
	//empty list?
	if (h == NULL) return NULL;			

	if (h->id == id) {		
		Operation* aux = h;
		h = h->next;
		free(aux);
	}
	else
	{
		Operation* aux = h;
		Operation* auxPrev = aux;
		//search id to remove
		while (aux && aux->id != id) {	
			auxPrev = aux;
			aux = aux->next;
		}
		//if founded, remove
		if (aux != NULL) {					
			auxPrev->next = aux->next;
			free(aux);
		}
	}
	return h;
}

/**
* @brief Update Operation
* 
* @param h Head of the list
* @param id Operation identifier
* @param type Operation type
* @param maqId Machine identifier
* @param time Time units required for the operation
* @param finished Whether the operation is finished or not
* @return pointer to list
*/
Operation* UpdateOperation(Operation* h, int id, int type, int maqId, int time, bool finished) {
	Operation* aux = SearchOperation(h, id);
	//founded an operation?
	if (aux != NULL)		
	{
		aux->executionTime = time;
		aux->finished = finished;
	}
	return h;
}

/**
* @brief Search for an operation
* @param h Head of the list
* @param id	Identifier to be searched
*/
Operation* SearchOperation(Operation* h, int id) {
	if (h == NULL) return NULL;		
	else
	{
		Operation* aux = h;
		while (aux != NULL) {
			if (aux->id == id) {
				return (aux);
			}
			aux = aux->next;
		}
		return NULL;
	}
}

/**
 * Calculates the minimum time of a specific operation.
 * 
 * \param h Head of the operations list
 * \param opId Operation identifier
 * \return 
 */
float CalculateMinTimeOperation(Operation* h, int opId) {
	float minTime = 0;

	Operation* aux = h;
	while (aux != NULL) {
		if (aux->id == opId) {
			if (minTime == 0 || minTime > aux->executionTime) {
				minTime = aux->executionTime;
			}
		}
		aux = aux->next;
	}
	return minTime;
}

/**
 * Calculates the maximum time of a specific operation.
 *
 * \param h Head of the operations list
 * \param opId Operation identifier
 * \return
 */
float CalculateMaxTimeOperation(Operation* h, int opId) {
	float maxTime = 0;

	Operation* aux = h;
	while (aux != NULL) {
		if (aux->id == opId) {
			if (maxTime == 0 || maxTime < aux->executionTime) {
				maxTime = aux->executionTime;
			}
		}
		aux = aux->next;
	}
	return maxTime;
}

/**
 *	@brief Show all operations of the operations list
 *  @param h Head of the operations list
 */
void ShowAllOperations(Operation* h) {
	Operation* aux = h;
	while (aux) {
		printf("\nOperations List:\n");
		printf("Operation ID = %d\n", aux->id);
		printf("Operation type = %d\n", aux->type);
		printf("Machine ID  = %d\n", aux->machineId);
		printf("Required time(units) = %.2f\n", aux->executionTime);
		printf("Operation finished = %d\n", aux->finished);
		aux = aux->next;
	}
}

/**
 *	@brief Show a specific operation data
 *  @param op Operation
 */
void ShowOperation(Operation* op, int id) {
	Operation* aux = SearchOperation(op, id);
	if (aux !=NULL) {
		printf("\nOperation ID = %d\n", aux->id);
		printf("Operation type = %d\n", aux->type);
		printf("Machine ID  = %d\n", aux->machineId);
		printf("Required time(units) = %.2f\n", aux->executionTime);
		printf("Operation finished = %d\n\n", aux->finished);
	}
}

/**
 * Get operation with minimum time for a specific type of operation.
 * 
 * \param op Head of operations list
 * \param type Operation type
 * \return 
 */
Operation* GetOperationMinTime(Operation* op, int type) {
	Operation* aux = op;
	Operation* finalOp = NULL;
	while (aux != NULL) {
		if ((finalOp == NULL && aux->type == type) || (aux->type == type && aux->executionTime < finalOp->executionTime)) {
			finalOp = aux;
		}
		aux = aux->next;
	}

	return finalOp;
}

/**
 * Get operation with maximum time for a specific type of operation.
 * 
 * \param op Head of operations list
 * \param type Operation type
 * \return 
 */
Operation* GetOperationMaxTime(Operation* op, int type) {
	Operation* aux = op;
	Operation* finalOp = NULL;
	while (aux != NULL) {
		if ((finalOp == NULL && aux->type == type) || (aux->type == type && aux->executionTime > finalOp->executionTime)) {
			finalOp = aux;
		}
		aux = aux->next;
	}

	return finalOp;
}
