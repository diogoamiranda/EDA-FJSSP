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

	Job* job1 = CreateJob(0, "plastic cutting");

	Job* headJobList = NULL;
	headJobList = InsertJobEnd(headJobList, job1);

	Operation* op1 = CreateOperation(0, 0, 0, 4, false);
	Operation* op2 = CreateOperation(1, 0,  1, 1, false);
	Operation* op3 = CreateOperation(2, 0, 2, 5, false);

	Operation* headOperationsList = NULL;
	headOperationsList = InsertOperationEnd(headOperationsList, op1);
	headOperationsList = InsertOperationEnd(headOperationsList, op2);
	headOperationsList = InsertOperationEnd(headOperationsList, op3);
#pragma endregion

#pragma region PAHSE1_2
	/*bool b = SaveJobBinary("jobs.bin", headJobList);

	if (b == true) {
		DeleteAllJobs(&headJobList);
		ReadJobBinary = LerJobBinario("jobs.bin");
	}*/

#pragma endregion

#pragma region PAHSE1_3
	Operation* op4 = CreateOperation(4, 0, 5, 5, false);
	headOperationsList = InsertOperationEnd(headOperationsList, op4);

#pragma endregion

#pragma region PAHSE1_4
	headOperationsList = RemoveOperation(headOperationsList, 4);

#pragma endregion

#pragma region PAHSE1_5
	headOperationsList = UpdateOperation(headOperationsList, 3, 0, 6, 5, true);

#pragma endregion

#pragma region PAHSE1_6
	 float time = CalculateMinTimeJob(headJobList, headOperationsList, job1->id);
	 printf("minimum time of %.2f units to finish job %d\n", time, job1->id);

#pragma endregion

#pragma region PAHSE1_7
	time = CalculateMaxTimeJob(job1->id);
	printf("maximum time of %.2f units to finish job %d\n", time, job1->id);

#pragma endregion

#pragma region PAHSE1_8
	time = CalculateAvgTimeJobOperations(job1->id);
	printf("average time of %.2f units to finish any job operation of the job ID %d\n", time, job1->id);

#pragma endregion

	return 0;
}