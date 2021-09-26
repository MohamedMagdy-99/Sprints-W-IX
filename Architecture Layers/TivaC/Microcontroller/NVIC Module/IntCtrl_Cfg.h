/**********************************************************************************************************************

 *  FILE DESCRIPTION
 *  -------------------------------------------------------------------------------------------------------------------
 *         File:  <IntCtrl_Cfg.h>
 *       Module:  NVIC
 *
 *  Description:  Header File For Configurations Of NVIC Module     
 *  
 *********************************************************************************************************************/
#ifndef INTCTRL_CFG_H
#define INTCTRL_CFG_H

/**********************************************************************************************************************
 * INCLUDES
 *********************************************************************************************************************/

/**********************************************************************************************************************
 *  GLOBAL CONSTANT MACROS
 *********************************************************************************************************************/
/************************************************************************/
/* Macro states number of used interrupts in system */
#define NUM_USED_INT                    (0x01)
/************************************************************************/

/* These are priority system's options to be chosen from */
#define PRIOGRPS_8_SUBPRIOS_1           (0x00U)
#define PRIOGRPS_4_SUBPRIOS_2           (0x05U)
#define PRIOGRPS_2_SUBPRIOS_4           (0x06U)
#define PRIOGRPS_1_SUBPRIOS_8           (0x07U)

#define DEFAULT_NO_PREMPTION            PRIOGRPS_1_SUBPRIOS_8
#define DEFAULT_WITH_PREMPTION          PRIOGRPS_8_SUBPRIOS_1

/************************************************************************/
/* This macro will be filled with the priority system option */
#define PRIORITY_SYSTEM                 DEFAULT_NO_PREMPTION
/************************************************************************/ 

/* These macros will be used to be filled in the configuration structure to state the grp/sub grp prios */
#define GRP_PRIO_1                      (0x01U)
#define GRP_PRIO_2                      (0x02U)
#define GRP_PRIO_3                      (0x03U)
#define GRP_PRIO_4                      (0x04U)
#define GRP_PRIO_5                      (0x05U)
#define GRP_PRIO_6                      (0x06U)
#define GRP_PRIO_7                      (0x07U)
#define GRP_PRIO_8                      (0x08U)

#define SUBGRP_PRIO_1                   (0x01U)
#define SUBGRP_PRIO_2                   (0x02U)
#define SUBGRP_PRIO_3                   (0x03U)
#define SUBGRP_PRIO_4                   (0x04U)
#define SUBGRP_PRIO_5                   (0x05U)
#define SUBGRP_PRIO_6                   (0x06U)
#define SUBGRP_PRIO_7                   (0x07U)
#define SUBGRP_PRIO_8                   (0x08U)

#endif  /* INTCTRL_CFG_H */

/**********************************************************************************************************************
 *  END OF FILE: IntCtrl_Cfg.h
 *********************************************************************************************************************/
