#ifndef PURE_STM_H
#define PURE_STM_H
#include <stdint.h>
/**
 * @file pure_stm.h
 * @brief Minimalist Bare-Metal peripheral driver for STM32F4 series microcontrollers.
 * @author Arthyrod
 */

/* =================================================================           
 * 1. CORE DEFINITIONS
 * ================================================================= */

#define LOW 0
#define HIGH 1
#define INPUT 0
#define OUTPUT 1

#define HSI_VALUE    16000000U
#define HSE_VALUE    25000000U
#define PPL_VALUE   100000000U
extern uint32_t SystemCoreClock;

/* Bus Enable Masks */
#define AHB1_ALL_EN   0x007000FF  
#define AHB2_ALL_EN   0x00000080 
#define APB1_ALL_EN   0x36FE41FF  
#define APB2_ALL_EN   0x00077911  


/* =================================================================           
 * 2. REGISTER STRUCTURES
 * ================================================================= */

// --- GPIO ---
typedef struct {
    volatile uint32_t MODER;    
    volatile uint32_t OTYPER;   
    volatile uint32_t OSPEEDR;  
    volatile uint32_t PUPDR;    
    volatile uint32_t IDR;      
    volatile uint32_t ODR;     
    volatile uint32_t BSRR;     
    volatile uint32_t LCKR;     
    volatile uint32_t AFRL;    
    volatile uint32_t AFRH;    
} GPIO_TypeDef;

// --- RCC ---
typedef struct {
    volatile uint32_t CR;           
    volatile uint32_t PLLCFGR;      
    volatile uint32_t CFGR;         
    volatile uint32_t CIR;          
    volatile uint32_t AHB1RSTR;     
    volatile uint32_t AHB2RSTR;     
    uint32_t RSVD_18_1C[2];         
    volatile uint32_t APB1RSTR;     
    volatile uint32_t APB2RSTR;     
    uint32_t RSVD_28_2C[2];       
    volatile uint32_t AHB1ENR;      
    volatile uint32_t AHB2ENR;      
    uint32_t RSVD_38_3C[2];         
    volatile uint32_t APB1ENR;      
    volatile uint32_t APB2ENR;      
    uint32_t RSVD_48_4C[2];         
    volatile uint32_t AHB1PENR;     
    volatile uint32_t AHB2PENR;     
    uint32_t RSVD_58_5C[2];         
    volatile uint32_t APB1PENR;     
    volatile uint32_t APB2PENR;     
    uint32_t RSVD_68_6C[2];         
    volatile uint32_t BDCR;         
    volatile uint32_t CSR;          
    uint32_t RSVD_78_7C[2];         
    volatile uint32_t SSCGR;        
    volatile uint32_t PLLI2SCFGR;   
    uint32_t RSVD_88;               
    volatile uint32_t DCKCFGR;     
} RCC_TypeDef;

// --- Flash ---
typedef struct {
    volatile uint32_t ACR;      
    volatile uint32_t KEYR;     
    volatile uint32_t OPTKEYR;  
    volatile uint32_t SR;       
    volatile uint32_t CR;     
    volatile uint32_t OPTCR;   
} FLASH_TypeDef;

// --- Timer ---

typedef struct {
    volatile uint32_t CTRL;    
    volatile uint32_t LOAD;    
    volatile uint32_t VAL;     
    volatile uint32_t CALIB;   
} SysTick_TypeDef;

typedef struct {
    volatile uint32_t CR1;      
    volatile uint32_t CR2;    
    volatile uint32_t SMCR;     
    volatile uint32_t DIER;     
    volatile uint32_t SR;       
    volatile uint32_t EGR;      
    volatile uint32_t CCMR1;   
    volatile uint32_t CCMR2;    
    volatile uint32_t CCER;     
    volatile uint32_t CNT;      
    volatile uint32_t PSC;      
    volatile uint32_t ARR;      
    volatile uint32_t RCR;      
    volatile uint32_t CCR1;     
    volatile uint32_t CCR2;     
    volatile uint32_t CCR3;     
    volatile uint32_t CCR4;     
    volatile uint32_t BDTR;     
    volatile uint32_t DCR;      
    volatile uint32_t DMAR;     
    volatile uint32_t OR;       
} TIM_Advanced_TypeDef; // For TIM1

typedef struct {
    volatile uint32_t CR1;   
    volatile uint32_t CR2;  
    volatile uint32_t SMCR;  
    volatile uint32_t DIER;  
    volatile uint32_t SR;   
    volatile uint32_t EGR;  
    volatile uint32_t CCMR1; 
    volatile uint32_t CCMR2; 
    volatile uint32_t CCER; 
    volatile uint32_t CNT;   
    volatile uint32_t PSC;   
    volatile uint32_t ARR;  
    uint32_t RSVD_30;        
    volatile uint32_t CCR1;  
    volatile uint32_t CCR2;  
    volatile uint32_t CCR3;  
    volatile uint32_t CCR4; 
    uint32_t RSVD_44;         
    volatile uint32_t DCR;  
    volatile uint32_t DMAR; 
    volatile uint32_t OR;   
} TIM_GenPurp_TypeDef; // For TIM2 to TIM5

