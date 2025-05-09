/**
 * @file    GPIO_Driver.c
 * @brief   GPIO Driver Implementation
 * @details This source file implements the functions for initializing, configuring, and controlling
 *          GPIO (General Purpose Input/Output) pins on the microcontroller. The functions provided
 *          include setting pin modes, writing values to pins, reading pin states, and toggling pin states.
 *
 *          The GPIO driver uses the register definitions provided in GPIO_Register.h to interact 
 *          with the hardware. This file should be included as part of the overall GPIO management
 *          system in your application.
 *
 * @note    Ensure that the GPIO registers and configurations are set up correctly before calling
 *          these functions. Incorrect configurations may result in undefined behavior or hardware 
 *          malfunctions.
 *
 * @version 1.0
 * @date    2024-09-05
 * @author  Mai Anh Tuan _ EMB05
 */
 /*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
 #include "GPIO.h"
/*==================================================================================================
*                                      DECLEARATION FUNCTION PROTOTYPE
==================================================================================================*/
extern void GPIO_Init(GPIO_Type* ConfigPtr,unsigned char PinNumber ,unsigned char Mode);
extern void GPIO_WriteToOutputPin (GPIO_Type *pGPIOx, unsigned char PinNumber, unsigned char value);
extern void GPIO_SetOutputPin (GPIO_Type *pGPIOx, unsigned char PinNumber);
extern void GPIO_ResetOutputPin (GPIO_Type *pGPIOx, unsigned char PinNumber);
extern void GPIO_TogglePin (GPIO_Type *pGPIOx, unsigned char PinNumber);
extern unsigned char GPIO_ReadStateInputPin (GPIO_Type *pGPIOx, unsigned char PinNumber);
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/**
* @brief          Configures the specified GPIO pin as either input or output based on the provided mode.
* @details        This function initializes the direction of a GPIO pin by setting it as either an input or output 
*                 according to the mode specified by the user.
*
* @param[in]      pGPIOx         Pointer to the GPIO peripheral where the pin resides. 
*                                **Note:** Only from GPIOA to GPIOE are valid.
*                                Passing any other value is not allowed.
*                                or leads malfuction of function.
*
* @param[in]      PinNumber      The specific pin number to configure within the GPIO port.
*                                **Note:** The PinNumber has values from 0 to 31.
*                                Passing any other value is not allowed.
*                                or leads malfuction of function.
*
* @param[in]      Mode           The desired mode for the GPIO pin (input or output).
*                                - GPIO_MODE_INPUT: Configures the pin as an input.
*                                - GPIO_MODE_OUTPUT: Configures the pin as an output.
*                                - **Note:** Only GPIO_MODE_INPUT or GPIO_MODE_OUTPUT are valid. 
*                                            Passing any other value is not allowed
*                                            or leads malfuction of function.
*
* @return         void
*
* @pre            The GPIO clock must be enabled before calling this function
* @post           The specified GPIO pin will be set to the desired mode.
*
* @api            This is a low-level function used to set up the direction of a GPIO pin.
*/
void GPIO_Init(GPIO_Type * pGPIOx, unsigned char PinNumber ,unsigned char Mode)
{
    if (Mode==GPIO_MODE_INPUT)
    {
        pGPIOx->PDDR &= ~(unsigned int)(1<< PinNumber); //Input
    }
    else if (Mode==GPIO_MODE_OUTPUT)
    {
        pGPIOx->PDDR |= (1<< PinNumber); //Output
    }
}

/**
* @brief          Set ouput level of the specific GPIO pins
* @details        This function set the level of output GPIO pin by setting it as either an HIGH or LOW 
*                 according to the mode specified by the user.
*
* @param[in]      pGPIOx         Pointer to the GPIO peripheral where the pin resides. 
*                                **Note:** Only from GPIOA to GPIOE are valid.
*                                Passing any other value is not allowed.
*                                or leads malfuction of function.
*
* @param[in]      PinNumber      The specific pin number to configure within the GPIO port.
*                                **Note:** The PinNumber has values from 0 to 31.
*                                Passing any other value is not allowed.
*                                or leads malfuction of function.
*
* @param[in]      value           The desired level for the GPIO pin (high or low).
*                                - GPIO_HIGH_OUTPUT_PIN: Configures the pin as an high level.
*                                - GPIO_LOW_OUTPUT_PIN: Configures the pin as an low level.
*                                - **Note:** Only GPIO_HIGH_OUTPUT_PIN or GPIO_LOW_OUTPUT_PIN are valid. 
*                                            Passing any other value is not allowed.
*                                            or leads malfuction of function.
*
* @return         void
*
* @pre            The GPIO clock must be enabled and Initing GPIO must be implemented before calling this function
* @post           The specified GPIO pin will be set to the desired level.
*
* @api            This is a low-level function used to set up the level of a GPIO pin.
*/
void GPIO_WriteToOutputPin (GPIO_Type *pGPIOx, unsigned char PinNumber, unsigned char value)
{
    if (value==GPIO_HIGH_OUTPUT_PIN)
    {
        pGPIOx->PDOR |= (1<<PinNumber);
    }
    else if (value==GPIO_LOW_OUTPUT_PIN)
    {
        pGPIOx->PDOR &= ~(unsigned int)(1<<PinNumber);
    }
}

