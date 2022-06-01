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
Job* CreateJob(int id, char* name) {
	//allocates a Job in memory
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
Job* ReadJobBinary(char* fileName) {
	FILE* fp;
	Job* h = NULL;
	Job* aux;

	if ((fp = fopen(fileName, "rb")) == NULL) return NULL;
	fclose(fp);
	return h;
}

/**
* @brief Removes all nodes from a job list
* @param h Pointer to the head of the list
*/
void RemoveAllJobs(Job** h) {
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
* @brief Removes a specif job from the job list
* @param h Pointer to the head of the list
*/
Job* RemoveJob(Job* h, int jobId) {
	Job* currJob = h; 
	Job* prevJob;

	//empty list?
	if (currJob == NULL) return NULL;

	if (currJob->id == jobId) {
		h = h->next;
		Operation* op = currJob->operations;
		RemoveOperations(op);
		free(currJob);
	}
	else
	{
		prevJob = h;
		currJob = prevJob->next;

		//search id to remove
		while (currJob && currJob->id != jobId) {
			prevJob = currJob;
			currJob = currJob->next;
		}
		//if founded, remove
		if (currJob != NULL) {
			prevJob->next = currJob->next;
			Operation* op = currJob->operations;
			RemoveOperations(op);
			free(currJob);
		}
	}
	return h;
}

/**
* @brief Check if a job exists.
* @param h Head of the list
* @param id	Identifier to be searched
* @return True/False
*/
bool JobExist(Job* h, int id) {
	if (h == NULL) return false;
	Job* aux = h;
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
* @brief Removes a specif operation from the job operations list
* @param h Pointer to the head of the list
*/
void RemoveJobOperation(Job* h, int jobId, int opId) {
	Job* auxJob = SearchJob(h, jobId);
	if (auxJob == NULL) return;

	Operation* op = auxJob->operations;
	Operation* hOp = auxJob->operations;
	while (op != NULL) {
		if (op->id == opId) {
			hOp = RemoveOperation(hOp, opId);
			return;
		}
		op = op->next;
	}

}

/**
 * Updates a specif operation from the job operations list.
 * 
 * \param h Head of the list
 * \param jobId Job identifier
 * \param opId Operation identifier
 * \param opType Operation type
 * \param opMachId Machine identifier
 * \param opTime Operation execution time
 * \param opFinished Whether the operation is finished or not
 * \return 
 */
Job* UpdateJobOperation(Job* h, int jobId, int opId, int opType, int opMachId, int opTime, bool opFinished) {
	Job* auxJob = SearchJob(h, jobId);
	if (auxJob == NULL) return;

	Operation* op = auxJob->operations;
	UpdateOperation(op, opId, opType, opMachId, opTime, opFinished);

	return auxJob;
}

/**
* @brief Calculates the minimum time a job takes to complete
* @param h Head of the job list
* @param jobId Job identifier
* @return minTimeJob Minimum time that a job takes to complete
*/
float CalculateMinTimeJob(Job* h, int jobId) {
	float minTimeJob = 0;
	Job* auxJob = SearchJob(h, jobId);
	//get job operations
	Operation* op = auxJob->operations;
	Operation* auxOp = NULL;
	while (op != NULL) {
		//TODO: remove order dependency from operations in the job operations list
		if (auxOp == NULL || auxOp->type != op->type) {
			auxOp = GetOperationMinTime(auxJob->operations, op->type);
			if (auxOp != NULL) {
				minTimeJob += auxOp->executionTime;
				ShowOperation(auxOp, auxOp->id);
			}
		}
		op = op->next;//next operation
	}

	return minTimeJob;
}

/**
* @brief Calculates the maximum time a job takes to complete
* @param h Head of the job list
* @param jobId Job identifier
* @return maxTimeJob Maximum time that a job takes to complete
*/
float CalculateMaxTimeJob(Job* h, int jobId) {
	float maxTimeJob = 0;
	Job* auxJob = SearchJob(h, jobId);
	//get job operations
	Operation* op = auxJob->operations;
	Operation* auxOp = NULL;
	while (op != NULL) {
		//TODO: remove order dependency from operations in the job operations list
		if (auxOp == NULL || auxOp->type != op->type) {
			auxOp = GetOperationMaxTime(auxJob->operations, op->type);
			if (auxOp != NULL) {
				maxTimeJob += auxOp->executionTime;
				ShowOperation(auxOp, auxOp->id);
			}
		}
		op = op->next;//next operation
	}

	return maxTimeJob;
}

/**
 * Calculates the average time necessary to complete a job operation,
 * list operations and prints average.
 * TODO: remove order dependency from operations in the job operations list
 * 
 * \param h Head of the jobs list
 * \param jobId Job identifier
 * \return 
 */
void ShowAvgTimeJobOperations(Job* h, int jobId) {
	float avgTimeOp = 0;
	float totalTimeOp = 0;
	int countOp = 0;
	int lastOpType = -1;

	Job* auxJob = SearchJob(h, jobId);
	//get job operations
	Operation* op = auxJob->operations;
	Operation* auxOp = auxJob->operations;
	while (op != NULL) {
		if (lastOpType != op->type) { //avoid multiple calculations for the same type of operation
			while (auxOp != NULL) {
				if (auxOp->type == op->type) {
					countOp++;
					totalTimeOp += auxOp->executionTime;
					lastOpType = auxOp->type;
					ShowOperation(auxJob->operations, auxOp->id);
				}
				auxOp = auxOp->next;
			}
			avgTimeOp = totalTimeOp / countOp;
			printf("Average time of %.2f to complete operation type %d\n", avgTimeOp, op->type);
			printf("***********************\n");
			//reset vars for next calculations
			countOp = 0;
			totalTimeOp = 0;
			avgTimeOp = 0;
			auxOp = auxJob->operations;
		}
		op = op->next;//next operation
	}
}

/**
 * Insert new operation in the operations list of a specific job.
 * TODO: CHECK IF OPERATION ALREADY EXISTS BEFORE INSERT
 * 
 * \param h Head of Jobs list
 * \param jobId Job identifier
 * \param opId Operation identifier
 * \param opType Operation type
 * \param machId Machine identifier
 * \param time Operation time
 * \param finished Operation state
 * \return 
 */
Job* InsertJobOperationEnd(Job* h, int jobId, int opId, int opType, int machId, int time, bool finished) {
	// if empty job list
	if (h == NULL) return NULL;
	// search job
	Job* aux = SearchJob(h, jobId);
	Operation* jobOp = NULL;
	if (aux) {
		jobOp = aux->operations;
		jobOp = CreateOperation(jobOp, opId, opType, machId, time, false);
		aux->operations = jobOp;
	}

	return h;
}

void ShowJobOperations(Job* h, int jobId) {
	Job* aux = SearchJob(h, jobId);
	if (aux) {
		Operation* op = aux->operations;
		printf("Job List:\n");
		printf("Job ID = %d\n", aux->id);
		printf("finished = %s\n", aux->finished ? "true" : "false");
		printf("********** Job Operations ***********\n");
		while (op != NULL) {
			printf("operation id = %d\n", op->id);
			printf("machine id = %d\n", op->machineId);
			printf("execution time = %.2f\n\n", op->executionTime);
			op = op->next;
		}
		printf("*************************\n");
	}
}

void ShowJobs(Job* h) {
	Job* aux = h;
	printf("job List:\n");
	while (aux) {
		printf("\tjob ID = %d\n", aux->id);
		aux = aux->next;
	}
}
