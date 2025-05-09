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
#ifndef MAX7219_H
#define MAX7219_H
/*==================================================================================================
*                                       INCLUDE FILE
==================================================================================================*/
#include "Config.h"
/*==================================================================================================
*                                    MACRO DEFINITIONS
==================================================================================================*/
#define NORMAL_MODE 					0x0C01
#define SHUTDOWN_MODE 				0x0C00
#define NONE_DISPLAY_TEST 		0x0F00
#define DECODE_ALL_DIGITS 		0x09FF
#define SCAN_LIMIT_ALL_DIGITS 0x0B07
#define INTENSITY_REG 				0x0A00
#define LED_0									0x0100
#define LED_1									0x0200
#define LED_2									0x0300
#define LED_3									0x0400
#define LED_4									0x0500
#define LED_5									0x0600
#define LED_6									0x0700
#define LED_7									0x0800 			 				
/*==================================================================================================
*                                    GLOBLA VARIABLES
==================================================================================================*/
extern unsigned short ADC_Value;
/**
 * @brief Initializes the MAX7219 display.
 *
 * This function configures the MAX7219 for normal operation,
 * disables the display test, sets the scan limit to display all digits,
 * and sets the decode mode for all digits.
 */
void Init_MAX7219(void);

/**
 * @brief Displays time on the MAX7219.
 *
 * @param second The current second (0-59).
 * @param minute The current minute (0-59).
 * @param hour   The current hour (0-23).
 */
void Display_Time(unsigned char second, unsigned char miniute, unsigned char hour);

/**
 * @brief Displays date on the MAX7219.
 *
 * @param day   The current day (1-31).
 * @param month The current month (1-12).
 * @param year  The current year (e.g., 2024).
 */
void Display_Date(unsigned char day, unsigned char month, unsigned short year);

/**
 * @brief Controls the display intensity based on an ADC value.
 *
 * @param ADC_value The ADC value (0-4095) to set the intensity.
 */
void Control_Intensity(unsigned short ADC_value);

/**
 * @brief Turns off the MAX7219 display.
 *
 * This function sets the MAX7219 to shutdown mode, turning off the display.
 */
void Turn_Off_Display(void);

/**
 * @brief Turns on the MAX7219 display.
 *
 * This function sets the MAX7219 to normal mode, turning on the display.
 */
void Turn_On_Display(void);

#endif
