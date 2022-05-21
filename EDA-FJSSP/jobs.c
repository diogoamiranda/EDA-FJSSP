/**
 * @file jobs.c
 * @author diogo miranda
 * @date 2022
 * @brief Methods for manipulating Singly Linked Lists (Jobs)
*/

#include <stdio.h>
#include <stdlib.h>
#include "jobs.h"
#include "operations.h"


/**
* @brief Creates a new job.
*
* Allocates necessary memory to store a Job in memory
*
* @param id Job identifier
* @param name Job name
*
*/
Job* CreateJob(int id, char* name){
	//alocar memória tendo em conta o tamanho do bloco de memória Job
	Job* newJob = (Job*)malloc(sizeof(Job));

	if (newJob == NULL) return NULL;

	newJob->id = id;
	strcpy(newJob->name, name);
	//without operations by default
	newJob->operations = NULL;
	//last node so sets pointer to NULL
	newJob->next = NULL;
	return newJob;
}

/**
* @brief Inserts job at the end of the job list
* @param h Head of the list
* @param n New job to insert
* @return Head of the list
*/
Job* InsertJobEnd(Job* h, Job* n) {
	//Check if the new job already exists
	if (JobExist(h, n->id)) return h;	//if it exists, don't insert

	//empty list?
	if (h == NULL) {
		h = n;
	}
	else
	{
		//go to the end of the list
		Job* aux = h;
		while (aux->next != NULL) {
			aux = aux->next;
		}
		//inserts at the end of the list
		aux->next = n;
	}
	return h;
}

/**
* @brief Preserve data in file
* Writes all nodes in the List to a file
*/
bool SaveJobBinary(char* fileName, Job* h) {
	FILE* fp;

	if (h == NULL) return false;
	if ((fp = fopen(fileName, "wb")) == NULL) return false;

	Job* aux = h;
	JobFile auxJob;
	//write n records to file
	while (aux) {
		//Write job data to file without any pointers
		auxJob.id = aux->id;
		strcpy(auxJob.name, aux->name);
		auxJob.finished = aux->finished;
		fwrite(&auxJob, sizeof(auxJob), 1, fp);
		aux = aux->next;
	}
	fclose(fp);
	return true;
}

/**
* @brief Read information about a job
*/
Job* ReadJobBinary(char* nomeFicheiro) {
	FILE* fp;
	Job* h = NULL;
	Job* aux;

	if ((fp = fopen(nomeFicheiro, "rb")) == NULL) return NULL;
	fclose(fp);
	return h;
}

/**
* @brief Delete all nodes from a job list
* @param h Pointer to the head of the list
*/
void DeleteAllJobs(Job** h) {
	if (h != NULL) {
		Job* aux;
		while (*h) {
			aux = *h;
			*h = (*h)->next;
			free(aux);
		}
	}
}

/**
* @brief Check if a job exists.
* @param h Head of the list
* @param id	Identifier to be searched
* @return True/False
*/
bool JobExist(Job* h, int id) {
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
* @brief Search for a job.
* @param h Head of the list	
* @param id Identifier to be searched
* @return Pointer to the copy of founded job
*/
Job* SearchJob(Job* h, int id) {
	if (h == NULL) return NULL;
	else
	{
		Job* aux = h;
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
* @brief Calculates the minimum time a job takes to complete
* @param h Head of the job list
* @param hOp Head of the operations list
* @param jobId Job identifier
* @return minTimeJob Minimum time that a job takes to complete
*/
float CalculateMinTimeJob(Job* h, Operation* hOp, int jobId) {
	Job* aux = SearchJob(h, jobId);
	float minTimeJob = 0;

	return minTimeJob;
}

float CalculateMaxTimeJob(int jobId) {
	return 0.1;
}

float CalculateAvgTimeJobOperations(int jobId) {
	return 2;
}

//2nd Phase
Job* InsertJobOperation(Job* h, Operation* o, int jobId) {
	// if empty job list
	if (h == NULL) return NULL;	
	// search job
	Job* aux = SearchJob(h, jobId);
	if (aux) {
		//add operations
		aux->operations = o;
	}
	
	return aux;
}