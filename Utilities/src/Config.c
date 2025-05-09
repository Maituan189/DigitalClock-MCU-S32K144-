/**
 * @file    Config.c
 * @brief   System Configuration for Peripherals
 * @details This file initializes system clocks, NVIC, UART, SPI, LPIT, 
 *          ADC, and button configurations for the microcontroller.
 *
 * @version 1.0
 * @date    2024-10-09
 * @author  Mai Anh Tuan
 */
 /*==================================================================================================
*                                       INCLUDE FILE
==================================================================================================*/
#include "Config.h"
/*==================================================================================================
*                                      LOCAL VARIABLES
==================================================================================================*/
static Port_ConfigType PORTC_Pin6;
static Port_ConfigType PORTC_Pin7;
static Port_ConfigType PORTC_Pin12;
static Port_ConfigType PORTC_Pin13;
static Port_ConfigType PORTC_Pin14;
static Port_ConfigType PORTB_Pin14;
static Port_ConfigType PORTB_Pin15;
static Port_ConfigType PORTB_Pin16;
static Port_ConfigType PORTB_Pin17;
static Pcc_ConfigType  PCC_PORTC;
static Pcc_ConfigType  PCC_PORTD;
static Pcc_ConfigType  PCC_PORTB;
static Pcc_ConfigType  PCC_UART1;
static Pcc_ConfigType  PCC_UART0;
static Pcc_ConfigType  PCC_LPSPI1;
static Pcc_ConfigType  PCC_ADC0;
static Lpspi_ConfigType ConfigSPI1;
static Pcc_ConfigType ConfigLPIT;
static Scg_Firc_ConfigType ConfigFIRC;
static Scg_Sosc_ConfigType ConfigSOSC;
static Lpit_ChannelConfigType ConfigLPIT_CH3;
static Lpuart_ConfigType ConfigUART;

/*==================================================================================================
*                                      LOCAL FUNCTIONS
==================================================================================================*/
static void Config_Clock(void)
{
	/*Confugure clock source for LPITUART*/
	ConfigFIRC.div1=0;
	ConfigFIRC.div2=1;
	Clock_SetScgFircConfig(&ConfigFIRC);
	
	/*Confugure clock source for LPIT*/
	ConfigSOSC.div1=SCG_CLOCK_DIV_BY_2;
	ConfigSOSC.div2=SCG_CLOCK_DIV_BY_8;
	Clock_SetScgSoscConfig(&ConfigSOSC);
	
	/*Enable Port Clock*/
	/*Enable clock for PORTC: PCC[CGC]*/
	PCC_PORTC.clockName = PORTC_CLK;
	PCC_PORTC.clkGate = CLK_GATE_ENABLE;
	Clock_SetPccConfig(&PCC_PORTC);
	
	/*Enable clock for PORTB: PCC[CGC]*/
	PCC_PORTD.clockName = PORTD_CLK;
	PCC_PORTD.clkGate = CLK_GATE_ENABLE;
	Clock_SetPccConfig(&PCC_PORTD);
	
	PCC_PORTB.clockName = PORTB_CLK;
	PCC_PORTB.clkGate = CLK_GATE_ENABLE;
	Clock_SetPccConfig(&PCC_PORTB);
	
	/*Peripheral Clock Source Select of UART_Channel0: PCC[PCS]*/
	PCC_UART0.clkGate = CLK_GATE_ENABLE;
	PCC_UART0.clkSrc = CLK_SRC_OP_3;
	PCC_UART0.clockName =  LPUART0_CLK;
	Clock_SetPccConfig(&PCC_UART0);
	
	/*Peripheral Clock Source Select: PCC[PCS]*/
	PCC_UART1.clkGate = CLK_GATE_ENABLE;
	PCC_UART1.clkSrc = CLK_SRC_OP_3;
	PCC_UART1.clockName =  LPUART1_CLK;
	Clock_SetPccConfig(&PCC_UART1);
	
	/* Enable clock for LPSPI: PCC[CGC]*/
	PCC_LPSPI1.clkGate = CLK_GATE_ENABLE;
	PCC_LPSPI1.clkSrc = CLK_SRC_OP_3;
	PCC_LPSPI1.clockName = LPSPI1_CLK;
	Clock_SetPccConfig(&PCC_LPSPI1);
	
	/* Enable clock for LPIT: PCC[CGC]*/
	ConfigLPIT.clkGate=CLK_GATE_ENABLE;
	ConfigLPIT.clockName=LPIT0_CLK;
	ConfigLPIT.clkSrc=CLK_SRC_OP_1;
	Clock_SetPccConfig(&ConfigLPIT);
	
	/* Enable clock for ADC0: PCC[CGC]*/
	PCC_ADC0.clockName = ADC0_CLK;
	PCC_ADC0.clkSrc = CLK_SRC_OP_3;
	PCC_ADC0.clkGate = CLK_GATE_ENABLE;
	Clock_SetPccConfig(&PCC_ADC0);
	
}

