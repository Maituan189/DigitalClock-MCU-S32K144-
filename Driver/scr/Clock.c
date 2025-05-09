/**
 * @file    Clock.c
 * @brief   Clock configuration implementation.
 * @details This file contains functions to configure various clock sources
 *          and settings for the system, including peripheral clocks, 
 *          FIRC, SIRC, SOSC, SPLL, and the system run mode clock.
 *
 * @note    This code is designed for a microcontroller clock setup.
 *
 * @version 1.0
 * @date    2024-10-20
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Clock.h"
/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/   
void Clock_SetPccConfig(const Pcc_ConfigType* ConfigPtr)
{
	/* 1. Disable the peripheral clock */
	PCC->PCCn[ConfigPtr->clockName] &=~ (1u<<PCC_CGC_SHIFT);
	
	/* 2. Check whether Clock Gate Control is enable or disable ?*/
	if( ConfigPtr->clkGate == CLK_GATE_ENABLE )
	{
		/* 2.1. Check whether Peripheral Clock Source Select is off or set ?*/
		if(ConfigPtr->clkSrc != CLK_SRC_OFF)
		{
			/* Set Peripheral Clock Source Select */
			PCC->PCCn[ConfigPtr->clockName] |= ( (unsigned int)ConfigPtr->clkSrc << PCC_PCS_SHIFT);
		}
		
		/* 2.2. Enable the peripheral clock */
		PCC->PCCn[ConfigPtr->clockName] |= (1u<<PCC_CGC_SHIFT);
	}
	
}

void Clock_SetScgFircConfig(const Scg_Firc_ConfigType * ConfigPtr)
{
	SCG ->FIRCCSR |= (1U<<SCG_FIRC_ENABLE_SHIFT);
	/* Step 1. Setup dividers 1. */
	SCG->FIRCDIV |= ((unsigned int)(ConfigPtr->div1)<< SCG_FIRCDIV_FIRCDIV1_SHIFT);
	/* Step 2. Setup dividers 2. */
	SCG->FIRCDIV |= ((unsigned int)(ConfigPtr->div2)<< SCG_FIRCDIV_FIRCDIV2_SHIFT);
	
}

void Clock_SetScgSircConfig(const Scg_Sirc_ConfigType * ConfigPtr)
{
	SCG -> SIRCCSR |= (1U<<SCG_SIRC_ENABLE_SHIFT);
	/* Step 1. Setup dividers 1 */
	SCG->SIRCDIV |= ((unsigned int)(ConfigPtr->div1)<< SCG_FIRCDIV_FIRCDIV1_SHIFT);
	
	/* Step 2. Setup dividers 2. */
	SCG->SIRCDIV |= ((unsigned int)(ConfigPtr->div2)<< SCG_FIRCDIV_FIRCDIV2_SHIFT);
	
}

void Clock_SetScgSoscConfig(const Scg_Sosc_ConfigType * ConfigPtr)
{
	/* Step 1. Setup dividers 1 */
	SCG->SOSCDIV |= ((unsigned int)(ConfigPtr->div1)<< SCG_SOSCDIV_SOSCDIV1_SHIFT);
	
	/* Step 2. Setup dividers 2. */
	SCG->SOSCDIV |= ((unsigned int)(ConfigPtr->div2)<< SCG_SOSCDIV_SOSCDIV2_SHIFT);
	
	/* Step 3. Set SOSC configuration. */
	SCG->SOSCCFG = (SCG_SOSCCFG_RANGE_MEDIUMFREQ<<SCG_SOSCCFG_RANGE_SHIFT)|(SCG_SOSCCFG_EREFS_INTERNAL_CRYSTAL<<SCG_SOSCCFG_EREFS_SHIFT);
	
	/* Step 4. Clear Lock Register */
	SCG->SOSCCFG &= ~(1U<<SCG_CSR_LK_SHIFT);
	
	/* Step 5. Enable SOSC clock*/
	SCG->SOSCCSR |= (1U<<SCG_SOSCCSR_ENABLE_SHIFT);
	
	/* Step 6. Wait for System OSC to initialize */
	while (((SCG ->SOSCCSR >>SCG_SOSCCSR_SOSCVLD_SHIFT) & 0x01) ==0);
}

void Clock_SetScgSpllConfig(const Scg_Spll_ConfigType * ConfigPtr)
{
	
	/* Step 1. Disable SPLL */
	SCG->SPLLCSR &= ~(1U<<SCG_SPLLCSR_DISABLE_SHIFT);

	/* Step 2. Setup dividers 1 */
	SCG->SPLLDIV |= ((unsigned int)(ConfigPtr->div1)<< SCG_SPLLDIV_SPLLDIV1_SHIFT);
	
	/* Step 2. Setup dividers 2. */
	SCG->SPLLDIV |= ((unsigned int)(ConfigPtr->div2)<< SCG_SPLLDIV_SPLLDIV2_SHIFT);
	
	/* Step 3. Set PLL configuration. */
	SCG->SPLLCFG = 0;
	SCG->SPLLCFG |= ((unsigned int)(ConfigPtr->prediv)<< SCG_SPLLCFG_SPLLPREDIV_SHIFT);
	SCG->SPLLCFG |= ((unsigned int)(ConfigPtr->mult)<< SCG_SPLLCFG_SPLLMULT_SHIFT);
	SCG->SPLLCFG |= ((unsigned int)(ConfigPtr->src)<< SCG_SPLLCFG_SPLLSRC_SHIFT);
	/* Step 4. Clear Lock Register */
	SCG->SPLLCSR &= ~(1U<<SCG_CSR_LK_SHIFT);

	/* Step 5. Enable SPLL clock*/
	SCG->SPLLCFG = 1U;
	
	/* Step 6. Wait for SPLL to initialize */
	while (((SCG ->SPLLCSR >>SCG_SPLLCSR_SPLLVLD_SHIFT) & 0x01) ==0);
}

void Clock_SetScgRunModeConfig(const Scg_RunMode_ConfigType * ConfigPtr)
{
	/* Step1 .Sets the RUN clock control (system clock source, bus, core and slow dividers */
	unsigned int value = 0;
	
	/* Step1.1. Set system clock source */
	value |= ((unsigned int)ConfigPtr->sys_clk_src <<SCG_RCCR_SCS_SHIFT);
	
	/* Step1.2. Set Core Clock Divide Ratio */
	value |= ((unsigned int)ConfigPtr->sys_clk_src <<SCG_RCCR_DIVCORE_SHIFT);

	/* Step1.3. Set Bus Clock Divide Ratio */
	value |= ((unsigned int)ConfigPtr->sys_clk_src <<SCG_RCCR_DIVBUS_SHIFT);

	/* Step1.4. Set Slow Clock Divide Ratio */
	value |= ((unsigned int)ConfigPtr->slow_div <<SCG_RCCR_DIVSLOW_SHIFT);
	
	SCG->RCCR = value;
	
	/* Step 2. cormfirm: System Clock Source as config */
	while(!((SMC_PMSTAT>>0)&0x01));
}
