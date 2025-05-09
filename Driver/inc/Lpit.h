/**
 * @file    Lpit.h
 * @brief   Low Power Interval Timer (LPIT) driver interface.
 * @details This file provides function declarations and data structures used 
 *          to configure and control the LPIT peripheral. It includes functions 
 *          to initialize the timer, start and stop timer channels, and retrieve 
 *          timer counter values.
 *
 * @note    The LPIT supports multiple channels, each of which can be configured 
 *          individually for different timing operations, including periodic 
 *          interrupts.
 *
 * @version 1.0
 * @date    2024-10-20
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
==================================================================================================*/
#ifndef LPIT_H
#define LPIT_H
/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Lpit_Register.h"
/*==================================================================================================
*                                STRUCTURES AND ENUM
==================================================================================================*/
/**
 * @struct Lpit_ChannelConfigType
 * @brief  Configuration structure for LPIT timer channels.
 * 
 * @details This structure holds the configuration parameters for an LPIT timer channel, 
 *          such as the period and whether interrupt generation is enabled.
 */
typedef struct
{
    unsigned int period;                        /*!< Period of timer channel                     */
    unsigned char isInterruptEnabled;           /*!< Timer channel interrupt generation enable   */
		unsigned char padding[3];
} Lpit_ChannelConfigType;

/**
 * @brief   Initializes the LPIT module.
 * 
 * @details This function performs the basic initialization of the LPIT module, 
 *          setting it up for further configuration of individual timer channels.
 *
 * @return  None.
 */
void Lpit_Init( void );

/**
 * @brief   Configures a specific LPIT channel.
 * 
 * @details This function initializes a timer channel of the LPIT with the provided 
 *          configuration settings, such as the period and interrupt enable state.
 *
 * @param[in] channel     Channel number to initialize.
 * @param[in] ConfigPtr   Pointer to the configuration structure for the channel.
 *
 * @return  None.
 */
void Lpit_InitChannel(unsigned char channel, const Lpit_ChannelConfigType* ConfigPtr);

/**
 * @brief   Starts a specific LPIT timer channel.
 * 
 * @details This function enables the timer for the specified channel, starting 
 *          the countdown based on the period set during initialization.
 *
 * @param[in] channel     Channel number to start.
 *
 * @return  None.
 */
void Lpit_StartChannel(unsigned char channel);

/**
 * @brief   Stops a specific LPIT timer channel.
 * 
 * @details This function stops the timer for the specified channel, halting 
 *          any further counting.
 *
 * @param[in] channel     Channel number to stop.
 *
 * @return  None.
 */
void Lpit_StopChannel(unsigned char channel);

/**
 * @brief   Retrieves the current counter value of a specific LPIT channel.
 * 
 * @details This function returns the current value of the counter for the 
 *          specified timer channel.
 *
 * @param[in] channel     Channel number to get the counter value from.
 *
 * @return  The current counter value of the specified channel.
 */
unsigned int Lpit_GetCounterChannel(unsigned char channel);

/**
 * @brief   Clears the interrupt flag for a specific LPIT channel.
 * 
 * @details This function clears the interrupt flag for the specified LPIT 
 *          timer channel, allowing new interrupts to be triggered.
 *
 * @param[in] channel     Channel number to clear the interrupt flag for.
 *
 * @return  None.
 */
void Lpit_Clear_Interrupt_Flag (unsigned char channel);

#endif