static void Config_NVIC(void)
{
	/*Configures NVIC for LPITUART1*/
	NVIC_EnableInterrupt(LPUART1_RxTx_IRQn); 
	NVIC_SetPriority(LPUART1_RxTx_IRQn, 9);
	
	/*Configures NVIC for Button*/
	NVIC_EnableInterrupt(PORTC_IRQn);
	NVIC_SetPriority(PORTC_IRQn, 5);
	
	/*Setting NIVIC for LPIT Channel 3*/
	NVIC_SetPriority(LPIT0_Ch3_IRQ, 0);
	NVIC_EnableInterrupt(LPIT0_Ch3_IRQ);
	
	/*Setting NIVIC for ADC Channel 0*/
	NVIC_EnableInterrupt(ADC0_IRQ);
	NVIC_SetPriority(ADC0_IRQ, 10);
}


static void Config_UART_1(void)
{
	/*Set alternate function pins: PORT_PCR[MUX]*/
	PORTC_Pin6.base = PORTC;
	PORTC_Pin6.mux = 2; 
	PORTC_Pin6.pinPortIdx = 6;
	Port_Init(&PORTC_Pin6);
	PORTC_Pin7.base = PORTC;
	PORTC_Pin7.mux = 2;
	PORTC_Pin7.pinPortIdx = 7;
	Port_Init(&PORTC_Pin7);
	/*Configure UART1: Baudrate 19200, interrupt RX, 
	one stop bit, no parity bit, idle line with 8 character*/
	ConfigUART.pUARTx= LPUART1;
	ConfigUART.Init.lpuart_baudrate_modulo_divisor= 250;
	ConfigUART.Init.lpuart_data_frame = FRAME_8_BIT;
	ConfigUART.Init.lpuart_oversampling = oversampling_ratio_10;
	ConfigUART.Init.lpuart_enable_int_RX = 1;
	ConfigUART.Init.lpuart_parity_bit = LPUART_DISABLE_PARITY_BIT;
	ConfigUART.Init.lpuart_stop_bit = ONE_STOP_BIT;
	ConfigUART.Init.lpuart_enable_idl = 1;
	ConfigUART.Init.lpuart_number_character_idl = IDLE_CHARACTER_8;
	Lpuart_Init (&ConfigUART);
}

static void Config_Buttons(void)
{
	/* Configure Pin 12 of Port C is GPIO */
	PORTC_Pin12.base = PORTC;
	PORTC_Pin12.pinPortIdx= 12;
	PORTC_Pin12.mux= 1;
	PORTC_Pin12.intConfig= PORT_INT_FALLING_EDGE;
	Port_Init(&PORTC_Pin12);
	
	PORTC_Pin13.base = PORTC;
	PORTC_Pin13.pinPortIdx= 13;
	PORTC_Pin13.mux= 1;
	PORTC_Pin13.intConfig= PORT_INT_FALLING_EDGE;
	Port_Init(&PORTC_Pin13);
	
	/* Configure Pin 12&13 of Port C is input */
	GPIO_Init (GPIOC, 12, GPIO_MODE_INPUT);
	GPIO_Init (GPIOC, 13, GPIO_MODE_INPUT);
}
	
