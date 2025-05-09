/**
*   @file    Driver_GPIO.h
*   @brief   GPIO Driver Header
*   @details This header file provides the declarations for the GPIO (General Purpose Input/Output) driver functions.
*            It includes function prototypes for initializing GPIO pins, setting pin modes, reading and writing
*            pin states, and toggling pin states. The file also contains definitions for constants and macros related
*            to GPIO configuration.
*
*            The functions declared in this header file interact with the GPIO hardware registers to control the
*            GPIO pins of the microcontroller. It is intended to be used with the corresponding implementation file
*            (`Driver_GPIO.c`) which defines the actual functionality.
*
*   @note    Include this header file in your source files to access the GPIO driver functions. Ensure that the
*            necessary GPIO configurations are performed before using these functions.
*
* @version 1.0
* @date    2024-09-05
* @author  Mai Anh Tuan _ EMB05
*/
/*==================================================================================================
==================================================================================================*/
#ifndef GPIO_H
#define GPIO_H
/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "GPIO_Register.h"
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define ENABLE 1
#define DISENABLE 0
/*MODE_GPIO*/
#define GPIO_MODE_INPUT  0
#define GPIO_MODE_OUTPUT 1
/*MODE INPUT*/
/*MODE OUTPUT*/
#define GPIO_HIGH_OUTPUT_PIN 1
#define GPIO_LOW_OUTPUT_PIN 0
/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
typedef struct __attribute__((packed))
{
  GPIO_Type         *      base;                  /*!< Gpio base pointer.  */  
  unsigned char GPIO_PinNumber;
  unsigned char GPIO_PinMode; 
} GPIO_Pin_Config_t;

/*!
 * @brief Initializes the pins with the given configuration structure
 *
 * This function configures the pins with the options provided in the
 * provided structure.
 *
 * @param[in] ConfigPtr:  The configuration structure
 * @return 
 */

/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
extern void GPIO_Init(GPIO_Type* ConfigPtr, unsigned char PinNumber,unsigned char Mode);
extern void GPIO_WriteToOutputPin (GPIO_Type *pGPIOx, unsigned char PinNumber, unsigned char value);
extern void GPIO_SetOutputPin (GPIO_Type *pGPIOx, unsigned char PinNumber);
extern void GPIO_ResetOutputPin (GPIO_Type *pGPIOx, unsigned char PinNumber);
extern void GPIO_TogglePin (GPIO_Type *pGPIOx, unsigned char PinNumber);
extern unsigned char GPIO_ReadStateInputPin (GPIO_Type *pGPIOx, unsigned char PinNumber);
#endif
