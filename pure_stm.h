#ifndef PURE_STM_H
#define PURE_STM_H

/**
 * @file pure_stm.h
 * @brief Minimalist Bare-Metal peripheral driver for STM32F4 series microcontrollers.
 * @author Arthyrod
 */

// --- General Definitions ---
#define HSI 0
#define HSE 1

// --- GPIO Register Structure ---
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

// --- RCC Register Structure (Reset and Clock Control) ---
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

// --- Timer Structures ---
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
    volatile uint32_t CR1;      // Control register 1
    volatile uint32_t CR2;      // Control register 2
    volatile uint32_t SMCR;     // Slave mode control register
    volatile uint32_t DIER;     // DMA/Interrupt enable register
    volatile uint32_t SR;       // Status register
    volatile uint32_t EGR;      // Event generation register
    volatile uint32_t CCMR1;    // Capture/compare mode register 1
    uint32_t reserved1;         // Reserved (0x1C)
    volatile uint32_t CCER;     // Capture/compare enable register
    volatile uint32_t CNT;      // Counter
    volatile uint32_t PSC;      // Prescaler
    volatile uint32_t ARR;      // Auto-reload register
    uint32_t reserved2;         // Reserved (0x30)
    volatile uint32_t CCR1;     // Capture/compare register 1
    volatile uint32_t CCR2;     // Capture/compare register 2
} TIM9_TypeDef; //  For TIM9

typedef struct {
    volatile uint32_t CR1;      // Control register 1
    uint32_t reserved0[2];      // Reserved (0x04 - 0x08)
    volatile uint32_t DIER;     // DMA/Interrupt enable register
    volatile uint32_t SR;       // Status register
    volatile uint32_t EGR;      // Event generation register
    volatile uint32_t CCMR1;    // Capture/compare mode register 1
    uint32_t reserved1;         // Reserved (0x1C)
    volatile uint32_t CCER;     // Capture/compare enable register
    volatile uint32_t CNT;      // Counter
    volatile uint32_t PSC;      // Prescaler
    volatile uint32_t ARR;      // Auto-reload register
    uint32_t reserved2;         // Reserved (0x30)
    volatile uint32_t CCR1;     // Capture/compare register 1
} TIM10_11_TypeDef; // For TIM10 and TIM11

// --- Memory Mapping (Peripheral Base Addresses) ---
#define RCC   ((RCC_TypeDef *)      0x40023800)

#define GPIOA ((GPIO_TypeDef *)     0x40020000)
#define GPIOB ((GPIO_TypeDef *)     0x40020400)
#define GPIOC ((GPIO_TypeDef *)     0x40020800)

#define TIM1  ((TIM_Advanced_TypeDef *) 0x40010000)
#define TIM2  ((TIM_GenPurp_TypeDef *)   0x40000000)
#define TIM3  ((TIM_GenPurp_TypeDef *)   0x40000400)
#define TIM4  ((TIM_GenPurp_TypeDef *)   0x40000800)
#define TIM5  ((TIM_GenPurp_TypeDef *)   0x40000C00)
#define TIM9  ((TIM9_TypeDef *)     0x40014000)
#define TIM10 ((TIM10_11_TypeDef *) 0x40014400)
#define TIM11 ((TIM10_11_TypeDef *) 0x40014800)

// --- Function Prototypes ---

// RCC
void clock_init(uint8_t clk_source, uint8_t pll_set, uint8_t clk_frequency);

// GPIO
void pinMode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode);
void pinSet(GPIO_TypeDef *port, uint8_t pin, uint8_t state);
uint32_t portRead(GPIO_TypeDef *port);
uint8_t pinRead(GPIO_TypeDef *port, uint8_t pin);

// Timers
void delay_ms(uint32_t ms);

#endif // PURE_STM_H