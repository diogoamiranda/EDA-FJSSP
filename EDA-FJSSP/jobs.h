/**
 * @file jobs.h
 * @author diogo miranda
 * @date 2022
 * @brief Jobs - Definitions of Structs, Constants, and Function Signatures
 *
*/

//prevent double declaration of any identifiers (types, etc)
#ifndef JOBS
#define JOBS

#include <stdio.h>
#include <stdbool.h>
#include "operations.h"

//avoid MSG ERROS: _CRT_SECURE_NO_WARNINGS
#pragma warning( disable : 4996 ) 

#pragma region Constants
#define JOB_NAME_MAX_LENGTH 50
#define LOAD_PROCESS_PLAN_BYTES_TO_READ_BY_LINE 100
#pragma endregion

#pragma region Structs

/**
 * @brief Dynamic structure to store a job
 *
 * A job contains an identifier (@@id), a name (@@name),
 * a boolean to check the state of the job(@@finished) and a pointer(*next).
 */
typedef struct job {
	int id;
	char name[JOB_NAME_MAX_LENGTH];
	bool finished;
	struct Operation* operations; //pointer to the operations list
	struct Job* next; //pointer to the next memory block/node of type Job
} Job;

/**
 * @brief Dynamic structure (BST) to store a job
 *
 * A job contains an identifier (@@id), a name (@@name),
 * a boolean to check the state of the job(@@finished) and a pointer(*next).
 */
typedef struct jobTree {
	int id;
	char name[JOB_NAME_MAX_LENGTH];
	bool finished;
	struct Operation* operations; //pointer to the operations list
	struct JobTree* left; //pointer to the left memory block/node of type Job
	struct JobTree* right;//pointer to the right memory block/node of type Job
} JobTree;

/**
 * @brief Struct to store a job in a file
 *
 * A job contains an identifier (@@id), a name (@@name),
 * a boolean to check the state of the job(@@finished)
 */
typedef struct jobFile {
	int id;
	char name[JOB_NAME_MAX_LENGTH];
	bool finished;
}JobFile;

#pragma endregion

#pragma region FunctionSignatures

// creates a new job(allocates memory)
Job* CreateJob(int id, char* name);
JobTree* CreateJobTree(int id, char* name);

// inserts job at the end of the job list
Job* InsertJobEnd(Job* h, Job* n);
JobTree* InsertJobTree(JobTree* root, JobTree* n);

// inserts new operations for a job at the beginning of the list
Job* InsertJobOperationStart(Job* h, int jobId, int opId, int opType, int machId, int time, bool finished);
JobTree* InsertJobOperationTree(JobTree* root, int jobId, int opId, int opType, int machId, int time, bool finished);

// calculates the min time a job takes to complete
float CalculateMinTimeJob(Job* h, int jobId);

// calculates the max time a job takes to complete
float CalculateMaxTimeJob(Job* h, int jobId);

// calculates average amount of time required to complete a job operation
void ShowAvgTimeJobOperations(Job* h, int jobId);

// writes job data to file
bool SaveJobBinary(char* fileName, Job* h);

// reads file with data from a job
Job* ReadJobBinary(char* fileName);

// reads jobs, operations and machines from a file
Job* LoadProcessPlan(char* fileName);
JobTree* LoadProcessPlanTree(char* fileName);

// removes all nodes from the job list
void RemoveAllJobs(Job** h);

// removes job from the job list
Job* RemoveJob(Job* h, int jobId);

// removes job from the job tree
JobTree* RemoveJobTree(JobTree* h, int jobId);

// removes job operation
void RemoveJobOperation(Job* h, int jobId, int opId);
void RemoveJobOperationTree(JobTree* root, int jobId, int opId);

// updates job operation
Job* UpdateJobOperation(Job* h, int jobId, int opId, int opType, int opMachId, int opTime, bool opFinished);

// checks if job exists 
bool JobExist(Job* h, int id);
bool JobExistTree(JobTree* root, int id);

void ShowJobOperations(Job* h, int jobId);

void ShowJobs(Job* h);

void ShowJobsTreeInOrder(JobTree* root);
#pragma endregion


#endif

