/**
 * @file    
 * @brief   
 * @details 
 *          
 *
 * @version 1.0
 * @date    2024-10-09
 * @author  Mai Anh Tuan
 */
 /*==================================================================================================
==================================================================================================*/
#ifndef CONFIG_H
#define CONFIG_H
 /*==================================================================================================
*                                       INCLUDE FILE
==================================================================================================*/
#include "GPIO.h"
#include "Port.h"
#include "Nvic.h"
#include "Clock.h"
#include "Systick.h"
#include "Lpit.h"
#include "Lpspi.h"
#include "Lpuart.h"
 /*==================================================================================================
*                                       MACRO DEFINITIONS
==================================================================================================*/
#define PCC_PORTC_REG_H 				(*(volatile unsigned int*)(0x40065000u + 0x12CU))
#define ADC0_BASE_ADDRESS 0x4003B000U 
#define ADC0 	    (*(volatile unsigned int* ADC0_BASE_ADDRESS))
#define ADC0_CFG1 (*((volatile unsigned int*)(ADC0_BASE_ADDRESS + 0x40U)))
#define ADC0_SC3 	(*((volatile unsigned int*)(ADC0_BASE_ADDRESS + 0x94U)))	
#define ADC0_SC1A (*((volatile unsigned int*)(ADC0_BASE_ADDRESS)))	
#define ADC0_CFG2 (*((volatile unsigned int*)(ADC0_BASE_ADDRESS + 0x44U)))	
#define ADC0_SC2 	(*((volatile unsigned int*)(ADC0_BASE_ADDRESS+ 0x90U)))		
#define ADC0_RA 	(*((volatile unsigned int*)(ADC0_BASE_ADDRESS+ 0x48U)))
#define ADC_SC1A_ADCH_SHIFT (0U)
#define ADC0_SE12 					(12U)
 /*==================================================================================================
*                                  GLOBAL FUNCTION PROTOTYPE
==================================================================================================*/
void Config_System(void);

#endif

