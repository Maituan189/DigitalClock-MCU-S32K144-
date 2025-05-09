/**
 * @file  	main.c  
 * @brief   Implement algorithims and run tasks on Board
 * @details All task will be implemented on IRQ handlers
 *          In the main function, there is only configuration function
 *
 * @requirement 
 * SRS 1: After power on, display the time: 00-00-00 (date: 01.01.1971)
 * SRS 2: Press Button 1
 * - SRS 2-1: Display the date
 * - SRS 2-2: Display the time
 * SRS 3: Press Button 2
 * - SRS 3-1: Turn off the display mode
 * - SRS 3-2: Turn on the display mode
 * SRS4: Setting date, time by UART serial communication
 * SRS5: Use potentiometer to control the brightness of LED display(Opt)
 *
 * @version 1.0
 * @date    2024-10-09
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "String.h"
#include "Config.h"
#include "MAX7219.h"
#include "UART_Processing.h"
#include "ProcessDateTime.h"
/*==================================================================================================
*                                FUNCTION PROTOTYPES
==================================================================================================*/
void PORTC_IRQHandler(void);
void LPUART1_RxTx_IRQHandler(void);
void LPIT0_Ch3_IRQHandler(void);
void ADC0_IRQHandler (void);
/*==================================================================================================
*                                GLOBAL VARIALBES
==================================================================================================*/
volatile static unsigned char input_complete;
volatile static unsigned char State_Button1=DISPLAY_TIME_MODE;
volatile static unsigned char State_Button2=TURNON_DISPLAY_MODE;
volatile static unsigned char State_Set = 0;
volatile static unsigned char count=0;
volatile static unsigned char State_Display;
unsigned char second=0,minute=0,hour=0,day=1,month=1;
unsigned short year=1971;
unsigned short ADC_Value;
unsigned char Error_String[] = "Error_Format\n"; 
unsigned char Date_Updated_Str[] = "\nDate Updated\n";
unsigned char Time_Updated_Str[] = "\nTime Updated\n";
unsigned char Time_Format_Str[] = "\nPlease type right format: XX-XX-XX\n";
unsigned char Date_Format_Str[] = "\nPlease type right format: dd.mm.yyyy\n";
/*==================================================================================================
*                                MAIN FUNCTION
==================================================================================================*/
int main(void)
{
	/*Function to configure overall system*/
	Config_System();
	/*Function to init module MAX*/
	Init_MAX7219();
	while(1)
	{
		/*empty*/
	}
}

void PORTC_IRQHandler(void)
{
	/* Check interrupt flag of Pin12-PortC(Button1) */
	if(PORTC->PCR[12] & (1<<24))
	{
		/* Clear interrupt flag */
		PORTC->PCR[12] |= (1<<24);
		/* Toggle state of button 1 */
		State_Button1++;
		if (State_Button1 > DISPLAY_TIME_MODE)
		{
			State_Button1 = DISPLAY_DATE_MODE;
		}
	}
	/* Check interrupt flag of Pin13-PortC(Button2) */
	else if (PORTC->PCR[13] & (1<<24))
	{
		/* Clear interrupt flag */
		PORTC->PCR[13] |= (1<<24);
		/* Toggle state of button 2 */
		State_Button2++;
		if (State_Button2 > TURNON_DISPLAY_MODE)
		{
			State_Button2 = TURNOFF_DISPLAY_MODE;
		}
	}
	else 
	{
		/*do not empty*/
	}
}

