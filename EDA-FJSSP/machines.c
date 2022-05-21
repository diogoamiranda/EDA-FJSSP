/**
 * @file machines.c
 * @author diogo miranda
 * @date 2022
 * @brief Methods for manipulating Singly Linked Lists (Machines)
*/

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include "machines.h"

/**
*	@brief Creates a new machine.
*
*	Allocates necessary memory to store a machine in memory
*
*   @param id Machine identifier
*	@param available Whether the machine is being used or not
*
*/
Machine* CreateMachine(int id, bool available)
{
	//allocate memory taking into account the size of the Job memory block
	Machine* newMachine = (Machine*)malloc(sizeof(Machine));

	if (newMachine == NULL) return NULL;

	newMachine->id = id;
	newMachine->available = available;
	//last node so sets pointer to NULL
	newMachine->next = NULL;
	return newMachine;
}

/**
* @brief Inserts machine at the end of the machine list
* @param h Head of the list
* @param n New machine to insert
* @return Inicio da Lista
*/
Machine* InsertMachineEnd(Machine* h, Machine* n) {
	//Check if the new machine already exists
	if (MachineExist(h, n->id)) return h;	// if it exists, don't insert

	//empty list?
	if (h == NULL) {
		h = n;
	}
	else
	{
		//go to the end of the list
		Machine* aux = h;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//inserts at the end of the list
		aux->next = n;
	}
	return h;
}

/**
* @brief Check if machine exists.
* @param h Head of the list
* @param id	Identifier to be searched
* @return True/False
*/
bool MachineExist(Machine* h, int id) {
	if (h == NULL) return false;
	Machine* aux = h;
	while (aux != NULL) {
		if (aux->id == id)
			return true;
		aux = aux->next;
	}
	return false;
}