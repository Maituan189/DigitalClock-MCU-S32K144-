/**
 * @file    Port.c
 * @brief   Port Driver Source File
 * @details This source file contains the implementation of the Port driver functions.
 *          It provides the functionality to initialize and configure GPIO port pins
 *          according to the settings specified in the configuration structure.
 *
 * @note    Ensure that the configuration structure is properly defined and passed to 
 *          the functions in this file to avoid incorrect port configurations.
 *
 * @version 1.0
 * @date    2024-09-19
 * @author  Mai Anh Tuan
 */
/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Port.h"
/*==================================================================================================
*                                       GLOBAL FUNCTIONS
==================================================================================================*/
/**
 * @brief Initializes the GPIO pins with the specified configuration.
 *
 * This function configures the GPIO port pins as specified in the 
 * `Port_ConfigType` structure. It sets up the pull resistor, drive strength, 
 * mux selection, and interrupt configuration for the specified pin.
 *
 * @param[in] ConfigPtr Pointer to the configuration structure that specifies the 
 *                      port settings.
 * @return Port_ret_t   Status of the operation.
 *                      - PORT_OK: Initialization was successful.
 *                      - PORT_ERR_PARA: Error due to incorrect parameter.
 */
Port_ret_t Port_Init(const Port_ConfigType* ConfigPtr)
{
		static Port_ret_t ret = PORT_OK;
		static unsigned int regValue;
    /* Check if pinPortIdx is within a valid range */
    if (ConfigPtr->pinPortIdx >= NUM_OF_PINS_PER_PORT) 
    {
        return PORT_ERR_PARA; /*!< Return error if pin index is out of range */
    }
    /* Validate other configuration values if necessary */
    if (ConfigPtr->pullConfig > PORT_PULL_UP || ConfigPtr->driveSelect > PORT_HIGH_DRV_STRENGTH || ConfigPtr->mux > PORT_MUX_ALT7 || ConfigPtr->intConfig > PORT_INT_LOGIC_ONE)
    {
        return PORT_ERR_PARA; /*!< Return error if any configuration parameter is out of range */
    }
	
	regValue = ConfigPtr->base->PCR[ConfigPtr->pinPortIdx];
	/* 1. Internal resistor pull feature selection. */
	switch (ConfigPtr->pullConfig)
    {
		case PORT_NO_PULL_UP_DOWN:
			{ 
				regValue &= ~(PULL_ENABLE<<1);
			}
			break;
		case PORT_PULL_DOWN:
			{
				regValue |= (PULL_ENABLE<<1);
				regValue &= ~(PULL_ENABLE<<0);
			}
			break;
		case PORT_PULL_UP:
			{
				regValue |= (PULL_ENABLE<<1);
				regValue |= (PULL_ENABLE<<0);
			}
			break;
	}
	/* 2. Configures the drive strength.*/
	if (ConfigPtr->driveSelect == PORT_HIGH_DRV_STRENGTH)
	{
		regValue &= ~(1u<<6);
    	regValue |= (1u<<6);
	}
	else if (ConfigPtr->driveSelect == PORT_LOW_DRV_STRENGTH)
	{
		regValue &= ~(1u<<6);
	}
	/* 3. mux selection. */
	regValue &= ~ ((1u<<8) | (1u<<9) | (1u<<10));
	regValue |= (unsigned int) (((ConfigPtr->mux))<<8);
	/* 4. Interrupt generation condition. */
	regValue &= ~((1u<<16)|(1u<<17)|(1u<<18)|(1u<<19));
  regValue |= (unsigned int) ((ConfigPtr->intConfig)<<16);

    ConfigPtr->base->PCR[ConfigPtr->pinPortIdx] = regValue;
	return ret;	
}
