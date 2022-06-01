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
 * Creates a new job.
 * Allocates necessary memory to store a JobTee in memory
 * 
 * \param id
 * \param name
 * \return 
 */
JobTree* CreateJobTree(int id, char* name) {
	//allocates a Job in memory
	JobTree* newJob = (JobTree*)malloc(sizeof(JobTree));

	if (newJob == NULL) return NULL;

	newJob->id = id;
	strcpy(newJob->name, name);
	//without operations by default
	newJob->operations = NULL;
	//last node so sets pointer to NULL
	newJob->left = NULL;
	newJob->right = NULL;
	return newJob;
}

/**
* @brief Inserts job into the job tree
* @param root Root of the tree
* @param n New root
* @return Root of the tree
*/
JobTree* InsertJobTree(JobTree* root, JobTree* n) {
	//Check if the new job already exists
	//if (JobExistTree(root, jobId)) return root;	//if it exists, don't insert

	//empty tree?
	if (root == NULL) {
		return CreateJobTree(n->id, n->name);
	}

	if (n->id < root->id) {
		root->left = InsertJobTree(root->left, n);
	}
	else {
		if (n->id > root->id) {
			root->right = InsertJobTree(root->right, n);
		}
	}
	// return node pointer
	return root;
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
 * Loads all the information related to a process plan.
 * Allocate memory and insert into appropriate lists.
 * 
 * \param fileName File name with data about a process plan
 * \return 
 */
Job* LoadProcessPlan(char* fileName) {
	FILE* fp;
	Job* hJob = NULL;
	Operation* hOp = NULL;
	Job* newJob = NULL;
	Operation* newOp = NULL;
	char jobName[JOB_NAME_MAX_LENGTH];
	char strLine[LOAD_PROCESS_PLAN_BYTES_TO_READ_BY_LINE]; // read x bytes at a time;

	if ((fp = fopen(fileName, "r")) == NULL) return NULL;

	Job aux;
	Operation auxOp;
	int currLine = 0;
	while (fgets(strLine, LOAD_PROCESS_PLAN_BYTES_TO_READ_BY_LINE, fp) != NULL){
		// ignore first line
		if (currLine != 0) {
			sscanf(strLine, "%d,%d,%f,%d", &aux.id, &auxOp.type, &auxOp.executionTime, &auxOp.machineId);
			sprintf(jobName, "Job%d", aux.id);//concatenate string and job id
			//avoid unnecessary memory allocation
			if (currLine == 1 || aux.id != hJob->id) {
				newJob = CreateJob(aux.id, jobName);
				hJob = InsertJobEnd(hJob, newJob);
			}
			InsertJobOperationStart(hJob, aux.id, currLine, auxOp.type, auxOp.machineId, auxOp.executionTime, false);
		    //TODO: Add machines
		}

		currLine++;
	}
	fclose(fp);
	return hJob;
}

/**
 * Loads all the information related to a process plan.
 * Allocate memory and insert into appropriate tree.
 *
 * \param fileName File name with data about a process plan
 * \return
 */
JobTree* LoadProcessPlanTree(char* fileName) {
	FILE* fp;
	JobTree* rootJob = NULL;
	Operation* hOp = NULL;
	JobTree* newJob = NULL;
	Operation* newOp = NULL;
	char jobName[JOB_NAME_MAX_LENGTH];
	char strLine[LOAD_PROCESS_PLAN_BYTES_TO_READ_BY_LINE]; // read x bytes at a time;

	if ((fp = fopen(fileName, "r")) == NULL) return NULL;

	JobTree aux;
	Operation auxOp;
	int currLine = 0;
	while (fgets(strLine, LOAD_PROCESS_PLAN_BYTES_TO_READ_BY_LINE, fp) != NULL) {
		// ignore first line
		if (currLine != 0) {
			sscanf(strLine, "%d,%d,%f,%d", &aux.id, &auxOp.type, &auxOp.executionTime, &auxOp.machineId);
			sprintf(jobName, "Job%d", aux.id);//concatenate string and job id
			//avoid unnecessary memory allocation
			if (currLine == 1 || aux.id != rootJob->id) {
				newJob = CreateJobTree(aux.id, jobName);
				rootJob = InsertJobTree(rootJob, newJob);
			}
			//InsertJobOperationStart(rootJob, aux.id, currLine, auxOp.type, auxOp.machineId, auxOp.executionTime, false);
			//TODO: Add machines
		}

		currLine++;
	}
	fclose(fp);
	return rootJob;
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
 * Given a non-empty bst.
 * Return the min jobId(key) found in that tree.
 * 
 * \param root Root of the tree
 * \return 
 */
JobTree* FindMinValueJobTree(JobTree* root) {
	if (root->left == NULL) return root;
	else {
		//recursively find the leftmost leaf
		return(FindMinValueJobTree(root->left));
	}

}

/**
* @brief Removes a specif job from the job tree
* @param h Pointer to the root of the tree
*/
JobTree* RemoveJobTree(JobTree* root, int jobId) {
	if (root == NULL) return NULL;

	// if smaller than the root's key then it is in left subtree
	if(jobId < root->id){
		root->left = RemoveJobTree(root->left, jobId);
	}
	else {
		//if greater than the root's key then it is in right subtree
		if (jobId > root->id) {
			root->right = RemoveJobTree(root->right, jobId);
		}
		//same key as root's key
		else {
			//node with only one child or no child
			if (root->left == NULL) {
				JobTree* aux = root->right;
				Operation* op = root->operations;
				RemoveOperations(op);
				free(root);
				return aux;
			}
			else {
				if (root->right == NULL) {
					JobTree* aux = root->left;
					Operation* op = aux->operations;
					RemoveOperations(op);
					free(root);
					return aux;
				}

				//two children
				//get inorder successor (smallest in the right subtree)
				JobTree* aux = FindMinValueJobTree(root->right);

				//copy the inorder sucessor's content
				root->id = aux->id;

				//delete inorder sucessor (smallest of the right subtree)
				root->right = RemoveJobTree(root->right, aux->id);
			}
		}

		return root;
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
	Job* aux = h;
	while (aux != NULL) {
		if (aux->id == id)
			return true;
		aux = aux->next;
	}
	return false;
}

/**
* @brief Check if a job exists in the job tree.
* @param h Root of the tree
* @param id Identifier to be searched
* @return True/False
*/
bool JobExistTree(JobTree* root, int id) {
	// root is null or key(id) is present at root
	if (root == NULL) return false;

	if (root->id == id) return true;

	// id is greater than root's id
	if (root->id < id) {
		//recursively call right subtree
		return JobExistTree(root->right, id);
	}

	// id is smaller than root's id
	//recursively call left subtree
	return JobExistTree(root->left, id);

	//return false if nothing found
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
	Job* aux = h;
	while (aux != NULL) {
		if (aux->id == id) {
			return (aux);
		}
		aux = aux->next;
	}
	return NULL;
}

/**
* @brief Search for a job in a BST.
* @param h Root of the tree
* @param id Identifier to be searched
* @return Pointer to the copy of founded job
*/
JobTree* SearchJobTree(JobTree* root, int id) {
	// root is null or key(id) is present at root
	if (root == NULL || root->id == id) return root;

	// id is greater than root's id
	if (root->id < id) {
		return SearchJobTree(root->right, id);
	}

	// id is smaller than root's id
	return SearchJobTree(root->left, id);
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

void RemoveJobOperationTree(JobTree* root, int jobId, int opId) {
	JobTree* auxJob = SearchJobTree(root, jobId);
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
 * Insert new operation at the beginning of the list in the operations list of a specific job.
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
Job* InsertJobOperationStart(Job* h, int jobId, int opId, int opType, int machId, int time, bool finished) {
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

/**
 * Insert new operation at the beginning of the list in the operations list of a specific job (Tree version).
 * TODO: CHECK IF OPERATION ALREADY EXISTS BEFORE INSERT
 *
 * \param root Root of job tree
 * \param jobId Job identifier
 * \param opId Operation identifier
 * \param opType Operation type
 * \param machId Machine identifier
 * \param time Operation time
 * \param finished Operation state
 * \return
 */
JobTree* InsertJobOperationTree(JobTree* root, int jobId, int opId, int opType, int machId, int time, bool finished) {
	// if empty job tree
	if (root == NULL) return NULL;
	// search job
	JobTree* aux = SearchJobTree(root, jobId);
	Operation* jobOp = NULL;
	if (aux) {
		jobOp = aux->operations;
		jobOp = CreateOperation(jobOp, opId, opType, machId, time, false);
		aux->operations = jobOp;
	}

	return root;
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
			printf("\toperation id = %d\n", op->id);
			printf("\toperation type = %d\n", op->type);
			printf("\tmachine id = %d\n", op->machineId);
			printf("\texecution time = %.2f\n\n", op->executionTime);
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

/**
 * Function to do inorder traversal of jobs bst.
 * 
 * \param root Root of the tree
 */
void ShowJobsTreeInOrder(JobTree* root) {
	if(root != NULL){
		ShowJobsTreeInOrder(root->left);
		printf("job id: %d; ", root->id);
		ShowJobsTreeInOrder(root->right);
	}
}
