/**********************************************************************************************************************
 *  FILE DESCRIPTION
 *  -----------------------------------------------------------------------------------------------------------------*/
/**        \file  IntCtrl.c
 *        \brief  Nested Vector Interrupt Controller Driver
 *
 *      \details  The Driver Configure All MCU interrupts Priority into gorups and subgroups
 *                Enable NVIC Interrupt Gate for Peripherals
 *
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  INCLUDES
 *********************************************************************************************************************/
#include "IntCtrl.h"
/**********************************************************************************************************************
*  LOCAL MACROS CONSTANT\FUNCTION
*********************************************************************************************************************/	
#define VECTKEY_Pos              (16U)                                           /*!< SCB AIRCR: VECTKEY Position */
#define VECTKEY_Msk              (0xFFFFUL << VECTKEY_Pos)                       /*!< SCB AIRCR: VECTKEY Mask */
 
#define PRIGROUP_Pos             (8U)                                            /*!< SCB AIRCR: PRIGROUP Position */
#define PRIGROUP_Msk             (7UL << PRIGROUP_Pos)                           /*!< SCB AIRCR: PRIGROUP Mask */

#define IRQn_MIN                 (0u)
#define IRQn_MAX                 (138u)
/**********************************************************************************************************************
 *  LOCAL DATA 
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL DATA
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  LOCAL FUNCTION PROTOTYPES
 *********************************************************************************************************************/
STATIC Std_ReturnType IntCtrl_SetPriority(IRQn_Type IRQ_Number, IntCtr_GrpPrio_t GrpPrio, IntCtr_SubGrpPrio_t SubGrpPrio);
STATIC Std_ReturnType IntCtrl_SetPrioritySystem(IntCtr_GrpPrioSys_t PrioSystem);
/**********************************************************************************************************************
 *  LOCAL FUNCTIONS
 *********************************************************************************************************************/
/************************************************************************************************
* \Syntax          : Std_ReturnType IntCtrl_EnableIRQ                                     
* \Description     : Enable Interrupts of a certian peripheral in NVIC                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : IRQn_Type IRQ_Number                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOK
***********************************************************************************************/
Std_ReturnType IntCtrl_EnableIRQ(IRQn_Type IRQ_Number)
{

  if(IRQ_Number == ALL_MCU_INTERRUPTS)
  {
    uint8 u8_loopCounter = INITIAL_VALUE;
    for(u8_loopCounter = INITIAL_VALUE; u8_loopCounter <= IRQn_MAX; u8_loopCounter++)
    {
      NVIC->ISER[(((uint32)(sint32)u8_loopCounter) >> 5UL)] = (uint32)(1UL << (((uint32)(sint32)u8_loopCounter) & 0x1FUL));
    }
  }
  else if((sint32)(IRQ_Number) >= 0 && IRQ_Number != ALL_MCU_INTERRUPTS)
  {
    NVIC->ISER[(((uint32)(sint32)IRQ_Number) >> 5UL)] = (uint32)(1UL << (((uint32)(sint32)IRQ_Number) & 0x1FUL));
  }
  else
  {
    return E_NOT_OK;
  }
    return E_OK;
}

/************************************************************************************************
* \Syntax          : Std_ReturnType IntCtrl_EnableIRQ                                     
* \Description     : Disable Interrupts in NVIC                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : IRQn_Type IRQ_Number                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOK
***********************************************************************************************/
Std_ReturnType IntCtrl_DisableIRQ(IRQn_Type IRQ_Number)
{

  if(IRQ_Number == ALL_MCU_INTERRUPTS)
  {
    uint8 u8_loopCounter = INITIAL_VALUE;
    for(u8_loopCounter = INITIAL_VALUE; u8_loopCounter <= IRQn_MAX; u8_loopCounter++)
    {
       NVIC->ICER[(((uint32)(sint32)u8_loopCounter) >> 5UL)] = (uint32)(1UL << (((uint32)(sint32)u8_loopCounter) & 0x1FUL));
    }
  }
  else if((sint32)(IRQ_Number) >= 0 && IRQ_Number != ALL_MCU_INTERRUPTS)
  {
     NVIC->ICER[(((uint32)(sint32)IRQ_Number) >> 5UL)] = (uint32)(1UL << (((uint32)(sint32)IRQ_Number) & 0x1FUL));
  }
  else
  {
    return E_NOT_OK;
  }
  return E_OK;
}
/************************************************************************************************
* \Syntax          : Std_ReturnType IntCtrl_SetPriority                                     
* \Description     : Assign Group\Subgroup priority in NVIC_PRIx Nvic and SCB_SYSPRIx Registers                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : IntCtr_GrpPrio_t GrpPrio, IntCtr_SubGrpPrio_t SubGrpPrio                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOK
***********************************************************************************************/
STATIC Std_ReturnType IntCtrl_SetPriority(IRQn_Type IRQ_Number, IntCtr_GrpPrio_t GrpPrio, IntCtr_SubGrpPrio_t SubGrpPrio)
{
    IntCtr_Prio_t Priority;

    switch(PRIORITY_SYSTEM)
    {
        case(PRIOGRPS_8_SUBPRIOS_1):
        {
            Priority = GrpPrio;
            break;
        }
        case(PRIOGRPS_4_SUBPRIOS_2):
        {
            Priority = ((GrpPrio << 1) | SubGrpPrio);
            break;
        }
        case(PRIOGRPS_2_SUBPRIOS_4):
        {
            Priority = ((GrpPrio << 2) | SubGrpPrio);
            break;
        }
        case(PRIOGRPS_1_SUBPRIOS_8):
        {
            Priority = SubGrpPrio;
            break;
        }
        default:
        {
            break;
        }                        
    }

   if ((sint32)(IRQ_Number) >= IRQn_MIN && (sint32)(IRQ_Number) <= IRQn_MAX)
   {
     NVIC->IP[IRQ_Number] = (uint8)((Priority << 3U) & (uint32)0xFFUL);
   }
   else
   {
     return E_NOT_OK;
   }
	
    return E_OK;
}

