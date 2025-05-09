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
#ifndef UART_PROCESSING_H
#define UART_PROCESSING_H
/*==================================================================================================
*                                       MACRO DEFINITIONS
==================================================================================================*/
#define MAX_LENGHT 					 20
#define NOT_SETTING 				 0
#define SET_DATE 						 2
#define SET_TIME 						 1
#define START_SETTING 			 4
#define INPUT_COMPLETE  		 1
#define INPUT_NONE_COMPLETE  0
/*==================================================================================================
*                                       INCLUDE FILES
==================================================================================================*/
#include "String.h"
#include "Config.h"
/*==================================================================================================
*                                       GLOBAL VARIABLES
==================================================================================================*/
extern unsigned char Error_String[20]; 
extern unsigned char Date_Updated_Str[20];
extern unsigned char Time_Updated_Str[20];
extern unsigned char Time_Format_Str[40];
extern unsigned char Date_Format_Str[40];
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void print_error_string(void);
void reset_received_data(void);
void receive_data(void);
void reset_data(volatile unsigned char *str);
void process_setting(volatile unsigned char *state_set);
unsigned char Check_Date_Format(void);
unsigned char Check_Time_Format(void);
void Update_Date(unsigned char *day, unsigned char *month, unsigned short *year);
void Update_Time(unsigned char *second, unsigned char *minute, unsigned char *hour);
void print_Date_Updated_Str(void);
void print_Time_Updated_Str(void);
void print_Output(char *str);


#endif



