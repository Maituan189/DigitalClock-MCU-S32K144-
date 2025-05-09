/**
 * @file    Lpuart_Register.h
 * @brief   Low Power Universal Asynchronous Receiver-Transmitter (LPUART) Register Definitions
 * @details This file contains the register definitions and shift constants 
 *          for the LPUART peripherals. It provides the necessary structures 
 *          and macros for accessing and configuring the LPUART hardware.
 *
 * @note    This implementation is intended for use with the Kinetis family 
 *          of microcontrollers, where LPUART is used for serial communication.
 *
 * @version 1.0
 * @date    2024-10-20
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
==================================================================================================*/
#ifndef LPUART_REG_H
#define LPUART_REG_H
/*==================================================================================================
*                                       MACRO DEFINITIONS
==================================================================================================*/
/* LPUART Register Shift Bit*/
#define LPUART_BAUD_OSR_SHIFT 			(24U)
#define LPUART_BAUD_SBR_SHIFT 			(0U)
#define LPUART_BAUD_SBNS_SHIFT 		  (13U)
#define LPUART_CTRL_M_SHIFT 				(4U)
#define LPUART_CTRL_PE_SHIFT 			  (1U)
#define LPUART_CTRL_RIE_SHIFT 			(21U)
#define LPUART_CTRL_ILIE_SHIFT 		  (20U)
#define LPUART_CTRL_IDLECFG_SHIFT 	(8U)
#define LPUART_CTRL_ILT_SHIFT 			(2U)
#define LPUART_CTRL_TE_SHIFT 			  (19U)
#define LPUART_CTRL_RE_SHIFT 			  (18U)
#define LPUART_STAT_IDLE_SHIFT 		  (20U)
#define LPUART_STAT_TDRE_SHIFT 		  (23U)
#define LPUART_STAT_RDRF_SHIFT 		  (21U)
/** Peripheral LPSPI base address */
#define LPUART0_base_address (0x4006A000U)
#define LPUART1_base_address (0x4006B000U)
#define LPUART2_base_address (0x4006C000U)
#define LPUART0              ((LPUART_Type*)LPUART0_base_address)
#define LPUART1              ((LPUART_Type*)LPUART1_base_address)
#define LPUART2              ((LPUART_Type*)LPUART2_base_address)

/*==================================================================================================
*                                           STRUCTURES 
==================================================================================================*/
/** 
 * @struct LPUART_Type
 * @brief Structure representing the LPUART register layout.
 * 
 * This structure contains all the registers required to control and monitor the 
 * LPUART peripheral. Each field corresponds to a specific register in the 
 * LPUART hardware and is defined as volatile to ensure correct access in a 
 * concurrent environment.
 */
/** LPUART - Register Layout Typedef */
typedef struct {
  volatile unsigned int VERID;
  volatile unsigned int PARAM;
  volatile unsigned int GLOBAL;
  volatile unsigned int PINCFG;
  volatile unsigned int BAUD;
  volatile unsigned int STAT;
  volatile unsigned int CTRL;
  volatile unsigned int DATA;
  volatile unsigned int MATCH;
  volatile unsigned int MODIR;
  volatile unsigned int FIFO;
  volatile unsigned int WATER;
} LPUART_Type;


#endif

