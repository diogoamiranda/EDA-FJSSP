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

// inserts job at the end of the job list
Job* InsertJobEnd(Job* h, Job* n);

// inserts new operations for a job
Operation* InsertJobOperationEnd(Job* h, int jobId, int opId, int opType, int machId, int time, bool finished);

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

// deletes all nodes from the job list
void DeleteAllJobs(Job** h);

// checks if job exists 
bool JobExist(Job* h, int id);

void ShowJobOperations(Job* h, int jobId);

void ShowJobs(Job* h);
#pragma endregion


#endif