/**
* @brief          Setting high-level ouput of the specific GPIO pins
* @details        This function set the high level of output GPIO pin by writing a specific bit in GPIOx to 1
*
* @param[in]      pGPIOx         Pointer to the GPIO peripheral where the pin resides. 
*                                **Note:** Only from GPIOA to GPIOE are valid.
*                                Passing any other value is not allowed.
*                                or leads malfuction of function.
*
* @param[in]      PinNumber      The specific pin number to configure within the GPIO port.
*                                **Note:** The PinNumber has values from 0 to 31.
*                                Passing any other value is not allowed.
*                                or leads malfuction of function.
*
* @return         void
*
* @pre            The GPIO clock must be enabled and Initing GPIO must be implemented before calling this function
* @post           The specified GPIO pin will be set to high level.
*
* @api            This is a low-level function used to set up the level of a GPIO pin.
*/
void GPIO_SetOutputPin (GPIO_Type *pGPIOx, unsigned char PinNumber)
{
    pGPIOx->PSOR |= (1<<PinNumber);
}


/**
* @brief          Resetting  ouput of the specific GPIO pins to low-level
* @details        This function reset the of output GPIO to low level pin by clearing a specific bit in GPIOx to 0
*
* @param[in]      pGPIOx         Pointer to the GPIO peripheral where the pin resides. 
*                                **Note:** Only from GPIOA to GPIOE are valid.
*                                Passing any other value is not allowed.
*                                or leads malfuction of function.
*
* @param[in]      PinNumber      The specific pin number to configure within the GPIO port.
*                                **Note:** The PinNumber has values from 0 to 31.
*                                Passing any other value is not allowed.
*                                or leads malfuction of function.
*
* @return         void
*
* @pre            The GPIO clock must be enabled and Initing GPIO must be implemented before calling this function
* @post           The specified GPIO pin will be reset to low level.
*
* @api            This is a low-level function used to reset the level of a GPIO pin.
*/
void GPIO_ResetOutputPin (GPIO_Type *pGPIOx, unsigned char PinNumber)
{
    pGPIOx->PCOR &= ~ (unsigned int)(1<<PinNumber);
}

/**
* @brief          Toggles the output level of the specified GPIO pin.
* @details        This function toggles the current state of the specified GPIO pin. 
*                 If the pin is currently at a high level, it will be set to low, and vice versa.

* @param[in]      pGPIOx         Pointer to the GPIO peripheral where the pin resides. 
*                                **Note:** Only from GPIOA to GPIOE are valid.
*                                Passing any other value is not allowed.
*                                or leads malfuction of function.
*
* @param[in]      PinNumber      The specific pin number to configure within the GPIO port.
*                                **Note:** The PinNumber has values from 0 to 31.
*                                Passing any other value is not allowed.
*                                or leads malfuction of function.
*
* @return         void
*
* @pre            The GPIO pin must be configured as an output using GPIO_Init before calling this function.
* @post           The specified GPIO pin will have its level toggled.
*
* @api            This is a low-level function used to toggle the level of a GPIO pin.
*/

void GPIO_TogglePin (GPIO_Type *pGPIOx, unsigned char PinNumber)
{
    pGPIOx->PTOR ^=(1<<PinNumber);
}

/**
* @brief          Reads the state of the specified GPIO input pin.
* @details        This function reads and returns the current state (high or low) of the specified GPIO pin. 
*                 It is assumed that the pin is configured as an input.

* @param[in]      pGPIOx         Pointer to the GPIO peripheral where the pin resides. 
*                                **Note:** Only from GPIOA to GPIOE are valid.
*                                Passing any other value is not allowed.
*                                or leads malfuction of function.
*
* @param[in]      PinNumber      The specific pin number to configure within the GPIO port.
*                                **Note:** The PinNumber has values from 0 to 31.
*                                Passing any other value is not allowed.
*                                or leads malfuction of function.
*
* @return         unsigned char  The current state of the pin:
*                                  - 0: Pin is at a low level.
*                                  - 1: Pin is at a high level.
*
* @pre            The GPIO pin must be configured as an input using GPIO_Init before calling this function.
* @post           The state of the specified GPIO pin is returned.
*
* @api            This is a low-level function used to read the state of a GPIO input pin.
*/
unsigned char GPIO_ReadStateInputPin (GPIO_Type *pGPIOx, unsigned char PinNumber)
{
    return (pGPIOx->PDIR>>PinNumber) & 0x01;
}
