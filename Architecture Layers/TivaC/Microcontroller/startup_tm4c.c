/* startup code for TM4C MCU */

#include "TM4C123GH6PM.h"

extern uint32_t CSTACK$$Limit;
void __iar_program_start(void);
void Unused_Handler(void);


uint32_t const __vector_table[] @ ".intvec" = {
    (uint32_t)&CSTACK$$Limit,
    (uint32_t)&__iar_program_start,
    (uint32_t)&NMI_Handler,
    (uint32_t)&HardFault_Handler,
    (uint32_t)&MemManage_Handler,
    (uint32_t)&BusFault_Handler,
    (uint32_t)&UsageFault_Handler,
    0,  /* Reserved */
    0,  /* Reserved */
    0,  /* Reserved */
    0,  /* Reserved */
    (uint32_t)&SVC_Handler,
    (uint32_t)&DebugMon_Handler,
    0,  /* Reserved */
    (uint32_t)&PendSV_Handler,
    (uint32_t)&SysTick_Handler,

    /* external uint32_terrupts (IRQs) ... */
    (uint32_t)&GPIOPortA_IRQHandler,    /* GPIO Port A                  */
    (uint32_t)&GPIOPortB_IRQHandler,    /* GPIO Port B                  */
    (uint32_t)&GPIOPortC_IRQHandler,    /* GPIO Port C                  */
    (uint32_t)&GPIOPortD_IRQHandler,    /* GPIO Port D                  */
    (uint32_t)&GPIOPortE_IRQHandler,    /* GPIO Port E                  */
    (uint32_t)&UART0_IRQHandler,        /* UART0 Rx and Tx              */
    (uint32_t)&UART1_IRQHandler,        /* UART1 Rx and Tx              */
    (uint32_t)&SSI0_IRQHandler,         /* SSI0 Rx and Tx               */
    (uint32_t)&I2C0_IRQHandler,         /* I2C0 Master and Slave        */
    (uint32_t)&PWMFault_IRQHandler,     /* PWM Fault                    */
    (uint32_t)&PWMGen0_IRQHandler,      /* PWM Generator 0              */
    (uint32_t)&PWMGen1_IRQHandler,      /* PWM Generator 1              */
    (uint32_t)&PWMGen2_IRQHandler,      /* PWM Generator 2              */
    (uint32_t)&QEI0_IRQHandler,         /* Quadrature Encoder 0         */
    (uint32_t)&ADCSeq0_IRQHandler,      /* ADC Sequence 0               */
    (uint32_t)&ADCSeq1_IRQHandler,      /* ADC Sequence 1               */
    (uint32_t)&ADCSeq2_IRQHandler,      /* ADC Sequence 2               */
    (uint32_t)&ADCSeq3_IRQHandler,      /* ADC Sequence 3               */
    (uint32_t)&Watchdog_IRQHandler,     /* Watchdog timer               */
    (uint32_t)&Timer0A_IRQHandler,      /* Timer 0 subtimer A           */
    (uint32_t)&Timer0B_IRQHandler,      /* Timer 0 subtimer B           */
    (uint32_t)&Timer1A_IRQHandler,      /* Timer 1 subtimer A           */
    (uint32_t)&Timer1B_IRQHandler,      /* Timer 1 subtimer B           */
    (uint32_t)&Timer2A_IRQHandler,      /* Timer 2 subtimer A           */
    (uint32_t)&Timer2B_IRQHandler,      /* Timer 2 subtimer B           */
    (uint32_t)&Comp0_IRQHandler,        /* Analog Comparator 0          */
    (uint32_t)&Comp1_IRQHandler,        /* Analog Comparator 1          */
    (uint32_t)&Comp2_IRQHandler,        /* Analog Comparator 2          */
    (uint32_t)&SysCtrl_IRQHandler,      /* System Control (PLL,OSC,BO)  */
    (uint32_t)&FlashCtrl_IRQHandler,    /* FLASH Control                */
    (uint32_t)&GPIOPortF_IRQHandler,    /* GPIO Port F                  */
    (uint32_t)&GPIOPortG_IRQHandler,    /* GPIO Port G                  */
    (uint32_t)&GPIOPortH_IRQHandler,    /* GPIO Port H                  */
    (uint32_t)&UART2_IRQHandler,        /* UART2 Rx and Tx              */
    (uint32_t)&SSI1_IRQHandler ,        /* SSI1 Rx and Tx               */
    (uint32_t)&Timer3A_IRQHandler,      /* Timer 3 subtimer A           */
    (uint32_t)&Timer3B_IRQHandler,      /* Timer 3 subtimer B           */
    (uint32_t)&I2C1_IRQHandler,         /* I2C1 Master and Slave        */
    (uint32_t)&QEI1_IRQHandler,         /* Quadrature Encoder 1         */
    (uint32_t)&CAN0_IRQHandler,         /* CAN0                         */
    (uint32_t)&CAN1_IRQHandler,         /* CAN1                         */
    (uint32_t)&CAN2_IRQHandler,         /* CAN2                         */
    0,                             /* Reserved                     */
    (uint32_t)&Hibernate_IRQHandler,    /* Hibernate                    */
    (uint32_t)&USB0_IRQHandler,         /* USB0                         */
    (uint32_t)&PWMGen3_IRQHandler,      /* PWM Generator 3              */
    (uint32_t)&uDMAST_IRQHandler,       /* uDMA Software Transfer       */
    (uint32_t)&uDMAError_IRQHandler,    /* uDMA Error                   */
    (uint32_t)&ADC1Seq0_IRQHandler,     /* ADC1 Sequence 0              */
    (uint32_t)&ADC1Seq1_IRQHandler,     /* ADC1 Sequence 1              */
    (uint32_t)&ADC1Seq2_IRQHandler,     /* ADC1 Sequence 2              */
    (uint32_t)&ADC1Seq3_IRQHandler,     /* ADC1 Sequence 3              */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    (uint32_t)&GPIOPortJ_IRQHandler,    /* GPIO Port J                  */
    (uint32_t)&GPIOPortK_IRQHandler,    /* GPIO Port K                  */
    (uint32_t)&GPIOPortL_IRQHandler,    /* GPIO Port L                  */
    (uint32_t)&SSI2_IRQHandler,         /* SSI2 Rx and Tx               */
    (uint32_t)&SSI3_IRQHandler,         /* SSI3 Rx and Tx               */
    (uint32_t)&UART3_IRQHandler,        /* UART3 Rx and Tx              */
    (uint32_t)&UART4_IRQHandler,        /* UART4 Rx and Tx              */
    (uint32_t)&UART5_IRQHandler,        /* UART5 Rx and Tx              */
    (uint32_t)&UART6_IRQHandler,        /* UART6 Rx and Tx              */
    (uint32_t)&UART7_IRQHandler,        /* UART7 Rx and Tx              */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    (uint32_t)&I2C2_IRQHandler,         /* I2C2 Master and Slave        */
    (uint32_t)&I2C3_IRQHandler,         /* I2C3 Master and Slave        */
    (uint32_t)&Timer4A_IRQHandler,      /* Timer 4 subtimer A           */
    (uint32_t)&Timer4B_IRQHandler,      /* Timer 4 subtimer B           */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    (uint32_t)&Timer5A_IRQHandler,      /* Timer 5 subtimer A           */
    (uint32_t)&Timer5B_IRQHandler,      /* Timer 5 subtimer B           */
    (uint32_t)&WideTimer0A_IRQHandler,  /* Wide Timer 0 subtimer A      */
    (uint32_t)&WideTimer0B_IRQHandler,  /* Wide Timer 0 subtimer B      */
    (uint32_t)&WideTimer1A_IRQHandler,  /* Wide Timer 1 subtimer A      */
    (uint32_t)&WideTimer1B_IRQHandler,  /* Wide Timer 1 subtimer B      */
    (uint32_t)&WideTimer2A_IRQHandler,  /* Wide Timer 2 subtimer A      */
    (uint32_t)&WideTimer2B_IRQHandler,  /* Wide Timer 2 subtimer B      */
    (uint32_t)&WideTimer3A_IRQHandler,  /* Wide Timer 3 subtimer A      */
    (uint32_t)&WideTimer3B_IRQHandler,  /* Wide Timer 3 subtimer B      */
    (uint32_t)&WideTimer4A_IRQHandler,  /* Wide Timer 4 subtimer A      */
    (uint32_t)&WideTimer4B_IRQHandler,  /* Wide Timer 4 subtimer B      */
    (uint32_t)&WideTimer5A_IRQHandler,  /* Wide Timer 5 subtimer A      */
    (uint32_t)&WideTimer5B_IRQHandler,  /* Wide Timer 5 subtimer B      */
    (uint32_t)&FPU_IRQHandler,          /* FPU                          */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    (uint32_t)&I2C4_IRQHandler,         /* I2C4 Master and Slave        */
    (uint32_t)&I2C5_IRQHandler,         /* I2C5 Master and Slave        */
    (uint32_t)&GPIOPortM_IRQHandler,    /* GPIO Port M                  */
    (uint32_t)&GPIOPortN_IRQHandler,    /* GPIO Port N                  */
    (uint32_t)&QEI2_IRQHandler,         /* Quadrature Encoder 2         */
    0,                             /* Reserved                     */
    0,                             /* Reserved                     */
    (uint32_t)&GPIOPortP0_IRQHandler,   /* GPIO Port P (Summary or P0)  */
    (uint32_t)&GPIOPortP1_IRQHandler,   /* GPIO Port P1                 */
    (uint32_t)&GPIOPortP2_IRQHandler,   /* GPIO Port P2                 */
    (uint32_t)&GPIOPortP3_IRQHandler,   /* GPIO Port P3                 */
    (uint32_t)&GPIOPortP4_IRQHandler,   /* GPIO Port P4                 */
    (uint32_t)&GPIOPortP5_IRQHandler,   /* GPIO Port P5                 */
    (uint32_t)&GPIOPortP6_IRQHandler,   /* GPIO Port P6                 */
    (uint32_t)&GPIOPortP7_IRQHandler,   /* GPIO Port P7                 */
    (uint32_t)&GPIOPortQ0_IRQHandler,   /* GPIO Port Q (Summary or Q0)  */
    (uint32_t)&GPIOPortQ1_IRQHandler,   /* GPIO Port Q1                 */
    (uint32_t)&GPIOPortQ2_IRQHandler,   /* GPIO Port Q2                 */
    (uint32_t)&GPIOPortQ3_IRQHandler,   /* GPIO Port Q3                 */
    (uint32_t)&GPIOPortQ4_IRQHandler,   /* GPIO Port Q4                 */
    (uint32_t)&GPIOPortQ5_IRQHandler,   /* GPIO Port Q5                 */
    (uint32_t)&GPIOPortQ6_IRQHandler,   /* GPIO Port Q6                 */
    (uint32_t)&GPIOPortQ7_IRQHandler,   /* GPIO Port Q7                 */
    (uint32_t)&GPIOPortR_IRQHandler,    /* GPIO Port R                  */
    (uint32_t)&GPIOPortS_IRQHandler,    /* GPIO Port S                  */
    (uint32_t)&PWM1Gen0_IRQHandler,     /* PWM 1 Generator 0            */
    (uint32_t)&PWM1Gen1_IRQHandler,     /* PWM 1 Generator 1            */
    (uint32_t)&PWM1Gen2_IRQHandler,     /* PWM 1 Generator 2            */
    (uint32_t)&PWM1Gen3_IRQHandler,     /* PWM 1 Generator 3            */
    (uint32_t)&PWM1Fault_IRQHandler     /* PWM 1 Fault                  */

};

