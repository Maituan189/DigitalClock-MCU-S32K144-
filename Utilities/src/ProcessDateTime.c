/**
 * @file    ProcessDateTime.c
 * @brief   Date and Time Processing Functions
 * @details This file contains functions to manage date and time calculations, including leap year 
 *          determination and days in a month. It also provides functionality to update the current
 *          day, month, hour, minute, and second.
 *
 * @version 1.0
 * @date    2024-10-09
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
*                                       INCLUDE FILE
==================================================================================================*/
#include "ProcessDateTime.h"
/*==================================================================================================
*                                       LOCAL FUNCTIONS PROTOTYPE
==================================================================================================*/
static unsigned char is_leap_year(unsigned short Year);
static unsigned char days_in_month(unsigned char Month, unsigned short Year);
/*==================================================================================================
*                                       LOCAL FUNCTIONS
==================================================================================================*/
static unsigned char is_leap_year(unsigned short Year)
{  
	  /* A year is a leap year if it is divisible by 4 but not by 100,
    or if it is divisible by 400.*/
    if ((Year%4==0 && Year%100!=0)||(Year%400==0))
    {
      return 1;
			/* Return 1 (TRUE) if it's a leap year */
    }
    else 
    {
      return 0;
			/* Return 0 (FALSE) if it's NOT a leap year */
    }
}
static unsigned char days_in_month(unsigned char Month, unsigned short Year)
{ 
    unsigned char Day;
	  /* Determine the number of days based on the month */
    switch(Month)
    {
        case 1: case 3: case 5: case 7: case 8: case 10: case 12: Day = 31; break;
        case 2: if(is_leap_year(Year)) Day = 29; else {Day = 28;} break;            
        case 4: case 6:case 9: case 11: Day = 30; break;
        default: Day=0; break;
    }
		/* Return the number of days in the month */
    return Day;
}
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
void Date(unsigned char *day_update)
{
	/* Check if the current day exceeds the number of days in the current month */
	if (*day_update > days_in_month(month, year))
	{
		/* Reset day to 1 */
		*day_update = 1;
		/* Move to the next month */
		month++;
	}
	else 
	{
		/*do not thing*/
	}
	/* Check if the month exceeds 12 (December) */
	if (month>12)
	{
		/* Increment the year */
		year++;
		/* Reset month to January */
		month=1;
	}
}

void Time(unsigned char *second_update)
{
	/* Check if seconds equal 60 */
	if (*second_update==60)
	{
		 /* Increment minute */
		minute++;
		/* Reset seconds to 0 */
		*second_update = 0;
	}
	else
	{
		/*do not thing*/
	}
	 /* Check if minutes equal 60 */
	if (minute==60)
	{
		/* Increment hour */
		hour++;
		/* Reset minutes to 0 */
		minute=0;
	}
	else
	{
		/*do not thing*/
	}
	/* Check if hour equals 24 */
	if (hour==24)
	{
		/* Reset hour to 0 */
		hour = 0 ;
		/* Increment day */
		day++;
	}
	else
	{
		/*do not thing*/
	}
}


