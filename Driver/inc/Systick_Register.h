#ifndef SYSTICK_REG_H
#define SYSTICK_REG_H


#define SYST_CSR_ENABLE_SHIFT    (0U)
#define SYST_CSR_TICKINT_SHIFT   (1U)
#define SYST_CSR_CLKSOURCE_SHIFT (2U)
#define SYST_CSR_COUNTFLAG_SHIFT (16U)

#define COUNTFLAG_IS_SET         (0x01U)
#define NULL ((void*)0)

typedef struct 
{
    volatile unsigned int CSR;
    volatile unsigned int RVR;
    volatile unsigned int CVR;
    volatile unsigned int CALIB;
} SYST_Type;

#define SYST_BASE_ADDRESS (0xE000E010)
#define SYST ((SYST_Type *)SYST_BASE_ADDRESS)

#endif
