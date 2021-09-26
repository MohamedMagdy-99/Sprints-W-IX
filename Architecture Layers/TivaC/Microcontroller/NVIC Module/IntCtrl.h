/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <IntCtrl.h>
 *       Module:  NVIC
 *
 *  Description:  Header File For NVIC Module     
 *  
 *********************************************************************************************************************/
#ifndef INTCTRL_H
#define INTCTRL_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/
#include "Std_Types.h"
#include "IntCtrl_Cfg.h"
#include "TM4C123GH6PM.h"
/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
#define ALL_MCU_INTERRUPTS          (0xFFU)

/**********************************************************************************************************************
 *  GLOBAL FUNCTION MACROS
 *********************************************************************************************************************/


/**********************************************************************************************************************
 *  GLOBAL DATA TYPES AND STRUCTURES
 *********************************************************************************************************************/
typedef uint32 IntCtr_GrpPrio_t;
typedef uint32 IntCtr_SubGrpPrio_t;
typedef uint32 IntCtr_Prio_t;
typedef uint32 IntCtr_GrpPrioSys_t;

typedef struct
{
    IRQn_Type           IRQ_Number; 
    IntCtr_GrpPrio_t    GrpPrio;
    IntCtr_SubGrpPrio_t SubGrpPrio;

}strIntCtrl_Config_t;

/**********************************************************************************************************************
 *  GLOBAL DATA PROTOTYPES
 *********************************************************************************************************************/
extern strIntCtrl_Config_t IntCtrl_Config[NUM_USED_INT];
 
/**********************************************************************************************************************
 *  GLOBAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
/******************************************************************************
* \Syntax          : Std_ReturnType IntCrtl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : None
*******************************************************************************/
Std_ReturnType IntCrtl_Init(void);
/************************************************************************************************
* \Syntax          : Std_ReturnType IntCrtl_EnableIRQ                                     
* \Description     : Enable Interrupts in NVIC                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : IRQn_Type IRQ_Number                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOK
***********************************************************************************************/
Std_ReturnType IntCrtl_EnableIRQ(IRQn_Type IRQ_Number);

/************************************************************************************************
* \Syntax          : Std_ReturnType IntCrtl_DisableIRQ                                     
* \Description     : Disable Interrupts in NVIC                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : IRQn_Type IRQ_Number                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOK
***********************************************************************************************/
Std_ReturnType IntCrtl_DisableIRQ(IRQn_Type IRQ_Number);

/************************************************************************************************
* \Syntax          : Std_ReturnType IntCtrl_EnableGlobalInterrupts                                    
* \Description     : Enables Global Interrupts                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                    
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOK
***********************************************************************************************/
Std_ReturnType IntCtrl_EnableGlobalInterrupts(void);

/************************************************************************************************
* \Syntax          : Std_ReturnType IntCtrl_DisableGlobalInterrupts                                     
* \Description     : Disable Global Interrupts                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOK
***********************************************************************************************/
Std_ReturnType IntCtrl_DisableGlobalInterrupts(void);

#endif  /* INTCTRL_H */

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl.h
 *********************************************************************************************************************/