void LPUART1_RxTx_IRQHandler(void)
{
	/* Check idle flag */
	if (((LPUART1->STAT >> LPUART_STAT_IDLE_SHIFT)&0x01))  
	{
		/* Clear the interrupt flag */
		LPUART1->STAT |=(1U<<LPUART_STAT_IDLE_SHIFT);			
		/* Set the flag indicating input is complete */		
		input_complete = INPUT_COMPLETE;											
	}
	else 
	{
		/*do not thing*/
	}
	/*Function to receive buffer data*/
	receive_data();
	/*Check input complete or not*/
	if((input_complete == INPUT_COMPLETE))
		{
			/*Check state set*/
			if ((State_Set == NOT_SETTING))
			{
				/*Function to check, process input buffer from RX-UART1 and return State_Set */
				process_setting(&State_Set);
				/*Reset initial conditions*/
				input_complete = INPUT_NONE_COMPLETE;
				reset_received_data();
				if (State_Set == SET_DATE)
				{
					/*Show format Date String for setting Date*/
					print_Output((char*)Date_Format_Str);
				}
				else if (State_Set == SET_TIME)
				{
					/*Show format Time String for setting Date*/
					print_Output((char*)Time_Format_Str);
				}
				else 
				{
					/*Show error if users input invalid string for setting mode*/
					print_Output((char*)Error_String);
				}
			}
			else if ((State_Set == SET_DATE))
			{
				/*Function to check Date format from RX-UART1 buffer*/
				if (Check_Date_Format())
				{
					/*Function to update input Date*/
					Update_Date(&day, &month, &year);
					/*Print successfull notifications*/
					print_Output((char*)Date_Updated_Str);
					/*Reset State_Set*/
					State_Set = NOT_SETTING;
				}
				else 
				{
					print_Output((char*)Error_String);
				}
				/*Reset initial conditions*/
				input_complete = INPUT_NONE_COMPLETE;
				reset_received_data();
			}
			else if ((State_Set == SET_TIME))
			{
				if (Check_Time_Format())
				{
					/*Function to update input Time*/
					Update_Time(&second, &minute, &hour);
					/*Print successfull notifications*/
					print_Output((char*)Time_Updated_Str);
					/*Reset State_Set*/
					State_Set = NOT_SETTING;
				}
				else 
				{
					print_Output((char*)Error_String);
				}
				/*Reset initial conditions*/
				input_complete = INPUT_NONE_COMPLETE;
				reset_received_data();
			}
			else 
			{
				/*do not thing*/
			}
		}
}

void LPIT0_Ch3_IRQHandler (void)
{
	/*Clear interrupt flag*/
	Lpit_Clear_Interrupt_Flag(3);
	/*Trigger ADC*/
	ADC0_SC1A |=  (ADC0_SE12<<ADC_SC1A_ADCH_SHIFT);
	/*Increase count to 1 unit, every time count is increased to 1 corresponding to 250ms*/
	count++;
	if (count==4)
	{
		/*Enough 1s*/
		second++; 
		count = 0;
	}
	else 
	{
		/*do not thing*/
	}
	/*Time update after 1 second*/
	Time(&second);
	/*Date update after 1 second*/
	Date(&day);
	/*Check state display and mode display*/
	if (State_Button1 == DISPLAY_DATE_MODE && State_Button2 == TURNON_DISPLAY_MODE)
	{
		if (State_Display == TURNOFF_DISPLAY_MODE)
		{
			State_Display = TURNON_DISPLAY_MODE;
			Turn_On_Display();
		}
		/*Show current Date to module LCD*/
		Display_Date(day,month,year);
	}
	else if (State_Button1 == DISPLAY_TIME_MODE && State_Button2 == TURNON_DISPLAY_MODE)
	{
		if (State_Display == TURNOFF_DISPLAY_MODE)
		{
			State_Display = TURNON_DISPLAY_MODE;
			Turn_On_Display();
		}
		/*Show current Time to module LCD*/
		Display_Time(second,minute,hour);
	}
	else if (State_Button2 == TURNOFF_DISPLAY_MODE)
	{
		Turn_Off_Display();
		State_Display = TURNOFF_DISPLAY_MODE;
	}
	else 
	{
		/*do not thing*/
	}
}

void ADC0_IRQHandler (void)
{
	/*Read ADC value*/
	ADC_Value = (unsigned short)ADC0_RA;
	/*Update intensity for module Led*/
	Control_Intensity(ADC_Value);
}


