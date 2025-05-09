/**
 * @file    Lpit_Register.h
 * @brief   Clock Register Definitions for the Low Power Interval Timer (LPIT).
 * @details This file contains register definitions and macros for configuring
 *          the Low Power Interval Timer (LPIT) peripheral. The LPIT is used 
 *          for generating periodic interrupts, with various control and status 
 *          registers accessible via this file.
 *          
 * @note    The LPIT module provides timer channels that can be individually 
 *          configured. Each channel contains its own counter and control 
 *          registers. This file facilitates access and manipulation of these 
 *          registers.
 *
 * @version 1.0
 * @date    2024-10-20
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
==================================================================================================*/
#ifndef LPIT_REG_H
#define LPIT_REG_H
/*==================================================================================================
*                                MACRO DEFINE
==================================================================================================*/
#define LPIT_MCR_M_CEN_SHIFT        (0u)
#define LPIT_MCR_DBG_EN_SHIFT       (3u)
#define LPIT_TMR_TCTRL_T_EN_SHIFT   (0u)
#define LPIT_TMR_TCTRL_MODE_SHIFT   (2u)
#define LPIT_TMR_COUNT              (4u)
#define LPIT_CHANNEL_0              (0u)
#define LPIT_CHANNEL_1              (1u)
#define LPIT_CHANNEL_2              (2u)
#define LPIT_CHANNEL_3              (3u)
#define ENABLE_LPIT                 (1u)
#define DISABLE_LPIT                (0u)
#define MAX_TAVL_VALUE              (0xFFFFFFFFu)
/** Peripheral LPIT0 base address */
#define LPIT0_BASE_ADDRESS                              (0x40037000u)
/** Peripheral LPIT0 base pointer */
#define LPIT0                                    ((LPIT_Type *)LPIT0_BASE_ADDRESS)
/*==================================================================================================
*                                STRUCTURES AND ENUM
==================================================================================================*/
/**
 * @struct LPIT_Type
 * @brief Structure defining the register layout of the LPIT peripheral.
 * 
 * @details The LPIT_Type structure contains various registers for configuring
 *          and controlling the LPIT module, including control and status registers,
 *          as well as individual timer channel registers for managing timer 
 *          functionality.
 */
typedef struct 
{
	volatile unsigned int VERID;
	volatile unsigned int PARAM;                          
  volatile unsigned int MCR;                            
  volatile unsigned int MSR;                            
  volatile unsigned int MIER;                           
  volatile unsigned int SETTEN;                         
  volatile unsigned int CLRTEN;
	volatile unsigned int RESERVED_0;
  
  struct 
  {                                         
    volatile unsigned int TVAL;                    
    volatile unsigned int CVAL;                    
    volatile unsigned int TCTRL;                   
    volatile unsigned int RESERVED_0;
  } TMR[LPIT_TMR_COUNT];	

} LPIT_Type;



#endif
