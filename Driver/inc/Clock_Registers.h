#ifndef CLOCK_REG_H
#define CLOCK_REG_H

#define PCC_CGC_SHIFT                       (30U)
#define PCC_PCS_SHIFT                       (24U)
#define SCG_FIRCDIV_FIRCDIV1_SHIFT          (0U)
#define SCG_FIRCDIV_FIRCDIV2_SHIFT          (8U)
#define SCG_SIRCCFG_RANGE_SHIFT             (0U)
#define SCG_CSR_LK_SHIFT                    (23U)
#define SCG_SIRCCSR_SIRCVLD_SHIFT           (24U)
#define SCG_SPLLCSR_SPLLVLD_SHIFT           (24U)
#define SCG_SOSCCSR_SOSCVLD_SHIFT           (24U)
#define SCG_SOSCCFG_RANGE_SHIFT             (4U)
#define SCG_SOSCCFG_EREFS_SHIFT             (2U)
#define SCG_SOSCDIV_SOSCDIV1_SHIFT          (0U)
#define SCG_SOSCDIV_SOSCDIV2_SHIFT          (8U)
#define SCG_SPLLDIV_SPLLDIV1_SHIFT          (0U)
#define SCG_SPLLDIV_SPLLDIV2_SHIFT          (0U)
#define SCG_RCCR_SCS_SHIFT                  (24U)
#define SCG_RCCR_DIVSLOW_SHIFT              (0U)
#define SCG_RCCR_DIVBUS_SHIFT               (4U)
#define SCG_RCCR_DIVCORE_SHIFT              (16U)
#define SCG_SPLLCSR_DISABLE_SHIFT           (0U)
#define SCG_SPLLCFG_SPLLPREDIV_SHIFT        (8U)
#define SCG_SPLLCFG_SPLLMULT_SHIFT          (16U)
#define SCG_SPLLCFG_SPLLSRC_SHIFT           (0U)
#define SCG_FIRC_ENABLE_SHIFT               (0U)
#define SCG_SIRC_ENABLE_SHIFT               (0U)
#define SCG_SOSCCFG_RANGE_LOWFREQ           (1U)
#define SCG_SOSCCFG_RANGE_MEDIUMFREQ        (2U)
#define SCG_SOSCCFG_RANGE_HIGHFREQ          (3U)
#define SCG_SOSCCFG_EREFS_INTERNAL_CRYSTAL  (1U)
#define SCG_SOSCCSR_ENABLE_SHIFT            (0U)
#define SMC_BASE_ADDRESS 0x4007E000	
#define SMC_PMSTAT	(*((volatile unsigned int*)(SMC_BASE_ADDRESS+0x14)))
typedef struct {
	volatile unsigned int PCCn[122];
} PCC_Type;

#define PCC_BASE_ADDRESS (0x40065000u)
#define PCC ((PCC_Type*)PCC_BASE_ADDRESS)


/** SCG - Register Layout Typedef */
typedef struct {
   volatile unsigned int VERID;                             /**< Version ID Register, offset: 0x0 */
   volatile unsigned int PARAM;                             /**< Parameter Register, offset: 0x4 */
   unsigned char RESERVED_0[8];
   volatile unsigned int CSR;                               /**< Clock Status Register, offset: 0x10 */
   volatile unsigned int RCCR;                              /**< Run Clock Control Register, offset: 0x14 */
   volatile unsigned int VCCR;                              /**< VLPR Clock Control Register, offset: 0x18 */
   volatile unsigned int HCCR;                              /**< HSRUN Clock Control Register, offset: 0x1C */
   volatile unsigned int CLKOUTCNFG;                        /**< SCG CLKOUT Configuration Register, offset: 0x20 */
   unsigned char RESERVED_1[220];
   volatile unsigned int SOSCCSR;                           /**< System OSC Control Status Register, offset: 0x100 */
   volatile unsigned int SOSCDIV;                           /**< System OSC Divide Register, offset: 0x104 */
   volatile unsigned int SOSCCFG;                           /**< System Oscillator Configuration Register, offset: 0x108 */
   unsigned char RESERVED_2[244];
   volatile unsigned int SIRCCSR;                           /**< Slow IRC Control Status Register, offset: 0x200 */
   volatile unsigned int SIRCDIV;                           /**< Slow IRC Divide Register, offset: 0x204 */
   volatile unsigned int SIRCCFG;                           /**< Slow IRC Configuration Register, offset: 0x208 */
   unsigned char RESERVED_3[244];
   volatile unsigned int FIRCCSR;                           /**< Fast IRC Control Status Register, offset: 0x300 */
   volatile unsigned int FIRCDIV;                           /**< Fast IRC Divide Register, offset: 0x304 */
   volatile unsigned int FIRCCFG;                           /**< Fast IRC Configuration Register, offset: 0x308 */
   unsigned char RESERVED_4[756];
   volatile unsigned int SPLLCSR;                           /**< System PLL Control Status Register, offset: 0x600 */
   volatile unsigned int SPLLDIV;                           /**< System PLL Divide Register, offset: 0x604 */
   volatile unsigned int SPLLCFG;                           /**< System PLL Configuration Register, offset: 0x608 */
} SCG_Type;

/** Peripheral SCG base address */
#define SCG_BASE_ADDRESS                                 (0x40064000u)
/** Peripheral SCG base pointer */
#define SCG                                      ((SCG_Type *)SCG_BASE_ADDRESS)


#endif

