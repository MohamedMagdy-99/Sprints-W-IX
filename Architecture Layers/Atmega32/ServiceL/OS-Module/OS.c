/*****************************************************************************
* Module: OS Module
* File Name: OS.c
* Description: Source file for OS Module
* Author: Mohamed Magdy
* Date: 28-Aug-2021
******************************************************************************/
/*- INCLUDES
----------------------------------------------*/
#include "OS.h"

/*- GLOBAL EXTERN VARIABLES
-------------------------------*/
strTasksCreationData_t Tasks[MAX_NUM_TASKS];

TaskIndex_t Tasks_Index[MAX_NUM_TASKS];

OS_SysTicks_t Sys_CurrentTime = Initial_Value;
/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: starts the OS
******************************************************************************************/
Std_ReturnType OS_Start(void)
{
	GptStart_aSync(TIMER_CHANNEL_0_ID, OS_BASE_SYSTICKS_TIMERTICKS, OS_CallBack);
	
	while(TRUE)
	{
		
	}	
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: call back function to update OS SysTicks each ISR
******************************************************************************************/
void OS_CallBack(void)
{
	Sys_CurrentTime++;
	GptStart_aSync(TIMER_CHANNEL_0_ID, OS_BASE_SYSTICKS_TIMERTICKS, OS_CallBack);
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: creates a Task to be added to the system queue.
******************************************************************************************/
Std_ReturnType OS_TaskCreate(TaskId_t Id, TaskPriority_t Priority, TaskPeriodicityTicks_t Periodicity,
							 ptrTask_t TaskPointer, TaskParameters_t Parameters)
{

	STATIC TaskIndex_t TaskToBeStoredIndex = Initial_Value;
	/* check if new task exceeds the max tasks allowed */
	if(TaskToBeStoredIndex > MAX_NUM_TASKS-1)
	{
		return E_NOT_OK;
	}
	/* store task data in array */
	Tasks[TaskToBeStoredIndex].Id = Id;
	Tasks[TaskToBeStoredIndex].Parameters = Parameters;
	Tasks[TaskToBeStoredIndex].Periodicity = Periodicity;
	Tasks[TaskToBeStoredIndex].Priority = Priority;
	Tasks[TaskToBeStoredIndex].TaskPointer = TaskPointer;
	/* store task index using its id */
	Tasks_Index[TaskToBeStoredIndex] = Id;
	/* increment index */
	TaskToBeStoredIndex++;
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: gets index of task in the tasks' array using its Id
******************************************************************************************/
Std_ReturnType OS_GetTaskIndex(TaskId_t Id, TaskIndex_t* TaskIndex)
{

	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: locks a certain task from being scheduled
******************************************************************************************/
Std_ReturnType OS_TaskLock(TaskId_t Id)
{
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: unlocks a certain task from being scheduled
******************************************************************************************/
Std_ReturnType OS_TaskResume(TaskId_t Id)
{
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: changes a certain task's priority
******************************************************************************************/
Std_ReturnType OS_SetPriority(TaskId_t Id)
{
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: changes a certain task's periodicity
******************************************************************************************/
Std_ReturnType OS_SetPeriodicity(TaskId_t Id)
{
	return E_OK;
}

