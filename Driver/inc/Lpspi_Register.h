/**
 * @file    Lpspi_Register.h
 * @brief   Low Power Serial Peripheral Interface (LPSPI) register definitions.
 * @details This header file defines the register layout and macros for controlling 
 *          the LPSPI peripheral. The LPSPI is a serial communication interface used 
 *          for full-duplex communication with various peripherals.
 *
 * @note    The LPSPI supports multiple configurations such as clock polarity, 
 *          clock phase, frame size, and other operational settings.
 *
 * @version 1.0
 * @date    2024-10-09
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
==================================================================================================*/
#ifndef LPSPI_REG_H
#define LPSPI_REG_H
/*==================================================================================================
*                                       MACRO DEFINITIONS
==================================================================================================*/
#define LPSPI_TCR_CPOL_SHIFT                     (31u)
#define LPSPI_TCR_CPHA_SHIFT                     (30u)
#define LPSPI_TCR_PRESCALE_SHIFT                 (27u)
#define LPSPI_TCR_FRAMESZ_SHIFT                  (0u)
#define LPSPI_TCR_LSBF_SHIFT                     (23u)
#define LPSPI_TCR_PCS_SHIFT                      (24u)
#define LPSPI_CCR_SCKDIV_SHIFT                   (0u)
#define LPSPI_FCR_RXWATER_SHIFT                  (16u)
#define LPSPI_FCR_TXWATER_SHIFT                  (0u)
#define LPSPI_CFGR1_NOSTALL_SHIFT                (3u)
#define LPSPI_CFGR1_MASTER_SHIFT                 (0u)
#define LPSPI_CR_DGGEN_SHIFT                     (3u)
#define LPSPI_CR_MEN_SHIFT                       (0u)
#define TRANSMIT_IS_REQUESTED                    (1u)
#define LPSPI_SR_TDF_SHIFT                       (0u)
#define LPSPI_TCR_FRAMESZ_MASK   								 (0xFFF)  
/** Peripheral LPSPI base address */
#define LPSPI0_base_address  (0x4002C000u)
#define LPSPI1_base_address  (0x4002D000u)
#define LPSPI2_base_address  (0x4002E000u)
#define LPSPI0                                   ((LPSPI_Type *)LPSPI0_base_address)
#define LPSPI1                                   ((LPSPI_Type *)LPSPI1_base_address)
#define LPSPI2                                   ((LPSPI_Type *)LPSPI2_base_address)

/*==================================================================================================
*                                           STRUCTURES 
==================================================================================================*/
/**
 * @struct LPSPI_Type
 * @brief  LPSPI Register Layout Structure.
 * @details This structure defines the register layout for the LPSPI peripheral, 
 *          including control, status, and data registers.
 */
typedef struct {
  volatile const  unsigned int VERID;
  volatile const  unsigned int PARAM;
  volatile unsigned char RESERVED_0[8];
  volatile unsigned int CR;
  volatile unsigned int SR;
  volatile unsigned int IER;
  volatile unsigned int DER;
  volatile unsigned int CFGR0;
  volatile unsigned int CFGR1;
  volatile unsigned char RESERVED_1[8];
  volatile unsigned int DMR0;
  volatile unsigned int DMR1;
  volatile unsigned char RESERVED_2[8];
  volatile unsigned int CCR;
  volatile unsigned char RESERVED_3[20];
  volatile unsigned int FCR;
  volatile const  unsigned int FSR;
  volatile unsigned int TCR;
  volatile unsigned int TDR;
  volatile unsigned char RESERVED_4[8];
  volatile const  unsigned int RSR;
  volatile const  unsigned int RDR;
} LPSPI_Type;


#endif

