/**
 * @file    Lpuart.c
 * @brief   LPUART driver implementation for initialization, transmit, and receive functions.
 * @details This file provides functions to initialize the LPUART peripheral, 
 *          transmit data, and receive data using the provided configuration structure.
 *
 * @note    The user needs to ensure the configuration structure is set up correctly before calling the initialization function.
 *
 * @version 1.0
 * @date    2024-10-20
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Lpuart.h"
/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/     
void Lpuart_Init (const Lpuart_ConfigType* ConfigPtr)
{
	unsigned int BAUD_Reg_Value=0;

	/*1. Check parameter */
	if (ConfigPtr == ((void*)0)
	|| ConfigPtr->Init.lpuart_baudrate_modulo_divisor == 0
	|| ConfigPtr->Init.lpuart_oversampling < oversampling_ratio_4 
	|| ConfigPtr->Init.lpuart_oversampling > oversampling_ratio_17
	|| (ConfigPtr->Init.lpuart_stop_bit != ONE_STOP_BIT && ConfigPtr->Init.lpuart_stop_bit != TWO_STOP_BIT)
	|| (ConfigPtr->Init.lpuart_data_frame != FRAME_8_BIT && ConfigPtr->Init.lpuart_data_frame != FRAME_9_BIT)
	|| (ConfigPtr->Init.lpuart_parity_bit != LPUART_ENABLE_PARITY_BIT && ConfigPtr->Init.lpuart_parity_bit != LPUART_DISABLE_PARITY_BIT)
	) 
	{
        return;
  }
	else 
	{
		/*do not thing */
	}
	/*Additional checks for idle settings only if enabled*/ 
	if (ConfigPtr->Init.lpuart_enable_idl) 
	{
    	if (ConfigPtr->Init.lpuart_number_character_idl > IDLE_CHARACTER_128 ||
    	    (ConfigPtr->Init.lpuart_type_select_idl != COUNT_FROM_START_BIT && 
    	     ConfigPtr->Init.lpuart_type_select_idl != COUNT_FROM_STOP_BIT)) 
    	{
		
    	    return; 
    	}
		else 
		{
			/*do not thing*/
		}
	}
	else 
	{
		/*do not thing*/
	}
	/*2. Setting baud rate */
	BAUD_Reg_Value |= (((unsigned int)(ConfigPtr->Init.lpuart_baudrate_modulo_divisor)<<LPUART_BAUD_SBR_SHIFT))
					|((unsigned int)(ConfigPtr->Init.lpuart_oversampling)<<LPUART_BAUD_OSR_SHIFT);
	ConfigPtr->pUARTx->BAUD = BAUD_Reg_Value;

	/*2. Setting frame */
	/*Select Stop Bit Number: BAUD[SBNS] */
	BAUD_Reg_Value |= ((unsigned int)(ConfigPtr->Init.lpuart_stop_bit)<<LPUART_BAUD_SBNS_SHIFT);
	ConfigPtr->pUARTx->BAUD = BAUD_Reg_Value;

	/*Set data characters number: CTRL[M] */
	ConfigPtr->pUARTx->CTRL |= ((unsigned int)(ConfigPtr->Init.lpuart_data_frame)<<LPUART_CTRL_M_SHIFT);

	/*Set parity bit: CTRL[PE] */
	ConfigPtr->pUARTx->CTRL |= ((unsigned int)(ConfigPtr->Init.lpuart_parity_bit)<<LPUART_CTRL_PE_SHIFT);

	if ((ConfigPtr->Init.lpuart_enable_int_RX) > 0)
	{
		ConfigPtr ->pUARTx ->CTRL |= (1U<<LPUART_CTRL_RIE_SHIFT);
	}
	else 
	{
		/*do not thing*/
	}

	if((ConfigPtr->Init.lpuart_enable_idl) > 0)
	{
		ConfigPtr->pUARTx->CTRL |= (1U<<LPUART_CTRL_ILIE_SHIFT);
		ConfigPtr->pUARTx->CTRL |= ((unsigned int)ConfigPtr->Init.lpuart_number_character_idl<<LPUART_CTRL_IDLECFG_SHIFT);
		ConfigPtr->pUARTx->CTRL |= ((unsigned int)ConfigPtr->Init.lpuart_type_select_idl<<LPUART_CTRL_ILT_SHIFT);
	}
	else 
	{
		/*do not thing*/
	}
	/*Enable transmitter, receiver Transmitter Enable: CTRL[TE] & Receiver Enable: CTRL[RE]*/
	ConfigPtr ->pUARTx ->CTRL |= (1U<< LPUART_CTRL_TE_SHIFT) | (1U<< LPUART_CTRL_RE_SHIFT);
}


void Lpuart_Transmit(LPUART_Type *pUartx, unsigned char *pTxBuffer, unsigned char size)
{
	while (size>0)
	{
		while ((((pUartx->STAT) >> LPUART_STAT_TDRE_SHIFT) & 0x01) == 0);
		pUartx->DATA = *pTxBuffer;
		pTxBuffer++;
		size--;
	}
}

void Lpuart_Receive(LPUART_Type *pUartx, unsigned char *pRxBuffer)
{
	*(pRxBuffer) = (unsigned char) pUartx->DATA;
}