__stackless void assert_failed (char const *file, int line) {
    /* TBD: damage control */
    NVIC_SystemReset(); /* reset the system */
}

__stackless void HardFault_Handler(void) {
    assert_failed("HardFault", __LINE__);
}

__stackless void NMI_Handler(void) {
    assert_failed("NMI", __LINE__);
}

__stackless void MemManage_Handler(void) {
    assert_failed("MemManage", __LINE__);
}

__stackless void BusFault_Handler(void) {
    assert_failed("BusFault", __LINE__);
}

__stackless void UsageFault_Handler(void) {
    assert_failed("UsageFault", __LINE__);
}

__stackless void Unused_Handler(void) {
    assert_failed("Unused", __LINE__);
}

#pragma weak SVC_Handler       = Unused_Handler
#pragma weak DebugMon_Handler  = Unused_Handler
#pragma weak PendSV_Handler    = Unused_Handler
#pragma weak SysTick_Handler   = Unused_Handler

#pragma weak GPIOPortA_IRQHandler   = Unused_Handler
#pragma weak GPIOPortB_IRQHandler   = Unused_Handler
#pragma weak GPIOPortC_IRQHandler   = Unused_Handler
#pragma weak GPIOPortD_IRQHandler   = Unused_Handler
#pragma weak GPIOPortE_IRQHandler   = Unused_Handler
#pragma weak UART0_IRQHandler       = Unused_Handler
#pragma weak UART1_IRQHandler       = Unused_Handler
#pragma weak SSI0_IRQHandler        = Unused_Handler
#pragma weak I2C0_IRQHandler        = Unused_Handler
#pragma weak PWMFault_IRQHandler    = Unused_Handler
#pragma weak PWMGen0_IRQHandler     = Unused_Handler
#pragma weak PWMGen1_IRQHandler     = Unused_Handler
#pragma weak PWMGen2_IRQHandler     = Unused_Handler
#pragma weak QEI0_IRQHandler        = Unused_Handler
#pragma weak ADCSeq0_IRQHandler     = Unused_Handler
#pragma weak ADCSeq1_IRQHandler     = Unused_Handler
#pragma weak ADCSeq2_IRQHandler     = Unused_Handler
#pragma weak ADCSeq3_IRQHandler     = Unused_Handler
#pragma weak Watchdog_IRQHandler    = Unused_Handler
#pragma weak Timer0A_IRQHandler     = Unused_Handler
#pragma weak Timer0B_IRQHandler     = Unused_Handler
#pragma weak Timer1A_IRQHandler     = Unused_Handler
#pragma weak Timer1B_IRQHandler     = Unused_Handler
#pragma weak Timer2A_IRQHandler     = Unused_Handler
#pragma weak Timer2B_IRQHandler     = Unused_Handler
#pragma weak Comp0_IRQHandler       = Unused_Handler
#pragma weak Comp1_IRQHandler       = Unused_Handler
#pragma weak Comp2_IRQHandler       = Unused_Handler
#pragma weak SysCtrl_IRQHandler     = Unused_Handler
#pragma weak FlashCtrl_IRQHandler   = Unused_Handler
#pragma weak GPIOPortF_IRQHandler   = Unused_Handler
#pragma weak GPIOPortG_IRQHandler   = Unused_Handler
#pragma weak GPIOPortH_IRQHandler   = Unused_Handler
#pragma weak UART2_IRQHandler       = Unused_Handler
#pragma weak SSI1_IRQHandler        = Unused_Handler
#pragma weak Timer3A_IRQHandler     = Unused_Handler
#pragma weak Timer3B_IRQHandler     = Unused_Handler
#pragma weak I2C1_IRQHandler        = Unused_Handler
#pragma weak QEI1_IRQHandler        = Unused_Handler
#pragma weak CAN0_IRQHandler        = Unused_Handler
#pragma weak CAN1_IRQHandler        = Unused_Handler
#pragma weak CAN2_IRQHandler        = Unused_Handler
#pragma weak Hibernate_IRQHandler   = Unused_Handler
#pragma weak USB0_IRQHandler        = Unused_Handler
#pragma weak PWMGen3_IRQHandler     = Unused_Handler
#pragma weak uDMAST_IRQHandler      = Unused_Handler
#pragma weak uDMAError_IRQHandler   = Unused_Handler
#pragma weak ADC1Seq0_IRQHandler    = Unused_Handler
#pragma weak ADC1Seq1_IRQHandler    = Unused_Handler
#pragma weak ADC1Seq2_IRQHandler    = Unused_Handler
#pragma weak ADC1Seq3_IRQHandler    = Unused_Handler
#pragma weak I2S0_IRQHandler        = Unused_Handler
#pragma weak EBI0_IRQHandler        = Unused_Handler
#pragma weak GPIOPortJ_IRQHandler   = Unused_Handler
#pragma weak GPIOPortK_IRQHandler   = Unused_Handler
#pragma weak GPIOPortL_IRQHandler   = Unused_Handler
#pragma weak SSI2_IRQHandler        = Unused_Handler
#pragma weak SSI3_IRQHandler        = Unused_Handler
#pragma weak UART3_IRQHandler       = Unused_Handler
#pragma weak UART4_IRQHandler       = Unused_Handler
#pragma weak UART5_IRQHandler       = Unused_Handler
#pragma weak UART6_IRQHandler       = Unused_Handler
#pragma weak UART7_IRQHandler       = Unused_Handler
#pragma weak I2C2_IRQHandler        = Unused_Handler
#pragma weak I2C3_IRQHandler        = Unused_Handler
#pragma weak Timer4A_IRQHandler     = Unused_Handler
#pragma weak Timer4B_IRQHandler     = Unused_Handler
#pragma weak Timer5A_IRQHandler     = Unused_Handler
#pragma weak Timer5B_IRQHandler     = Unused_Handler
#pragma weak WideTimer0A_IRQHandler = Unused_Handler
#pragma weak WideTimer0B_IRQHandler = Unused_Handler
#pragma weak WideTimer1A_IRQHandler = Unused_Handler
#pragma weak WideTimer1B_IRQHandler = Unused_Handler
#pragma weak WideTimer2A_IRQHandler = Unused_Handler
#pragma weak WideTimer2B_IRQHandler = Unused_Handler
#pragma weak WideTimer3A_IRQHandler = Unused_Handler
#pragma weak WideTimer3B_IRQHandler = Unused_Handler
#pragma weak WideTimer4A_IRQHandler = Unused_Handler
#pragma weak WideTimer4B_IRQHandler = Unused_Handler
#pragma weak WideTimer5A_IRQHandler = Unused_Handler
#pragma weak WideTimer5B_IRQHandler = Unused_Handler
#pragma weak FPU_IRQHandler         = Unused_Handler
#pragma weak PECI0_IRQHandler       = Unused_Handler
#pragma weak LPC0_IRQHandler        = Unused_Handler
#pragma weak I2C4_IRQHandler        = Unused_Handler
#pragma weak I2C5_IRQHandler        = Unused_Handler
#pragma weak GPIOPortM_IRQHandler   = Unused_Handler
#pragma weak GPIOPortN_IRQHandler   = Unused_Handler
#pragma weak QEI2_IRQHandler        = Unused_Handler
#pragma weak Fan0_IRQHandler        = Unused_Handler
#pragma weak GPIOPortP0_IRQHandler  = Unused_Handler
#pragma weak GPIOPortP1_IRQHandler  = Unused_Handler
#pragma weak GPIOPortP2_IRQHandler  = Unused_Handler
#pragma weak GPIOPortP3_IRQHandler  = Unused_Handler
#pragma weak GPIOPortP4_IRQHandler  = Unused_Handler
#pragma weak GPIOPortP5_IRQHandler  = Unused_Handler
#pragma weak GPIOPortP6_IRQHandler  = Unused_Handler
#pragma weak GPIOPortP7_IRQHandler  = Unused_Handler
#pragma weak GPIOPortQ0_IRQHandler  = Unused_Handler
#pragma weak GPIOPortQ1_IRQHandler  = Unused_Handler
#pragma weak GPIOPortQ2_IRQHandler  = Unused_Handler
#pragma weak GPIOPortQ3_IRQHandler  = Unused_Handler
#pragma weak GPIOPortQ4_IRQHandler  = Unused_Handler
#pragma weak GPIOPortQ5_IRQHandler  = Unused_Handler
#pragma weak GPIOPortQ6_IRQHandler  = Unused_Handler
#pragma weak GPIOPortQ7_IRQHandler  = Unused_Handler
#pragma weak GPIOPortR_IRQHandler   = Unused_Handler
#pragma weak GPIOPortS_IRQHandler   = Unused_Handler
#pragma weak PWM1Gen0_IRQHandler    = Unused_Handler
#pragma weak PWM1Gen1_IRQHandler    = Unused_Handler
#pragma weak PWM1Gen2_IRQHandler    = Unused_Handler
#pragma weak PWM1Gen3_IRQHandler    = Unused_Handler
#pragma weak PWM1Fault_IRQHandler   = Unused_Handler

