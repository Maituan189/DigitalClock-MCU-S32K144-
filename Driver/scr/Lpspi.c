/**
 * @brief  Initializes the LPSPI peripheral with the specified configuration.
 * @details This function sets up the LPSPI peripheral by configuring the clock divider, 
 *          prescaler, clock phase, polarity, frame size, and the peripheral chip select (PCS).
 *          Additionally, it configures the FIFO, mode (master/slave), and enables the LPSPI module.
 *
 * @param[in] ConfigPtr Pointer to the configuration structure (Lpspi_ConfigType).
 *
 * @return None.
 */
/*==================================================================================================
*                                        INCLUDE FILES
==================================================================================================*/
#include "Lpspi.h" 
/*==================================================================================================
*                                        GLOBAL FUNCTIONS
==================================================================================================*/ 
void Lpspi_Init (const Lpspi_ConfigType* ConfigPtr )
{
	unsigned int SCK_diver = 0;
	unsigned int TCR_value = 0;
	/* Step 1. Check parameter */
	if ( (ConfigPtr->pSPIx == (void*)0) 
	|| ConfigPtr->Init.spi_prescaler > LPSPI_PRE_DIV_BY_128 
	|| ConfigPtr->Init.spi_frame > LPSPI_FRAME_32
	|| ConfigPtr->Init.spi_cpol > SPI_CPOL_1
	|| ConfigPtr->Init.spi_cpha > SPI_CPHA_1
	|| ConfigPtr->Init.spi_pcs > LPSPI_PCS_3
	|| ConfigPtr->Init.spi_type_transfer > LPSPI_LSB_FIRST)
    {
        return;  // Invalid pointer
    }
	/* Step 2. Set divide ratio of the SCK pin*/
	SCK_diver = ConfigPtr->Init.spi_sck_div;
	ConfigPtr->pSPIx->CCR |= (SCK_diver);
	/* Step 3. 	Configures Clock Phase and Polarity    */
	/* Step 4.  Set Prescaler Value                    */
	/* Step 5.  Configures Clock Phase and Polarity    */
	/* Step 6.  Setting Frame data                     */
	/* Step 7.  Configures the peripheral chip select  */
	TCR_value =  ((unsigned int)(ConfigPtr->Init.spi_cpha) << LPSPI_TCR_CPHA_SHIFT)
				|((unsigned int)(ConfigPtr->Init.spi_cpol) << LPSPI_TCR_CPOL_SHIFT)
				|((unsigned int)(ConfigPtr->Init.spi_prescaler) << LPSPI_TCR_PRESCALE_SHIFT)
				|((unsigned int)(ConfigPtr->Init.spi_frame) << LPSPI_TCR_FRAMESZ_SHIFT)
				|((unsigned int)(ConfigPtr->Init.spi_type_transfer) << LPSPI_TCR_LSBF_SHIFT)
				|((unsigned int)(ConfigPtr->Init.spi_pcs) << LPSPI_TCR_PCS_SHIFT);
	ConfigPtr->pSPIx->TCR = TCR_value;

	/* 7. Setting Transmit/Receive FIFO */
	ConfigPtr ->pSPIx ->FCR |= ((3U)<<LPSPI_FCR_TXWATER_SHIFT) ;
	ConfigPtr ->pSPIx ->FCR &= ~(((1U)<<16)|((1U)<<17));
	
	ConfigPtr ->pSPIx ->CFGR1 |= (1U << LPSPI_CFGR1_NOSTALL_SHIFT);

	/* 8. Configures LPSPI mode */ 
		/* Master mode */
	ConfigPtr ->pSPIx ->CFGR1 |= (1U << LPSPI_CFGR1_MASTER_SHIFT);
		/* Debug mode */
	ConfigPtr ->pSPIx ->CR |= (1U << LPSPI_CR_DGGEN_SHIFT);

	/* 9. Enable LPSPI module */
	ConfigPtr ->pSPIx ->CR |= (1U << LPSPI_CR_MEN_SHIFT);
	
}

void Lpspi_Transmit(LPSPI_Type *pLpspi, unsigned short *pTxBuffer, unsigned short Size)
{
	while(Size > 0)
	{
		/* Wait until the Transmit Data Flag (TDF) is set */
		while((((pLpspi->SR)>>0)&0x01)==0);
		/* Write data to Transmit Data Register (TDR) */
		pLpspi->TDR = *pTxBuffer;
		/* Increment the buffer address */
		pTxBuffer+=1;
		/* Decrease the size count */
		Size -= 1;
	}
}