static void Config_SPI(void) 
{
	/* Set alternate function pin: PORT_PCR[MUX]*/
	PORTB_Pin14.base = PORTB;
	PORTB_Pin15.base = PORTB;
	PORTB_Pin16.base = PORTB;
	PORTB_Pin17.base = PORTB;
	
	PORTB_Pin14.pinPortIdx = 14; /*SCK*/
	PORTB_Pin15.pinPortIdx = 15; /*SIN*/
	PORTB_Pin16.pinPortIdx = 16; /*SOUT*/
	PORTB_Pin17.pinPortIdx = 17; /*CS3*/
	
	PORTB_Pin14.mux= PORT_MUX_ALT3; 
	PORTB_Pin15.mux= PORT_MUX_ALT3;
	PORTB_Pin16.mux= PORT_MUX_ALT3;
	PORTB_Pin17.mux= PORT_MUX_ALT3;

	Port_Init(&PORTB_Pin14);
	Port_Init(&PORTB_Pin15);
	Port_Init(&PORTB_Pin16);
	Port_Init(&PORTB_Pin17);
	
	
	/*Configure SPI1: Speed 1MHZ, 16 bits, chip select 3, 
	CPOL = 0, CPHA = 0, MSB data transfer*/
	ConfigSPI1.pSPIx = LPSPI1;
	ConfigSPI1.TxLen = 13;
	ConfigSPI1.Init.spi_sck_div = 46;
	ConfigSPI1.Init.spi_cpol = SPI_CPOL_0;
	ConfigSPI1.Init.spi_cpha = SPI_CPHA_0;
	ConfigSPI1.Init.spi_frame = LPSPI_FRAME_16;
	ConfigSPI1.Init.spi_pcs = LPSPI_PCS_3;
	ConfigSPI1.Init.spi_prescaler = LPSPI_PRE_DIV_BY_1;
	ConfigSPI1.Init.spi_type_transfer = LPSPI_MSB_FIRST;
	Lpspi_Init (&ConfigSPI1);
}

static void Config_LPIT(void)
{
	/*Congigure LPIT: enable interrupt, period = 250000 (=250ms), f = 1MHZ*/
	Lpit_Init();
	ConfigLPIT_CH3.isInterruptEnabled = 1;
	ConfigLPIT_CH3.period = 250000+1;
	Lpit_InitChannel(3, &ConfigLPIT_CH3);
	Lpit_StartChannel(3);
}

static void Config_ADC(void)
{
	PORTC_Pin14.base = PORTC;
	PORTC_Pin14.mux = 0; 
	PORTC_Pin14.pinPortIdx = 14;
	Port_Init(&PORTC_Pin14);
	
	ADC0_CFG1 |= (1U<<5);
	
	/*Enable the calibration : SC3[CAL]*/
	ADC0_SC3 |= (1U<<7);
	
	/*Enable the hardware average: SC3[AVGE]*/
	ADC0_SC3 |= (1U<<2);
	
	/*Select the sample averaged: SC3[AVGES]*/
	ADC0_SC3 |= (3U<<0);
	
	/*Wait for the calibration to complete: SC1A[SC1A]*/
	while (((ADC0_SC1A >> 7 )&0x01)==0);

	/*+ Select the ADC resolution: CFG1[MODE]*/
	ADC0_CFG1 |= (1U<<2);
	
	/*+ Select the sample time: CFG2[SMPLTS]*/
	ADC0_CFG2 |= (200U<<0);
	
	/*+ Select the voltage ref source: SC2[REFSEL]*/
	ADC0_SC2 &=~(1U<< 0);
	
	/*+ Select the type of trigger: SC2[ADTRG]*/
	ADC0_SC2 &= ~(1U<<6); 
	
	/*+ Select the type of conversion: SC3[ADCO]*/
	ADC0_SC3 &=~ (1U<<3);
	
	/*+ Select the type of conversion: SC3[ADCO]*/
	
	ADC0_SC1A &=~( (1U<<5)|(1U<<4)|(1U<<3)|(1U<<2)|(1U<<1)|(1U<<0) );
	ADC0_SC1A |=  (12U<<0);
	ADC0_SC1A |= (1U<<6);
}

/*==================================================================================================
*                                      GLOBAL FUNCTIONS
==================================================================================================*/
void Config_System(void)
{
	Config_Clock();
	Config_NVIC();
	Config_LPIT();
	Config_UART_1();
	Config_SPI();
	Config_Buttons();
	Config_ADC();
}

