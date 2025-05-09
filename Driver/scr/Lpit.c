/**
 * @file    Lpit.c
 * @brief   Low Power Interval Timer (LPIT) driver implementation.
 * @details This file contains the implementation of functions to initialize, 
 *          configure, and control the LPIT peripheral. It includes functions 
 *          to start and stop the timer channels, manage interrupts, and retrieve 
 *          the current counter value for each channel.
 *
 * @note    This implementation assumes a 32-bit periodic counter mode for the LPIT channels.
 *
 * @version 1.0
 * @date    2024-10-20
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Lpit.h"
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void Lpit_Init( void )
{
	/* Step 1. Set Debug mode */
	LPIT0->MCR |= (1u<<LPIT_MCR_DBG_EN_SHIFT);
	
	/* Step 2. Enable peripheral clock to timers */
	LPIT0->MCR |= (1u<<LPIT_MCR_M_CEN_SHIFT);
	
}
void Lpit_InitChannel(unsigned char channel, const Lpit_ChannelConfigType* ConfigPtr)
{
	/* Step 1. Check parameter */
	if (channel > LPIT_CHANNEL_3 || channel < LPIT_CHANNEL_0)
	{
		return;
	}
	else 
	{
		/*do not thing */
	}
	/* Step 2. Setups the timer channel operation mode: 32-bit Periodic Counter */
	LPIT0->TMR[channel].TCTRL &=~ (3u<<LPIT_TMR_TCTRL_MODE_SHIFT);
	
	/* Step 3. Set Timer Value Register */
	if(ConfigPtr->period != 0 )
	{
		LPIT0->TMR[channel].TVAL = ConfigPtr->period;
	} 
	else 
	{
		LPIT0->TMR[channel].TVAL = MAX_TAVL_VALUE;
	}
	/* Step 4. Check whether timeout interrupt is set ?*/
	if(ConfigPtr->isInterruptEnabled == 1)
	{
		LPIT0->MIER |=(1u<<channel);
	}
}

void Lpit_StartChannel(unsigned char channel)
{
	/* Step 1. Check parameter */
	if (channel > LPIT_CHANNEL_3 || channel < LPIT_CHANNEL_0)
	{
		return;
	}
	else 
	{
		/*do not thing */
	}
	/* Step 2. Starts timer channel counting */
	LPIT0->TMR[channel].TCTRL |= (1u<<LPIT_TMR_TCTRL_T_EN_SHIFT);
	
}


void Lpit_StopChannel(unsigned char channel)
{
	/* Step 1. Check parameter */
	if (channel > LPIT_CHANNEL_3 || channel < LPIT_CHANNEL_0)
	{
		return;
	}
	else 
	{
		/*do not thing */
	}
	/* Step 2. Stop timer channel counting */
	LPIT0->TMR[channel].TCTRL &= ~(1u<<LPIT_TMR_TCTRL_T_EN_SHIFT);
	
}

unsigned int Lpit_GetCounterChannel(unsigned char channel)
{
	/* Step 1. Check parameter */
	if (channel > LPIT_CHANNEL_3 || channel < LPIT_CHANNEL_0)
	{
		return DISABLE_LPIT;
	}
	else 
	{
		/*do not thing */
	}
	/* Step 2. Check whether timer channel is enabled? */
	if (((LPIT0->TMR[channel].TCTRL >> LPIT_TMR_TCTRL_T_EN_SHIFT) & 0x01) == 0)
	{
		return DISABLE_LPIT;
	}
	else
	{
		return LPIT0->TMR[channel].CVAL;
	}
}


void Lpit_Clear_Interrupt_Flag (unsigned char channel)
{
	if (channel > LPIT_CHANNEL_3 || channel < LPIT_CHANNEL_0)
	{
		return;
	}
	else 
	{
		/*do not thing */
	}
	LPIT0->MSR |= (1U<<channel);
}