/***************************************************************************************
* \Syntax          : Std_ReturnType IntCtrl_SetPrioritySystem                                      
* \Description     : Configure Grouping\SubGrouping System in APINT register in SCB                                   
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : IntCtr_GrpPrioSys_t PrioSystem                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOK
****************************************************************************************/
STATIC Std_ReturnType IntCtrl_SetPrioritySystem(IntCtr_GrpPrioSys_t PrioSystem)
{
    uint32 u32_regValue;

    IntCtr_GrpPrioSys_t PriorityGroupTmp = (PrioSystem & (uint32_t)0x07UL);        /* only values 0..7 are used (guard)  */

    u32_regValue  =  SCB->AIRCR;                                                   /* read old register configuration    */

    u32_regValue &= ~((uint32)(VECTKEY_Msk | PRIGROUP_Msk));                       /* clear bits to change               */
    
    u32_regValue  =  (u32_regValue                         |
                     ((uint32)0x5FAUL << VECTKEY_Pos)      |
                     (PriorityGroupTmp << PRIGROUP_Pos)     );                     /* Insert write key and priorty group */

    SCB->AIRCR =  u32_regValue;
    return E_OK;  
}
/**********************************************************************************************************************
 *  GLOBAL FUNCTIONS
 *********************************************************************************************************************/


/******************************************************************************
* \Syntax          : Std_ReturnType IntCtrl_Init(void)                                      
* \Description     : initialize Nvic\SCB Module by parsing the Configuration 
*                    into Nvic\SCB registers                                    
*                                                                             
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOK
*******************************************************************************/
Std_ReturnType IntCtrl_Init(void)
{
    uint8 u8_loopCounter = INITIAL_VALUE;
	/*Configure Grouping\SubGrouping System in APINT register in SCB*/
    IntCtrl_SetPrioritySystem(PRIORITY_SYSTEM);

    /*Assign Group\Subgroup priority in NVIC_PRIx Nvic and SCB_SYSPRIx Registers*/  
    for(u8_loopCounter = INITIAL_VALUE; u8_loopCounter < NUM_USED_INT; u8_loopCounter++)
    {
      IntCtrl_SetPriority(IntCtrl_Config[u8_loopCounter].IRQ_Number, IntCtrl_Config[u8_loopCounter].GrpPrio, 
                          IntCtrl_Config[u8_loopCounter].SubGrpPrio);  
    }

	/*Enable\Disable based on user configurations in NVIC_ENx and SCB_Sys Registers */
    for(u8_loopCounter = INITIAL_VALUE; u8_loopCounter < NUM_USED_INT; u8_loopCounter++)
    {
      IntCtrl_EnableIRQ(IntCtrl_Config[u8_loopCounter].IRQ_Number);  
    }

	
    return E_OK;
}

/************************************************************************************************
* \Syntax          : Std_ReturnType IntCtrl_EnableGlobalInterrupts                                    
* \Description     : Enables Global Interrupts                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                    
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOK
***********************************************************************************************/
Std_ReturnType IntCtrl_EnableGlobalInterrupts(void)
{
  Enable_GlobalInterrupts();
  return E_OK;
}

/************************************************************************************************
* \Syntax          : Std_ReturnType IntCtrl_DisableGlobalInterrupts                                     
* \Description     : Disable Global Interrupts                                                                                    
* \Sync\Async      : Synchronous                                               
* \Reentrancy      : Non Reentrant                                             
* \Parameters (in) : None                     
* \Parameters (out): None                                                      
* \Return value:   : E_OK or E_NOK
***********************************************************************************************/
Std_ReturnType IntCtrl_DisableGlobalInterrupts(void)
{
  Disable_GlobalInterrupts();
  return E_OK;
}
/**********************************************************************************************************************
 *  END OF FILE: IntCtrl.c
 *********************************************************************************************************************/
