/**
 * @file  	MAX7219.c
 * @brief 	MAX7219 Driver Functions
 * @details This file contains the implementation of functions to control the MAX7219 LED driver,
 *          including initialization, displaying time and date, controlling display intensity, 
 *          and turning the display on or off.
 *
 * @version 1.0
 * @date    2024-10-09
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
*                                       INCLUDE FILE
==================================================================================================*/
#include "MAX7219.h"
/*==================================================================================================
*                                       GLOBAL FUNCTION
==================================================================================================*/
void Init_MAX7219(void)
{
	/* Array to hold initialization commands for the MAX7219 */
	unsigned short Init[4]= {NORMAL_MODE, NONE_DISPLAY_TEST, SCAN_LIMIT_ALL_DIGITS, DECODE_ALL_DIGITS};
	/* Transmit the initialization commands to the MAX7219 via SPI */
	Lpspi_Transmit(LPSPI1,Init,4);
}

void Display_Time(unsigned char second, unsigned char minute, unsigned char hour)
{
	 /* Array to hold data for displaying time; calculates LED values for seconds, minutes, and hours */
	unsigned short Data_Time[8]={(LED_0 + (second%10))
															, (LED_1 + (second/10))
															, (LED_2 + 10)
															, (LED_5 + 10)
															, (LED_3 + (minute%10))
															, (LED_4 + (minute/10))
															, (LED_6 + (hour%10))
															, (LED_7 + (hour/10))};
	/* Transmit the time data to the MAX7219 via SPI */
	Lpspi_Transmit(LPSPI1,Data_Time,8);
}

void Display_Date(unsigned char day, unsigned char month, unsigned short year)
{
	 /* Array to hold data for displaying date; includes bit manipulation for indicators */
	unsigned short Data_Date[8]={((LED_6 + (day%10)) | (1U<<7))
															, (LED_7 + (day/10))
															, ((LED_4 + (month%10)) | (1U<<7))
															, (LED_5 + (month/10))
															, (LED_0 + (year%10))
															, (LED_1 + ((year/10)%10))
															, (LED_2 + ((year/100)%10))
															, (LED_3 + (year/1000))};
	/* Transmit the date data to the MAX7219 via SPI */
	Lpspi_Transmit(LPSPI1,Data_Date,8);
}

void Control_Intensity(unsigned short ADC_value)
{
	/* Calculate the intensity level based on the ADC value */
	unsigned short Level= INTENSITY_REG + (ADC_value*15)/4096;
	/* Transmit the intensity level to the MAX7219 via SPI */
	Lpspi_Transmit(LPSPI1,&Level,1);
}

void Turn_Off_Display(void)
{
	/* Set to shutdown mode */
	unsigned short Shut_Down_Mode = SHUTDOWN_MODE;
	/* Transmit the shutdown command to the MAX7219 via SPI */
	Lpspi_Transmit(LPSPI1,&Shut_Down_Mode,1);
}

void Turn_On_Display(void)
{
	/* Set to normal mode */
	unsigned short Normal_Mode = NORMAL_MODE;
	/* Transmit the normal mode command to the MAX7219 via SPI */
	Lpspi_Transmit(LPSPI1,&Normal_Mode,1);
}


