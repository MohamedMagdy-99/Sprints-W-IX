/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  CPU.c
 *        \brief  CPU Driver
 *
 *      \details  The Driver Configure CPU Configurations and Modes.
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "CPU.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/
#define CPU_PRIVILEGE           (0x00U)
#define CPU_NONPRIVILEGE        (0x01U)
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/
CPU_State_t CPU_State = CPU_PRIVILEGE;

/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/******************************************************************************
* \Syntax          : Std_ReturnType Cpu_EnterNonPrivilege(void)                                    
* \Description     : Makes Cpu Enter Privilege Mode.                                                                                            
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOT_OK
*******************************************************************************/
Std_ReturnType Cpu_EnterNonPrivilege(void)
{
    CPU_State = CPU_NONPRIVILEGE;
    SVCall_Pend();

    return E_OK;
}

/******************************************************************************
* \Syntax          : Std_ReturnType Cpu_EnterPrivilege(void)                                    
* \Description     : Makes Cpu Enter NonPrivilege Mode.                                                                                                      
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                    
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOT_OK
*******************************************************************************/
Std_ReturnType Cpu_EnterPrivilege(void)
{
   CPU_State = CPU_PRIVILEGE;
   SVCall_Pend();

   return E_OK;
}


/******************************************************************************
* \Syntax          : void SVC_Handler(void)                                
* \Description     : SVC ISR                                                                                                 
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
void SVC_Handler(void)
{
    if(CPU_State == CPU_PRIVILEGE)
    {
        Switch_CPU_Privileged();
    }
    else if(CPU_State == CPU_NONPRIVILEGE)
    {
        Switch_CPU_Unprivileged();
    }
    else
    {

    }
}
/**********************************************************************************************************************
 *  END OF FILE: CPU.c
 *********************************************************************************************************************/
