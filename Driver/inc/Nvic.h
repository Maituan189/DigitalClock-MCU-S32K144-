/**
*   @file    	Nvic.h
*   @brief   	This file contains the defined values and enum IRQ_Type of NVIC-related functions. 
*   @details 	This file declare prototype functions for configuring and controlling the Nested Vectored Interrupt Controller (NVIC) 
*             on ARM Cortex-M microcontrollers. Functions include enabling/disabling interrupts, setting priorities, and more. It 
*             contains enum of IRQ Handlers supported by CMSIC header file

*   @authors 	Mai Anh Tuan
*   @date 		10/09/2024
*   @version 	1.0
*
*	  @note 		Make sure to include the CMSIS header file corresponding to your microcontroller to use the NVIC functions.
*/

/*==================================================================================================
==================================================================================================*/
#ifndef NVIC_H
#define NVIC_H
/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Nvic_Registers.h"
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define BASE_ADDRES_NVIC_ISER 0xE000E100u       /*Base-address of Interrupt Set-Enable Register       */
#define BASE_ADDRES_NVIC_ICER 0xE000E180u       /*Base-address of Interrupt Clear-Enable Register     */
#define BASE_ADDRES_NVIC_ISPR 0xE000E200u       /*Base-address of Interrupt Set-Pending Register      */
#define BASE_ADDRES_NVIC_ICPR 0xE000E280u       /*Base-address of Interrupt Clear-Enable Register     */
#define BASE_ADDRES_NVIC_IABR 0xE000E300u       /*Base-address of Interrupt Active Bit Register       */
#define BASE_ADDRES_NVIC_IPR  0xE000E400u       /*Base-address of Interrupt Priority Enable Register  */
#define BASE_ADDRES_NVIC_STIR 0xE000EF00u       /*Base-address of Software Trigger Interrupt Register */

#define NVIC_ISER(IRQn) (*((volatile unsigned int*)(BASE_ADDRES_NVIC_ISER + (IRQn / 32)*4)))
#define NVIC_ICER(IRQn) (*((volatile unsigned int*)(BASE_ADDRES_NVIC_ICER + (IRQn / 32)*4)))
#define NVIC_ISPR(IRQn) (*((volatile unsigned int*)(BASE_ADDRES_NVIC_ISPR + (IRQn / 32)*4)))
#define NVIC_ICPR(IRQn) (*((volatile unsigned int*)(BASE_ADDRES_NVIC_ICPR + (IRQn / 32)*4)))
#define NVIC_IABR(IRQn) (*((volatile unsigned int*)(BASE_ADDRES_NVIC_IABR + (IRQn / 32)*4)))
#define NVIC_IPR(IRQn)  (*((volatile unsigned int*)(BASE_ADDRES_NVIC_IPR  + IRQn)))

#define ACTIVE     1
#define NOT_ACTIVE 0

