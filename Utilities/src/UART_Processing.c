/**
 * @file    UART_Processing.c
 * @brief   UART data processing for date and time settings
 * @details This module handles the reception of data from the UART interface, 
 *          processes the data to set date and time, and validates the input format. 
 *          It includes functions to check formats, reset data, and update time/date values.
 *
 * @version 1.0
 * @date    2024-10-09
 * @author  Mai Anh Tuan
 */
 /*==================================================================================================
*                                       INCLUDE FILE
==================================================================================================*/
#include "UART_Processing.h"

 /*==================================================================================================
*                                       LOCAL VARIABLES
==================================================================================================*/
static unsigned char received_data[MAX_LENGHT];
static unsigned char count_input_data=0;
static unsigned char Setting_Date_String[20] = "Setting Date:"; 
static unsigned char Setting_Time_String[20] = "Setting Time:"; 
 /*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void receive_data(void)
{
	/* Receive data from LPUART1 and store it in the received_data array */
	Lpuart_Receive(LPUART1, &received_data[count_input_data]);
	count_input_data++;
	/* Reset count_input_data if it exceeds MAX_LENGTH */
	if (count_input_data > MAX_LENGHT)
	{
		count_input_data=0;
	}
	else
	{
		/*do not thing*/
	}
}

void reset_data(volatile unsigned char *str)
{
	/* Reset the input data counter */
	count_input_data=0;
	/* Clear the string buffer by setting all elements to null */
	for (int i=0; i< MAX_LENGHT;i++)
	{
		*(str+i) = '\0';
	}
}

void reset_received_data(void)
{
	reset_data(received_data);
}

void print_Output(char *str)
{
	/* Get the length of the input string */
	static int length;
	length = my_strlen(str);
	/* Transmit the string via LPUART */
	Lpuart_Transmit(LPUART1,(unsigned char*) str, (unsigned char)length);
}


void process_setting(volatile unsigned char *state_set)
{	
	/* Compare the received data to predefined setting strings */
	if (stringcompare(received_data,Setting_Date_String))
	{
		/* Set the state to SET_DATE if the date string is matched */
		*state_set = SET_DATE;
	}
	else if (stringcompare(received_data, Setting_Time_String))
	{
		 /* Set the state to SET_TIME if the time string is matched */
		*state_set = SET_TIME;
	}
	else 
	{
		 /* Set the state to NOT_SETTING if no match is found */
		*state_set = NOT_SETTING;
	}
}

unsigned char Check_Date_Format(void)
{	
	if (Check_Format_Setting_Date((char*)received_data))
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

unsigned char Check_Time_Format(void)
{
	if (Check_Format_Setting_Time((char*)received_data))
	{
		return TRUE;
	}
	else 
	{
		return FALSE;
	}
}

void Update_Date(unsigned char *day, unsigned char *month, unsigned short *year)
{
	/* Temporary buffer to store the received date string */
	char temp[11]; 
	char *token;
	/* Copy the received data into the temporary buffer */
  my_strcpy(temp, (char*)received_data);
	/* Tokenize the date string by using '.' as a delimiter and extract day, month, and year */
  token = my_strtok(temp, ".");
	/* Convert the extracted day string to unsigned char */
  *day = my_atouchar(token);
  /* Get the next token for the month and convert it */
  token = my_strtok(NULL, ".");
  *month = my_atouchar(token);
	/* Get the next token for the year and convert it */
  token = my_strtok(NULL, ".");
  *year = my_atoushort(token);
}


void Update_Time(unsigned char *second, unsigned char *minute, unsigned char *hour)
{
	/* Temporary buffer to store the received time string */
	char temp[9]; 
  char *token;
	/* Copy the received data into the temporary buffer */
  my_strcpy(temp, (char*)received_data);
	/* Tokenize the time string by using '-' as a delimiter and extract hour, minute, and second */
  token = my_strtok(temp, "-");
	/* Convert the extracted hour string to unsigned char */
  *hour = my_atouchar(token);
	/* Get the next token for the minute and convert it */
  token = my_strtok(NULL, "-");
  *minute = my_atouchar(token);
	/* Get the next token for the second and convert it */
  token = my_strtok(NULL, "-");
  *second = my_atouchar(token);
}


