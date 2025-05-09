/**
 * @file    Lpspi.h
 * @brief   LPSPI Driver for Initialization and Data Transmission.
 * @details This header file contains the necessary data structures and function 
 *          declarations for configuring and operating the Low Power Serial Peripheral Interface (LPSPI).
 *
 * @version 1.0
 * @date    2024-10-09
 * @author  Mai Anh Tuan
 */

#ifndef LPSPI_H
#define LPSPI_H
/*==================================================================================================
*                                       INCLUDE FILE
==================================================================================================*/
#include "Lpspi_Register.h"
/*==================================================================================================
*                                    ENUMERATIONS
==================================================================================================*/
/**
 * @enum spi_clock_polarity_t
 * @brief Defines the clock polarity (CPOL) options for SPI communication.
 */
typedef enum
{
    SPI_CPOL_0  = 0U,  
    SPI_CPOL_1  = 1U,   
} spi_clock_polarity_t;

/**
 * @enum spi_clock_phase_t
 * @brief Defines the clock phase (CPHA) options for SPI communication.
 */
typedef enum
{
    SPI_CPHA_0  = 0U,  
    SPI_CPHA_1  = 1U  
} spi_clock_phase_t;

/**
 * @enum spi_peripheral_chip_select_t
 * @brief Defines the peripheral chip select (PCS) options for SPI communication.
 */
typedef enum
{
    LPSPI_PCS_0  = 0U,  
    LPSPI_PCS_1  = 1U,  
		LPSPI_PCS_2  = 2U,  
    LPSPI_PCS_3  = 3U  
} spi_peripheral_chip_select_t;

/**
 * @enum spi_frame_size_t
 * @brief Defines the frame size options for SPI communication.
 */
typedef enum
{
    LPSPI_FRAME_8  = 7U,  
    LPSPI_FRAME_16  = 15U,  
		LPSPI_FRAME_32  = 31U,   
} spi_frame_size_t;

/**
 * @enum spi_type_transfer_t
 * @brief Defines the type of data transfer (MSB first or LSB first).
 */
typedef enum
{
    LPSPI_MSB_FIRST  = 0U,  
    LPSPI_LSB_FIRST  = 1U    
} spi_type_transfer_t;

/**
 * @enum spi_prescaler_t
 * @brief Defines the prescaler options for the SPI clock.
 */
typedef enum
{
    LPSPI_PRE_DIV_BY_1   = 0U,  
    LPSPI_PRE_DIV_BY_2   = 1U,
    LPSPI_PRE_DIV_BY_4   = 2U,
    LPSPI_PRE_DIV_BY_8   = 3U,
    LPSPI_PRE_DIV_BY_16  = 4U,
    LPSPI_PRE_DIV_BY_32  = 5U,
    LPSPI_PRE_DIV_BY_64  = 6U,
    LPSPI_PRE_DIV_BY_128 = 7U
} spi_prescaler_t;

/*==================================================================================================
*                                    STRUCTURE DEFINITIONS
==================================================================================================*/
/**
 * @struct LPSPIT_InitType
 * @brief  Configuration structure for LPSPI initialization.
 * @details This structure contains the parameters necessary for initializing the LPSPI peripheral.
 */
typedef struct
{
unsigned int                  F_lpspi;      /* Clock supply for LPSPI */
unsigned int                  spi_speed; 
unsigned int                  spi_sck_div; 
spi_prescaler_t               spi_prescaler;
spi_type_transfer_t     	  	spi_type_transfer;
spi_frame_size_t              spi_frame;
spi_clock_polarity_t          spi_cpol;
spi_clock_phase_t             spi_cpha;
spi_peripheral_chip_select_t  spi_pcs;
unsigned char padding[2]; 
}LPSPIT_InitType;

/**
 * @struct Lpspi_ConfigType
 * @brief  Configuration structure for LPSPI operations.
 * @details This structure contains the configuration and buffer information 
 *          necessary for LPSPI data transmission.
 */
typedef struct
{
	LPSPI_Type *pSPIx;
	LPSPIT_InitType Init;
	unsigned char *pTxBuffer;
	unsigned char *pRxBuffer;  /* Reserve */
	unsigned short TxLen;
	unsigned short RxLen;	   /* Reserve */
}Lpspi_ConfigType;

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief  Initializes the LPSPI peripheral with the specified configuration.
 * @param[in] ConfigPtr Pointer to the configuration structure (Lpspi_ConfigType).
 * @return None.
 */
void Lpspi_Init (const Lpspi_ConfigType* ConfigPtr);
/**
 * @brief  Transmits data via the LPSPI peripheral.
 * @param[in] pLpspi Pointer to the LPSPI peripheral.
 * @param[in] pTxBuffer Pointer to the data buffer to be transmitted.
 * @param[in] Size Size of the data to be transmitted.
 * @return None.
 */
void Lpspi_Transmit(LPSPI_Type *pLpspi, unsigned short *pTxBuffer, unsigned short Size);


#endif /* LPSPI_H */


