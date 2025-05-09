
/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Systick.h"
/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/   
void Systick_Init(const Systick_ConfigType* ConfigPtr)
{
	//unsigned int Tval;
	/* Step 1. Check parameter */
	if (ConfigPtr == NULL) return;
	/* Step 2. Configuration for SysTick timer*/
	/* Step 2. 1. Disable the SysTick timer */
	SYST -> CSR &= ~(1U << SYST_CSR_ENABLE_SHIFT);
	/* Step 2.2. Setting the reload value */
	if(ConfigPtr->period != 0 )
	{
		SYST -> RVR = ConfigPtr -> period;
	} else 
	{
		SYST -> RVR = 0xFFFFFFU;
	}
	/* Step 2.3. Clear the current value */
	SYST -> CVR = 0;
	/* Step 2.4. Check whether timeout interrupt is set ?*/
	if(ConfigPtr->isInterruptEnabled != 0 )
	{
		SYST -> CSR |= (1U << SYST_CSR_TICKINT_SHIFT);
	}
	/* Step 2.5. Choose system clock*/
	if (ConfigPtr->fSystick != 0)
	{
		SYST -> CSR |= (1U << SYST_CSR_CLKSOURCE_SHIFT); /* Processor Clock */
	}
}

void Systick_Start(void)
{
	SYST -> CSR |= (1U << SYST_CSR_ENABLE_SHIFT);
}

void Systick_Stop(void)
{
	SYST -> CSR &= ~(1U << SYST_CSR_ENABLE_SHIFT);
}

unsigned int Systick_GetCounter(void)
{
	return (SYST->CVR);
}


void Delay(unsigned int ms)
{
	unsigned int count=0;
	while(1)
	{
	if ((SYST -> CSR >> SYST_CSR_COUNTFLAG_SHIFT) & COUNTFLAG_IS_SET)
	{
		count++;
		if (count==ms+1)
		{
			count=0;
			break;
		}
	}
	}
}
