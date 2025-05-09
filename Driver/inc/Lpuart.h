/**
 * @file    Lpuart.h
 * @brief   LPUART Driver for Initialization and Data Transmission.
 * @details This header file contains the necessary data structures and function 
 *          declarations for configuring and operating the LPUART.
 *
 * @version 1.0
 * @date    2024-10-20
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
==================================================================================================*/
#ifndef LPUART_H
#define LPUART_H
/*==================================================================================================
*                                       INCLUDE FILE
==================================================================================================*/
#include "Lpuart_Register.h"
/*==================================================================================================
*                                    ENUMERATIONS
==================================================================================================*/
/**
 * @brief Enum for UART oversampling ratios.
 *
 * Specifies the oversampling ratio used for UART communication.
 */
typedef enum
{
    oversampling_ratio_16_ = 0U,
    oversampling_ratio_4  = 3U,
    oversampling_ratio_5  = 4U,
    oversampling_ratio_6  = 5U,
    oversampling_ratio_7  = 6U,
    oversampling_ratio_8  = 7U,
    oversampling_ratio_9  = 8U,
    oversampling_ratio_10 = 9U,
    oversampling_ratio_11 = 10U,
    oversampling_ratio_12 = 11U,
    oversampling_ratio_13 = 12U,
    oversampling_ratio_14 = 13U,
    oversampling_ratio_15 = 14U,
    oversampling_ratio_16 = 15U,
    oversampling_ratio_17 = 16U
} uart_oversampling_ratio_t;

/**
 * @brief Enum for UART stop bit configuration.
 *
 * Specifies the number of stop bits used in UART communication.
 */
typedef enum
{
    ONE_STOP_BIT = 0U,
    TWO_STOP_BIT = 1U
} uart_stop_bit_number_t;

/**
 * @brief Enum for LPUART frame size.
 *
 * Specifies the size of the data frame in UART communication.
 */
typedef enum
{
    FRAME_8_BIT = 0U,
    FRAME_9_BIT = 1U
}lpuart_frame_size_t;

/**
 * @brief Enum for data transfer type.
 *
 * Specifies the order of data transmission in UART communication.
 */
typedef enum
{
    LPUART_MSB_FIRST  = 0U,  
    LPUART_LSB_FIRST  = 1U    
} uart_type_transfer_t;

/**
 * @brief Enum for UART parity bit configuration.
 *
 * Specifies whether parity bit is enabled or disabled in UART communication.
 */
typedef enum
{
    LPUART_ENABLE_PARITY_BIT  = 1U,  
    LPUART_DISABLE_PARITY_BIT  = 0U    
} uart_parity_bit_enable_t;

/**
 * @brief Enum for idle character configurations.
 *
 * Specifies the number of idle characters in UART communication.
 */
typedef enum
{
    IDLE_CHARACTER_1   = 0U,
    IDLE_CHARACTER_2   = 1U,
    IDLE_CHARACTER_4   = 2U,
    IDLE_CHARACTER_8   = 3U,
    IDLE_CHARACTER_16  = 4U,
    IDLE_CHARACTER_32  = 5U,
    IDLE_CHARACTER_64  = 6U,
    IDLE_CHARACTER_128 = 7U
} uart_character_idl;

/**
 * @brief Enum for idle character counting method.
 *
 * Specifies whether counting starts from the start bit or stop bit.
 */
typedef enum
{
    COUNT_FROM_START_BIT = 0U,
    COUNT_FROM_STOP_BIT = 1U
} uart_idl_type;

/*==================================================================================================
*                                    STRUCTURE DEFINITIONS
==================================================================================================*/
/**
 * @brief Structure for LPUART initialization parameters.
 *
 * Contains settings for initializing the LPUART peripheral, including baud rate,
 * oversampling ratio, stop bits, frame size, parity, and idle character configurations.
 */
typedef struct
{
    unsigned char lpuart_enable_int_TX; /*reserve*/
    unsigned char lpuart_enable_int_RX;
    unsigned char lpuart_enable_idl;
	unsigned char padding_1;
    unsigned int lpuart_baudrate_modulo_divisor;
    uart_oversampling_ratio_t lpuart_oversampling;
    unsigned char padding_2[2];
    uart_stop_bit_number_t lpuart_stop_bit;
    lpuart_frame_size_t lpuart_data_frame;
    uart_parity_bit_enable_t lpuart_parity_bit;
    uart_character_idl lpuart_number_character_idl;
    uart_idl_type   lpuart_type_select_idl;
}LPUART_InitType;

/**
 * @brief Structure for LPUART configuration.
 *
 * Contains a pointer to the LPUART peripheral and the initialization settings.
 */
typedef struct
{
	LPUART_Type *pUARTx;
	LPUART_InitType Init;
}Lpuart_ConfigType;

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
/**
 * @brief Initializes the LPUART peripheral.
 *
 * Configures the LPUART according to the parameters specified in the configuration structure.
 * Sets up baud rate, oversampling ratio, stop bits, frame size, parity, and interrupt settings.
 *
 * @param ConfigPtr Pointer to the configuration structure containing the initialization parameters.
 */
void Lpuart_Init (const Lpuart_ConfigType* ConfigPtr);

/**
 * @brief Transmits data using the LPUART.
 *
 * Sends a buffer of data via the LPUART peripheral.
 *
 * @param pUartx Pointer to the LPUART peripheral.
 * @param pTxBuffer Pointer to the data buffer to be transmitted.
 * @param size Size of the data buffer.
 */
void Lpuart_Transmit(LPUART_Type *pUartx, unsigned char *pTxBuffer, unsigned char size);

/**
 * @brief Receives data using the LPUART.
 *
 * Reads a buffer of data from the LPUART peripheral.
 *
 * @param pUartx Pointer to the LPUART peripheral.
 * @param pRxBuffer Pointer to the buffer where received data will be stored.
 */
void Lpuart_Receive(LPUART_Type *pUartx, unsigned char *pRxBuffer);

#endif /* LPUART_H */

