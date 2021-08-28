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
/* array of that saves the tasks data when created */
strTasksCreationData_t Tasks[MAX_NUM_TASKS];

/* array to save tasks Ids so we can get the task array index */
TaskId_t Tasks_Ids[MAX_NUM_TASKS];

/* array to save tasks priors so we can get the task array index */
TaskPriority_t Tasks_Priority[MAX_NUM_TASKS];

/* variable to save and update sys ticks */
OS_SysTicks_t Sys_CurrentTime = Initial_Value;

/* variable to hold the number of created tasks */
CreatedTasksCount_t CreatedTasksCount = Initial_Value;

/* a flag to indicate a sys tick has occurred */
OS_NewTickFlag_t OS_NewTickFlag = TRUE;

/* variable to hold tasks current state */
TaskState_t TasksCurrentState[MAX_NUM_TASKS];
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
	OS_Init();
	
	OS_Scheduler();
	
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: initializes the OS
******************************************************************************************/
Std_ReturnType OS_Init(void)
{
	GptStart_aSync(TIMER_CHANNEL_0_ID, OS_BASE_SYSTICKS_TIMERTICKS, OS_CallBack);
	
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: starts the OS
******************************************************************************************/
Std_ReturnType OS_Scheduler(void)
{

	while(TRUE)
	{
		if(OS_NewTickFlag == TRUE)
		{
			/* if a task is already running now, leave the if condition */
			if(OS_checkIfTaskRunning() == TRUE)
			{
				/* a task is already running we have to wait */
				/* reset tick flag */
				OS_NewTickFlag = FALSE;
			}
			else
			{
				/* check if it's the initial sys tick (0) which means all tasks are ready */
				if(Sys_CurrentTime == Initial_Value)
				{
					/* compare priority */
					
					/* run the winner task */
					
					/* reset tick flag */
					OS_NewTickFlag = FALSE;
				}
				else
				{
					/* else compare current sys ticks with tasks periodicity to know which tasks can run now */
					
					/* compare the priority of nominated tasks */
					
					/* run the winner task */
					
					/* reset tick flag */
					OS_NewTickFlag = FALSE;

				}
						
			}

		}
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
	/* update sys tick */
	Sys_CurrentTime++;
	
	/* update new tick flag */
	OS_NewTickFlag = TRUE;
	
	/* restart the timer */
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
	if(CreatedTasksCount >= MAX_NUM_TASKS)
	{
		return E_NOT_OK;
	}
	/* store task data in array */
	Tasks[TaskToBeStoredIndex].Id = Id;
	Tasks[TaskToBeStoredIndex].Parameters = Parameters;
	Tasks[TaskToBeStoredIndex].Periodicity = Periodicity;
	Tasks[TaskToBeStoredIndex].Priority = Priority;
	Tasks[TaskToBeStoredIndex].TaskPointer = TaskPointer;
	/* set initial state */
	TasksCurrentState[TaskToBeStoredIndex] = READY;
	/* store task index using its id */
	Tasks_Ids[TaskToBeStoredIndex] = Id;
	/* store task index using its prio */
	Tasks_Priority[TaskToBeStoredIndex] = Priority;
	/* increment index and tasks count */
	TaskToBeStoredIndex++;
	CreatedTasksCount++;
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
* Description: suspends a certain task from being scheduled
******************************************************************************************/
Std_ReturnType OS_TaskSuspend(TaskId_t Id)
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

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: starts the OS
******************************************************************************************/
boolean OS_checkIfTaskRunning(void)
{
	uint8_t u8_loopCounter = Initial_Value;
	for(u8_loopCounter = Initial_Value; u8_loopCounter < CreatedTasksCount; u8_loopCounter++)
	{
		if(TasksCurrentState[u8_loopCounter] == RUNNING)
		{
			return TRUE;
		}
	}
	return FALSE;
}