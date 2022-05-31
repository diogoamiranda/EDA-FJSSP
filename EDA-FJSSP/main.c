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
	Operation* op2 = CreateOperation(NULL, 1, 0,  1, 1, false);
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

	Operation* headJobOperationsList = NULL;
	headJobOperationsList = InsertJobOperationEnd(headJobList, 0, 0, 1, 1, 4, false);
	headJobOperationsList = InsertJobOperationEnd(headJobList, 0, 1, 1, 3, 5, false);
	headJobOperationsList = InsertJobOperationEnd(headJobList, 0, 2, 2, 2, 4, false);
	headJobOperationsList = InsertJobOperationEnd(headJobList, 0, 3, 2, 4, 5, false);
#pragma endregion

#pragma region PAHSE1_2
	/*bool b = SaveJobBinary("jobs.bin", headJobList);

	if (b == true) {
		DeleteAllJobs(&headJobList);
		ReadJobBinary = LerJobBinario("jobs.bin");
	}*/

#pragma endregion

#pragma region PAHSE1_3
	Operation* op4 = CreateOperation(NULL, 4, 4, 5, 5, false);
	headOperationsList = InsertOperationEnd(headOperationsList, op4);

#pragma endregion

#pragma region PAHSE1_4
	headOperationsList = RemoveOperation(headOperationsList, 4);

#pragma endregion

#pragma region PAHSE1_5
	headOperationsList = UpdateOperation(headOperationsList, 0, 4, 0, 6, 5, true);

#pragma endregion

#pragma region PAHSE1_6
	printf("**** Job Stats - Minimum time to finish job ****");
	float time = CalculateMinTimeJob(headJobList, job1->id);
	printf("minimum time of %.2f units to finish job %d\n\n", time, job1->id);

#pragma endregion

#pragma region PAHSE1_7
	printf("**** Job Stats - Maximum time to finish job ****");
	time = CalculateMaxTimeJob(headJobList, job1->id);
	printf("maximum time of %.2f units to finish job %d\n\n", time, job1->id);

#pragma endregion

#pragma region PAHSE1_8
	printf("**** Job Stats - AVG time to finish operation job ****");
	ShowAvgTimeJobOperations(headJobList, job1->id);

#pragma endregion

	return 0;
}