typedef struct {
    volatile uint32_t CR1;      
    volatile uint32_t CR2;      
    volatile uint32_t SMCR;     
    volatile uint32_t DIER;     
    volatile uint32_t SR;       
    volatile uint32_t EGR;      
    volatile uint32_t CCMR1;    
    uint32_t reserved1;         
    volatile uint32_t CCER;    
    volatile uint32_t CNT;     
    volatile uint32_t PSC;      
    volatile uint32_t ARR;      
    uint32_t reserved2;         
    volatile uint32_t CCR1;     
    volatile uint32_t CCR2;    
} TIM9_TypeDef; //  For TIM9

typedef struct {
    volatile uint32_t CR1;     
    uint32_t reserved0[2];      
    volatile uint32_t DIER;    
    volatile uint32_t SR;       
    volatile uint32_t EGR;     
    volatile uint32_t CCMR1;    
    uint32_t reserved1;         
    volatile uint32_t CCER;     
    volatile uint32_t CNT;      
    volatile uint32_t PSC;     
    volatile uint32_t ARR;      
    uint32_t reserved2;         
    volatile uint32_t CCR1;     
} TIM10_11_TypeDef; // For TIM10 and TIM11

/* =================================================================           
 * 3. PERIPHERAL INSTANCES (Memory Mapping)
 * ================================================================= */

#define RCC_BASE  0x40023800
#define RCC   ((RCC_TypeDef *) RCC_BASE)

#define FLASH_BASE 0x40023C00
#define FLASH ((FLASH_TypeDef *) FLASH_BASE)

#define GPIOA_BASE 0x40020000
#define GPIOA ((GPIO_TypeDef *)     GPIOA_BASE)
#define GPIOB_BASE 0x40020400
#define GPIOB ((GPIO_TypeDef *)     GPIOB_BASE)
#define GPIOC_BASE 0x40020800
#define GPIOC ((GPIO_TypeDef *)     GPIOC_BASE)

#define SYSTICK_BASE 0xE000E010
#define SysTick ((SysTick_TypeDef *) SYSTICK_BASE)
#define TIM1_BASE 0x40010000
#define TIM1  ((TIM_Advanced_TypeDef *) TIM1_BASE)
#define TIM2_BASE 0x40000000
#define TIM2  ((TIM_GenPurp_TypeDef *) TIM2_BASE)
#define TIM3_BASE 0x40000400
#define TIM3  ((TIM_GenPurp_TypeDef *) TIM3_BASE)
#define TIM4_BASE 0x40000800
#define TIM4  ((TIM_GenPurp_TypeDef *) TIM4_BASE)
#define TIM5_BASE 0x40000C00
#define TIM5  ((TIM_GenPurp_TypeDef *) TIM5_BASE)
#define TIM9_BASE 0x40014000
#define TIM9  ((TIM9_TypeDef *) TIM9_BASE)
#define TIM10_BASE 0x40014400
#define TIM10 ((TIM10_11_TypeDef *) TIM10_BASE)
#define TIM11_BASE 0x40014800
#define TIM11 ((TIM10_11_TypeDef *) TIM11_BASE)

/* =================================================================           
 * 4. API ENUMERATIONS
 * ================================================================= */

typedef enum {
    HSI, 
    HSE, 
    PLL  
} ClockSource_t;

typedef enum {
    // AHB1 Peripherals
    PERIPH_GPIOA, PERIPH_GPIOB, PERIPH_GPIOC, PERIPH_GPIOD, PERIPH_GPIOH,
    PERIPH_CRC, PERIPH_DMA1, PERIPH_DMA2,
    
    // AHB2 Peripherals
    PERIPH_OTGFS,      // USB On-The-Go Full Speed
    
    // APB1 Peripherals
    PERIPH_TIM2, PERIPH_TIM3, PERIPH_TIM4, PERIPH_TIM5,
    PERIPH_WWDG, PERIPH_SPI2, PERIPH_SPI3, PERIPH_USART2,
    PERIPH_I2C1, PERIPH_I2C2, PERIPH_I2C3, PERIPH_PWR,
    
    // APB2 Peripherals
    PERIPH_TIM1, PERIPH_USART1, PERIPH_USART6, PERIPH_ADC1,
    PERIPH_SPI1, PERIPH_SPI4, PERIPH_SYSCFG, PERIPH_TIM9,
    PERIPH_TIM10, PERIPH_TIM11
} Peripheral_t;

typedef enum {
    BUS_AHB1, BUS_AHB2, BUS_APB1, BUS_APB2
} Bus_t;

/* =================================================================           
 * 5. FUNCTION PROTOTYPES
 * ================================================================= */
 
// RCC
void clock_init(ClockSource_t clk_set);
void peripheral_bus_enable(Bus_t bus);
void periph_enable(Peripheral_t periph);

// GPIO
void pinMode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);
void pinSet(GPIO_TypeDef *port, uint8_t pin, uint8_t state);
uint32_t portRead(GPIO_TypeDef *port);
uint8_t pinRead(GPIO_TypeDef *port, uint8_t pin);

// Timers
void delay_ms(uint32_t ms);

#endif // PURE_STM_H






