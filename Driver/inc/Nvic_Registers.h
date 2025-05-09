/**
*   @file    	Nvic_Register.h
*   @brief   	This file contains the structure definition for NVIC_Type, representing the NVIC 
*             (Nested Vectored Interrupt Controller) registers in ARM Cortex-M microcontrollers.
*   @details 	The NVIC_Type structure is used to manage interrupt control, including enabling/disabling
*             interrupts, setting/clearing pending states, checking active interrupts, and configuring
*             interrupt priority levels.

*   @authors 	Mai Anh Tuan
*   @date 		10/09/2024
*   @version 	1.0
*
*	  @note 		Make sure to include the CMSIS header file corresponding to your microcontroller to use the NVIC functions.
*/

/*==================================================================================================
==================================================================================================*/
#ifndef NVIC_REG_H
#define NVIC_REG_H

/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief        NVIC_Type structure
* @details      This structure represents the NVIC (Nested Vectored Interrupt Controller) registers 
*               for enabling/disabling interrupts, setting pending/clear-pending states, active bit 
*               information, and interrupt priority levels on an ARM Cortex-M microcontroller.
*
*               - ISERx: Interrupt Set-Enable Registers (for enabling interrupts).
*               - ICERx: Interrupt Clear-Disable Registers (for disabling interrupts).
*               - ISPRx: Interrupt Set-Pending Registers (for setting pending interrupts).
*               - ICPRx: Interrupt Clear-Pending Registers (for clearing pending interrupts).
*               - IABRx: Interrupt Active Bit Registers (for checking active interrupts).
*               - IPRx: Interrupt Priority Registers (for setting interrupt priorities).
*               - STIRx: Software Trigger Interrupt Register (for generating software interrupts).
*
*               The padding fields are used to align the registers correctly in memory, according to
*               the NVIC's memory map.
*/
typedef struct {
	volatile unsigned int ISER[8];
  volatile unsigned int padding_1[24];    /**< Padding for alignment */
  volatile unsigned int ICER[8];
  volatile unsigned int padding_2[24];    /**< Padding for alignment */
  volatile unsigned int ISPR[8];
  volatile unsigned int padding_3[24];    /**< Padding for alignment */
  volatile unsigned int ICPR[8];
  volatile unsigned int padding_4[24];    /**< Padding for alignment */
  volatile unsigned int IABR[8];
  volatile unsigned int padding_5[56];    /**< Padding for alignment */
  volatile unsigned int IPR[60];
} NVIC_Type;

/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
/** Peripheral S32_NVIC base address */
#define NVIC_BASE_ADDRESS                    (0xE000E100u)

/** Peripheral S32_NVIC base pointer */
#define NVIC                                 ((NVIC_Type *)NVIC_BASE_ADDRESS)

#endif
