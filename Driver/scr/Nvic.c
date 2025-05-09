/**
*   @file    	Nvic.c
*   @brief   	This file contains the implementation of NVIC-related functions. 
*   @details 	This file provides functions for configuring and controlling the Nested Vectored Interrupt Controller (NVIC) 
*               on ARM Cortex-M microcontrollers. Functions include enabling/disabling interrupts, setting priorities, and more.

*   @authors 	Mai Anh Tuan
*   @date 		10/09/2024
*   @version 	1.0
*
*	@note 		Make sure to include the CMSIS header file corresponding to your microcontroller to use the NVIC functions.
*/

/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Nvic.h"

/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/

static unsigned char offset;
static unsigned int shiftAmount;
static unsigned int mask;

/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/

/**
* @brief        Enable Interrupt of IRQn pin
* @details      This function enable the interrupt in the NVIC corresponding to the given IRQ_number parameter
*				To advoid malfunction, the IRQ number must be matched with NVIC Interrupt ID in DMA_Interrupt_Mapping_Table
*
* @param[in]    IRQn_Type 
*                             
* @return       void
*
* @pre          The IRQ_number must be valid and within the range supported by the NVIC 
* @post         The interrupt corresponding to IRQ_number will be enabled.
*
* @api			This function is apart of API to control NVIC
*
*/
void NVIC_EnableInterrupt(IRQn_Type IRQ_number)
{
	NVIC->ISER[IRQ_number/32]= ((1<< (IRQ_number%32)));
}

/**
* @brief        Disnable Interrupt of IRQn pin
* @details      This function disable the interrupt in the NVIC corresponding to the given IRQ_number parameter
*				To advoid malfunction, the IRQ number must be matched with NVIC Interrupt ID in DMA_Interrupt_Mapping_Table
*
* @param[in]    IRQn_Type 
*                             
* @return       void
*
* @pre          The IRQ_number must be valid and within the range supported by the NVIC 
* @post         The interrupt corresponding to IRQ_number will be disabled.
*
* @api			This function is apart of API to control NVIC
*
*/
void NVIC_DisableInterrupt(IRQn_Type IRQ_number)
{
	NVIC->ICER[IRQ_number/32]= ((1<< (IRQ_number%32)));
}

/**
* @brief        Set pendding flag of IRQn pin
* @details      This function sets the pending flag of the interrupt in the NVIC corresponding to the given IRQ_number parameter
*				To advoid malfunction, the IRQ number must be matched with NVIC Interrupt ID in DMA_Interrupt_Mapping_Table
*
* @param[in]    IRQn_Type 
*                             
* @return       void
*
* @pre          The IRQ_number must be valid and within the range supported by the NVIC 
* @post         The pending flag of the interrupt corresponding to IRQ_number will be enabled.
*
* @api			This function is apart of API to control NVIC
*
*/
void NVIC_SetPendingFlag(IRQn_Type IRQ_number)
{
	NVIC->ISPR[IRQ_number/32]= ((1<< (IRQ_number%32)));
}

/**
* @brief        Clear the pendding flag of IRQn pin
* @details      This function clears the pending flag of the interrupt in the NVIC corresponding to the given IRQ_number parameter
*				To advoid malfunction, the IRQ number must be matched with NVIC Interrupt ID in DMA_Interrupt_Mapping_Table
*
* @param[in]    IRQn_Type 
*                             
* @return       void
*
* @pre          The IRQ_number must be valid and within the range supported by the NVIC 
* @post         The pending flag of the interrupt corresponding to IRQ_number will be cleared.
*
* @api			This function is apart of API to control NVIC
*
*/
void NVIC_ClearPendingFlag(IRQn_Type IRQ_number)
{
	NVIC->ICPR[IRQ_number/32]= ((1<< (IRQ_number%32)));
}

/**
* @brief        Read the state of the pendding flag of IRQn pin
* @details      This function reads the state of the pending flag of the interrupt in the NVIC corresponding to the given IRQ_number parameter
*				To advoid malfunction, the IRQ number must be matched with NVIC Interrupt ID in DMA_Interrupt_Mapping_Table
*
* @param[in]    IRQn_Type 
*                             
* @return       unsigned char
*
* @pre          The IRQ_number must be valid and within the range supported by the NVIC 
* @post         The state of the pending flag of the interrupt corresponding to IRQ_number will be read.
*
* @api			This function is apart of API to control NVIC
*
*/
unsigned char NVIC_GetPendingInterrupt(IRQn_Type IRQ_number)
{
	if ((NVIC_IABR(IRQ_number)>>IRQ_number)&0x01)
	{
		return ACTIVE;
	}
	else
	{
		return NOT_ACTIVE;
	}
}

/**
* @brief        Set priority for  IRQn pin
* @details      This function set priority of the interrupt in the NVIC corresponding to the given IRQ_number parameter
*				To advoid malfunction, the IRQ number must be matched with NVIC Interrupt ID in DMA_Interrupt_Mapping_Table
*				and the priority value must be below 15.
*
* @param[in]    IRQn_Type 
*                             
* @return       void
*
* @pre          The IRQ_number must be valid and within the range supported by the NVIC 
* @post         The preemption of the interrupt corresponding to IRQ_number will be set.
*
* @api			This function is apart of API to control NVIC
*/

void NVIC_SetPriority(IRQn_Type IRQ_number, unsigned int priority)
{
	/*Check valid of priority value*/
  	if (priority > 15) 
	{
     return;
  	}
	offset = IRQ_number%4;
	shiftAmount = offset*8;
	/*Clear previous priority value of IRQn*/
	mask = (unsigned int)(0xFF << shiftAmount);
	NVIC->IPR[IRQ_number / 4] &= ~mask;
	/*Set new priority value for IRQn*/
	NVIC->IPR[IRQ_number / 4] |= (priority<<(shiftAmount+4));
}

