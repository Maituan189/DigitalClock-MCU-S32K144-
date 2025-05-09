/**
 * @file    GPIO_Register.h
 * @brief   GPIO Register Definitions and Constants
 * @details This header file defines the register addresses, and constants used for 
 *          configuring and controlling GPIO (General Purpose Input/Output) pins on the microcontroller S32K144.
 *          It includes the definitions for GPIO registers and macros for manipulating GPIO pins.
 *
 *          This file provides the necessary definitions for low-level GPIO operations and should be 
 *          included in conjunction with the GPIO driver implementation for complete GPIO functionality.
 *
 * @note    Ensure that this header file is included in the source files that require direct access 
 *          to GPIO registers.
 *
 * @version 1.0
 * @date    2024-09-05
 * @author  Mai Anh Tuan _ EMB05
 */
/*==================================================================================================
==================================================================================================*/
#ifndef GPIO_REGISTER_H
#define GPIO_REGISTER_H
/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
/*==================================================================================================
*                                      DEFINES AND MACROS
==================================================================================================*/
#define GPIOA       ((GPIO_Type*)(0x400FF000))
#define GPIOB       ((GPIO_Type*)(0x400FF040))
#define GPIOC       ((GPIO_Type*)(0x400FF080))
#define GPIOD       ((GPIO_Type*)(0x400FF0C0))
#define GPIOE       ((GPIO_Type*)(0x400FF100))
/*==================================================================================================
*                                STRUCTURES AND OTHER TYPEDEFS
==================================================================================================*/
/**
* @brief          GPIO driver
* @details        This structure is gpio register in a port
*
*/
typedef struct
	{
	    volatile unsigned int PDOR;                /*  Port Data Output Register   */
	    volatile unsigned int PSOR;                /*  Port Set Output Register    */
	    volatile unsigned int PCOR;                /*  Port Clear Output Register  */
	    volatile unsigned int PTOR;                /*  Port Toggle Output Register */
	    const volatile unsigned int PDIR;          /*  Port Data Input Register    */
	    volatile unsigned int PDDR;                /*  Port Data Direction Register*/
	    volatile unsigned int PIDR;                /*  Port Input Disable Register */
	} GPIO_Type;
/*==================================================================================================
*                                GLOBAL VARIABLE DECLARATIONS
==================================================================================================*/
/*==================================================================================================
*                                    FUNCTION PROTOTYPES
==================================================================================================*/
#endif /* GPIO_REGISTER_H */

