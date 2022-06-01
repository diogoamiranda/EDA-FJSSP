/**
 * @file main.c
 * @author diogo miranda
 * @date 2022
 * @brief Instantiation and manipulation of the various lists
*/

#include <stdio.h>
#include "jobs.h"
#include "operations.h"
#include "machines.h"

/**
* Main function (main thread)
*/
int main() {

#pragma region PAHSE1_CRIAR_LISTAS
	Machine* m1 = CreateMachine(0, true);
	Machine* m2 = CreateMachine(1, true);
	Machine* m3 = CreateMachine(2, true);

	Machine* headMachList = NULL;
	headMachList = InsertMachineEnd(headMachList, m1);
	headMachList = InsertMachineEnd(headMachList, m2);
	headMachList = InsertMachineEnd(headMachList, m3);

	Operation* op1 = CreateOperation(NULL, 0, 0, 0, 4, false);
	Operation* op2 = CreateOperation(NULL, 1, 0, 1, 1, false);
	Operation* op3 = CreateOperation(NULL, 2, 0, 2, 5, false);

	//Phase 1 list
	Operation* headOperationsList = NULL;
	headOperationsList = InsertOperationEnd(headOperationsList, op1);
	headOperationsList = InsertOperationEnd(headOperationsList, op2);
	headOperationsList = InsertOperationEnd(headOperationsList, op3);

	Job* job1 = CreateJob(0, "plastic cutting");
	Job* job2 = CreateJob(1, "paint");

	Job* headJobList = NULL;
	headJobList = InsertJobEnd(headJobList, job1);
	headJobList = InsertJobEnd(headJobList, job2);

	headJobList = InsertJobOperationEnd(headJobList, 0, 0, 1, 1, 4, false);
	headJobList = InsertJobOperationEnd(headJobList, 0, 1, 1, 3, 5, false);
	headJobList = InsertJobOperationEnd(headJobList, 0, 2, 2, 2, 4, false);
	headJobList = InsertJobOperationEnd(headJobList, 0, 3, 2, 4, 5, false);
#pragma endregion

#pragma region PHASE1
#pragma region ex2
	/*bool b = SaveJobBinary("jobs.bin", headJobList);

	if (b == true) {
		RemoveAllJobs(&headJobList);
		ReadJobBinary = ReadJobBinary("jobs.bin");
	}*/

#pragma endregion

#pragma region ex3
	Operation* op4 = CreateOperation(NULL, 4, 4, 5, 5, false);
	headOperationsList = InsertOperationEnd(headOperationsList, op4);

#pragma endregion

#pragma region ex4
	headOperationsList = RemoveOperation(headOperationsList, 4);

#pragma endregion

#pragma region ex5
	headOperationsList = UpdateOperation(headOperationsList, 0, 4, 0, 6, 5, true);

#pragma endregion

#pragma region ex6
	printf("**** Job Stats - Minimum time to finish job ****");
	float time = CalculateMinTimeJob(headJobList, job1->id);
	printf("minimum time of %.2f units to finish job %d\n\n", time, job1->id);

#pragma endregion

#pragma region ex7
	printf("**** Job Stats - Maximum time to finish job ****");
	time = CalculateMaxTimeJob(headJobList, job1->id);
	printf("maximum time of %.2f units to finish job %d\n\n", time, job1->id);

#pragma endregion

#pragma region ex8
	printf("**** Job Stats - AVG time to finish operation job ****");
	ShowAvgTimeJobOperations(headJobList, job1->id);

#pragma endregion

#pragma endregion

#pragma region PHASE2

#pragma region ex3
	Job* job3 = CreateJob(3, "plastic necklace");

	headJobList = InsertJobEnd(headJobList, job3);
#pragma endregion

#pragma region ex4
	printf("\n******Ex. 4 - Phase 2****\n");
	printf("Before remove job\n");
	ShowJobs(headJobList);
	headJobList = RemoveJob(headJobList, job3->id);
	printf("After remove job\n");
	ShowJobs(headJobList);
#pragma endregion

#pragma region ex5
	headJobList = InsertJobOperationEnd(headJobList, 0, 4, 3, 4, 5, false);
#pragma endregion

#pragma region ex6
	RemoveJobOperation(headJobList, 0, 3);
#pragma endregion

#pragma region ex7
	UpdateJobOperation(headJobList, 0, 0, 5, 1, 10, false);
	
#pragma endregion

#pragma endregion

	return 0;
}