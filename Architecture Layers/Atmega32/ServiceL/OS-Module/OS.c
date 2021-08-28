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

/* a flag to indicate that a task will run */
OS_TaskWillRunFlag_t OS_TaskWillRunFlag = FALSE;

/* variable to hold tasks current state */
TaskState_t TasksCurrentState[MAX_NUM_TASKS];

/* currently running taks index */
TaskIndex_t CurrentlyRunningTaskIndex = Initial_Value;

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
	/* initialize tasks states to suspended until they are created */
	uint8_t u8_loopCounter = Initial_Value;
	
	for(u8_loopCounter = Initial_Value; u8_loopCounter < MAX_NUM_TASKS; u8_loopCounter++)
	{
		TasksCurrentState[u8_loopCounter] = SUSPENDED;
	}

	/* start timer for first time */
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
					CurrentlyRunningTaskIndex = ReturnIndexOfSmallestElement(Tasks_Priority, CreatedTasksCount);
					/* run the winner task */
					Tasks[CurrentlyRunningTaskIndex].TaskPointer(Tasks[CurrentlyRunningTaskIndex].Parameters);
					/* block all the task */
					OS_setTaskState(ALL_TASKS, BLOCKED);
					/* reset tick flag */
					OS_NewTickFlag = FALSE;
				}
				else
				{
					/* else compare current sys ticks with tasks periodicity to know which tasks can run now and make them ready */
					uint8_t u8_loopCounter = Initial_Value;
					for(u8_loopCounter = Initial_Value; u8_loopCounter < CreatedTasksCount; u8_loopCounter++)
					{
						if(((Sys_CurrentTime % (Tasks[u8_loopCounter].Periodicity)) == 0) && TasksCurrentState[u8_loopCounter] != SUSPENDED)
						{
							/* set its state to ready */
							OS_setTaskState(Tasks_Ids[u8_loopCounter], READY);
							/* set task will run flag */
							OS_TaskWillRunFlag = TRUE;
						}
					}
					/* if any task is confirmed to run in this sys tick */
					if(OS_TaskWillRunFlag == TRUE)
					{
						/* compare the priority of nominated tasks */
						uint8_t maxPrioirtyTemp = MAX_PRIOIRTY;
						for(u8_loopCounter = Initial_Value; u8_loopCounter < CreatedTasksCount; u8_loopCounter++)
						{
							if(TasksCurrentState[u8_loopCounter] == READY)
							{
								if(Tasks_Priority[u8_loopCounter] <= maxPrioirtyTemp)
								{
									/* update new max prio */
									maxPrioirtyTemp = Tasks_Priority[u8_loopCounter];
									/* update current task index to be running */
									CurrentlyRunningTaskIndex = u8_loopCounter;
								}
							}
						}
						/* set state of winner task to running */
						OS_setTaskState(Tasks_Ids[CurrentlyRunningTaskIndex], RUNNING);
						/* run the winner task */
						Tasks[CurrentlyRunningTaskIndex].TaskPointer(Tasks[CurrentlyRunningTaskIndex].Parameters);
						/* block all tasks */
						OS_setTaskState(ALL_TASKS, BLOCKED);
						/* reset tick flag */
						OS_NewTickFlag = FALSE;		
						/* rest task will run flag */
						OS_TaskWillRunFlag = FALSE;				
					}
					else
					{
						/* no task's periodicity matches current sys tick so no tasks will run */
											
						/* reset tick flag */
						OS_NewTickFlag = FALSE;
					}
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
/*	Tasks[TaskToBeStoredIndex].Id = Id;*/
	Tasks[TaskToBeStoredIndex].Parameters = Parameters;
	Tasks[TaskToBeStoredIndex].Periodicity = Periodicity;
/*	Tasks[TaskToBeStoredIndex].Priority = Priority;*/
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
Std_ReturnType OS_GetTaskIndex_Id(TaskId_t Id, TaskIndex_t* TaskIndex)
{
		
	uint8_t u8_loopCounter = Initial_Value;
	
	for(u8_loopCounter = Initial_Value; u8_loopCounter < CreatedTasksCount; u8_loopCounter++)
	{
		if(Tasks_Ids[u8_loopCounter] == Id)
		{
			*TaskIndex =  u8_loopCounter;
			return E_OK;
		}
	}
	/* task id not found */
	*TaskIndex = 0xFF;
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: gets index of task in the tasks' array using its Priority
******************************************************************************************/
Std_ReturnType OS_GetTaskIndex_Prio(TaskPriority_t Priority, TaskIndex_t* TaskIndex)
{
	
	uint8_t u8_loopCounter = Initial_Value;
	
	for(u8_loopCounter = Initial_Value; u8_loopCounter < CreatedTasksCount; u8_loopCounter++)
	{
		if(Tasks_Priority[u8_loopCounter] == Priority)
		{
			*TaskIndex =  u8_loopCounter;
			return E_OK;
		}
	}
	/* task id not found */
	*TaskIndex = 0xFF;
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
		TaskIndex_t TaskIndex = Initial_Value;
		/* get the task's index */
		OS_GetTaskIndex_Id(Id, &TaskIndex);
		/* change the state */
		TasksCurrentState[TaskIndex] = SUSPENDED;	
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
	TaskIndex_t TaskIndex = Initial_Value;
	/* get the task's index */
	OS_GetTaskIndex_Id(Id, &TaskIndex);
	/* change the state */
	TasksCurrentState[TaskIndex] = BLOCKED;	
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: changes a certain task's priority
******************************************************************************************/
Std_ReturnType OS_SetPriority(TaskId_t Id, TaskPriority_t Priority)
{
	TaskIndex_t TaskIndex = Initial_Value;
	/* get the task's index */
	OS_GetTaskIndex_Id(Id, &TaskIndex);
	/* change the Priority */
	Tasks[TaskIndex].Periodicity = Priority;	
	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: changes a certain task's periodicity
******************************************************************************************/
Std_ReturnType OS_SetPeriodicity(TaskId_t Id, TaskPeriodicityTicks_t Periodicity)
{
	TaskIndex_t TaskIndex = Initial_Value;
	/* get the task's index */
	OS_GetTaskIndex_Id(Id, &TaskIndex);
	/* change the periodicity */
	Tasks[TaskIndex].Periodicity = Periodicity;
	
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

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: changes a task's state or all tasks
******************************************************************************************/
Std_ReturnType OS_setTaskState(TaskId_t Id, TaskState_t TaskState)
{
	
	uint8_t u8_loopCounter = Initial_Value;
	
	
	if(Id == ALL_TASKS)
	{
		for(u8_loopCounter = Initial_Value; u8_loopCounter < MAX_NUM_TASKS; u8_loopCounter++)
		{
			/* check if a task is suspended don't change it */
			if(TasksCurrentState[u8_loopCounter] == SUSPENDED)
			{
				/* ignore */
				return E_NOT_OK;
			}
			else
			{
				TasksCurrentState[u8_loopCounter] = TaskState;
			}
			
		}	
	}
	else
	{
		/* check if a task is suspended ignore the call */
		if(TasksCurrentState[u8_loopCounter] == SUSPENDED)
		{
			/* ignore */
			return E_NOT_OK;
		}
		else
		{
			TaskIndex_t TaskIndex = Initial_Value;
			/* get the task's index */
			OS_GetTaskIndex_Id(Id, &TaskIndex);
			/* change the state */
			TasksCurrentState[TaskIndex] = TaskState;
		}

	}

	return E_OK;
}

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: gets the current system tick
******************************************************************************************/
Std_ReturnType OS_getCurrentSysTick(OS_SysTicks_t* Sys_CurrentTick)
{
	*Sys_CurrentTick = Sys_CurrentTime;
	return E_OK;
}