/*==================================================================================================
*                                             ENUMS
==================================================================================================*/
typedef enum
{
  DMA_0_IRQn               = 0u,
  DMA_1_IRQn               = 1u,
  DMA_2_IRQn               = 2u,
  DMA_3_IRQn               = 3u,
  DMA_4_IRQn               = 4u,
  DMA_5_IRQn               = 5u,
  DMA_6_IRQn               = 6u,
  DMA_7_IRQn               = 7u,
  DMA_8_IRQn               = 8u,
  DMA_9_IRQn               = 9u,
  DMA_10_IRQn              = 10u,
  DMA_11_IRQn              = 11u,
  DMA_12_IRQn              = 12u,
  DMA_13_IRQn              = 13u,
  DMA_14_IRQn              = 14u,
  DMA_15_IRQn              = 15u,
  DMA_Error_IRQ            = 16u,
  MCM_IRQ                  = 17u, 
  FTFC_IRQ                 = 18u,
  Read_Collision_IRQ       = 19u, 
  LVD_LVW_IRQ              = 20u, 
  FTFC_Fault_IRQ           = 21u,
  WDOG_EWM_IRQ             = 22u,  
  RCM_IRQ                  = 23u,
  LPI2C0_Master_IRQ        = 24u, 
  LPI2C0_Slave_IRQ         = 25u,
  LPSPI0_IRQHandler        = 26u, 
  LPSPI1_IRQ               = 27u,
  LPSPI2_IRQ               = 28u,
  Reserved45_IRQ           = 29u,
  Reserved46_IRQ           = 30u,
  LPUART0_RxTx_IRQ         = 31u,
  Reserved48_IRQ           = 32u,
  LPUART1_RxTx_IRQn        = 33u,     /**< LPUART1 Transmit / Receive  Interrupt */
  Reserved50_IRQH          = 34u,
  LPUART2_RxTx_IRQ         = 35u,
  Reserved52_IRQ           = 36u,
  Reserved53_IRQ           = 37u,
  Reserved54_IRQ           = 38u, 
  ADC0_IRQ                 = 39u,
  ADC1_IRQ                 = 40u,
  CMP0_IRQ                 = 41u,
  Reserved58_IRQ           = 42u,
  Reserved59_IRQ           = 43u,
  ERM_single_fault_IRQ     = 44u,
  ERM_double_fault_IRQ     = 45u,
  RTC_IRQ                  = 46u,
  RTC_Seconds_IRQ          = 47u,
  LPIT0_Ch0_IRQ            = 48u,
  LPIT0_Ch1_IRQ            = 49u,
  LPIT0_Ch2_IRQ            = 50u,
  LPIT0_Ch3_IRQ            = 51u,
  PDB0_IRQ                 = 52u,
  Reserved69_IRQ           = 53u,
  Reserved70_IRQ           = 54u,
  Reserved71_IRQ           = 55u,
  Reserved72_IRQ           = 56u,
  SCG_IRQ                  = 57u,
  LPTMR0_IRQ               = 58u,
  PORTA_IRQn               = 59u,     /**< Port A pin detect interrupt */
  PORTB_IRQn               = 60u,     /**< Port B pin detect interrupt */
  PORTC_IRQn               = 61u,     /**< Port C pin detect interrupt */
  PORTD_IRQn               = 62u,     /**< Port D pin detect interrupt */
  PORTE_IRQn               = 63u,     /**< Port E pin detect interrupt */
  SWI_IRQ                  = 64u,    
  Reserved81_IRQ           = 65u,    
  Reserved82_IRQ           = 66u,    
  Reserved83_IRQ           = 67u,
  PDB1_IRQ                 = 68u,
  FLEXIO_IRQ               = 69u,
  Reserved86_IRQ           = 70u,
  Reserved87_IRQ           = 71u,
  Reserved88_IRQ           = 72u,
  Reserved89_IRQ           = 73u,
  Reserved90_IRQ           = 74u,
  Reserved91_IRQ           = 75u,
  Reserved92_IRQ           = 76u,
  Reserved93_IRQ           = 77u,
  CAN0_ORed_IRQ            = 78u,
  CAN0_Error_IRQ           = 79u,
  CAN0_Wake_Up_IRQ         = 80u,
  CAN0_ORed_0_15_MB_IRQ    = 81u,
  CAN0_ORed_16_31_MB_IRQ   = 82u,
  Reserved99_IRQ           = 83u,
  Reserved100_IRQ          = 84u,
  CAN1_ORed_IRQ            = 85u,
  CAN1_Error_IRQ           = 86u,
  Reserved103_IRQ          = 87u,
  CAN1_ORed_0_15_MB_IRQ    = 88u,
  Reserved105_IRQ          = 89u,
  Reserved106_IRQ          = 90u,
  Reserved107_IRQ          = 91u,
  CAN2_ORed_IRQ            = 92u,
  CAN2_Error_IRQ           = 93u,
  Reserved110_IRQ          = 94u,
  CAN2_ORed_0_15_MB_IRQ    = 95u,
  Reserved112_IRQ          = 96u,
  Reserved113_IRQ          = 97u,
  Reserved114_IRQ          = 98u,
  FTM0_Ch0_Ch1_IRQ         = 99u,
  FTM0_Ch2_Ch3_IRQ         = 100u,
  FTM0_Ch4_Ch5_IRQ         = 101u,
  FTM0_Ch6_Ch7_IRQ         = 102u,
  FTM0_Fault_IRQ           = 103u,
  FTM0_Ovf_Reload_IRQ      = 104u,
  FTM1_Ch0_Ch1_IRQ         = 105u,
  FTM1_Ch2_Ch3_IRQ         = 106u,
  FTM1_Ch4_Ch5_IRQ         = 107u,
  FTM1_Ch6_Ch7_IRQ         = 108u,
  FTM1_Fault_IRQ           = 109u,
  FTM1_Ovf_Reload_IRQ      = 110u,     
  FTM2_Ch0_Ch1_IRQ         = 111u,
  FTM2_Ch2_Ch3_IRQ         = 112u,
  FTM2_Ch4_Ch5_IRQ         = 113u,
  FTM2_Ch6_Ch7_IRQ         = 114u,
  FTM2_Fault_IRQ           = 115u,
  FTM2_Ovf_Reload_IRQ      = 116u,
  FTM3_Ch0_Ch1_IRQ         = 117u,
  FTM3_Ch2_Ch3_IRQ         = 118u,
  FTM3_Ch4_Ch5_IRQ         = 119u,
  FTM3_Ch6_Ch7_IRQ         = 110u,
  FTM3_Fault_IRQ           = 121u,
  FTM3_Ovf_Reload_IRQ      = 122u,
} IRQn_Type;                            /*NVIC Interrupt ID*/        

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/

void NVIC_EnableInterrupt(IRQn_Type IRQ_number);
void NVIC_DisableInterrupt(IRQn_Type IRQ_number);
void NVIC_SetPendingFlag(IRQn_Type IRQ_number);
void NVIC_ClearPendingFlag(IRQn_Type IRQ_number);
unsigned char NVIC_GetPendingInterrupt(IRQn_Type IRQ_number);
void NVIC_SetPriority(IRQn_Type IRQ_number, unsigned int priority);

#endif /* NVIC_H */


