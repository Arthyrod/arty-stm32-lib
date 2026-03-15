#include "stdint.h"
#include "pure_stm.h"

// ============================================================================
// RCC FUNCTIONS
// ============================================================================

/**
 * @brief Initializes the system clock.
 * @param clk_set: 0 for HSI (16MHz), 1 for HSE (25MHz), 2 for PPL (100MHz)
 */
void clock_init(ClockSource_t clk_set) {
        switch (clk_set){
            case HSI: 
                if ((RCC->CFGR & 0xFFFC) == 0) {
                    break;
                }
                RCC->CR |= (1 << 0);
                while(!(RCC->CR & (1 << 1)));
                RCC->CFGR &= ~((1 << 1) | (1 << 0));
                while((RCC->CFGR & (0x3 << 2)) != 0); 
                RCC->CR &= ~((1 << 24) | (1 << 16));
                RCC->CFGR &= ~(0xFFF0); 
                FLASH->ACR &= ~0x7;
                break;
            case HSE:
                FLASH->ACR &= ~0x7;
                RCC->CR |= (1 << 16);
                while(!(RCC->CR & (1 << 17)));
                RCC->CFGR &= ~((1 << 1) | (1 << 0));
                RCC->CFGR |= (1 << 0);
                while((RCC->CFGR & (0x3 << 2)) != (1 << 2));
                RCC->CR &= ~(1 << 24);
                break;
            case PPL:
                RCC->CR |= (1 << 16); 
                while(!(RCC->CR & (1 << 17)));
                FLASH->ACR = (1 << 10) | (1 << 9) | (1 << 8) | 0x3;
                RCC->CFGR |= (0x4 << 10); 
                RCC->PLLCFGR = (25 << 0) | (200 << 6) | (0 << 16) | (1 << 22);
                RCC->CR |= (1 << 24); 
                while(!(RCC->CR & (1 << 25)));
                RCC->CFGR &= ~0x3;
                RCC->CFGR |= 0x2; 
                while(((RCC->CFGR >> 2) & 0x3) != 0x2);
                break;
        }
    }
/**
 * @brief  Enables the clock for all peripherals on a specific bus.
 * @param  bus: The target bus to be enabled (e.g., BUS_AHB1, BUS_APB2).
 */
void peripheral_bus_enable(Bus_t bus){
    switch(bus) {
        case BUS_AHB1:
            RCC->AHB1ENR |= AHB1_ALL_EN;
            break;
            
        case BUS_AHB2:
            RCC->AHB2ENR |= AHB2_ALL_EN;
            break;
            
        case BUS_APB1:
            RCC->APB1ENR |= APB1_ALL_EN;
            break;
            
        case BUS_APB2:
            RCC->APB2ENR |= APB2_ALL_EN;
            break;
    }
    __asm("nop");
    __asm("nop");
}
        

// ============================================================================
// GPIO FUNCTIONS
// ============================================================================

/**
 * @brief Configures the operating mode of a specific pin.
 * @param port: Pointer to the GPIO port (e.g., GPIOA, GPIOB).
 * @param pin: Pin number (0-15).
 * @param mode: 00: Input, 01: Output, 10: Alternate Function, 11: Analog.
 */
void pinMode(GPIO_TypeDef *port, uint8_t pin, uint8_t mode) {
    port->MODER &= ~(3U << (pin * 2)); 
    port->MODER |= (mode << (pin * 2));   
}

/**
 * @brief Sets the state (High/Low) of an output pin.
 * @param port: Pointer to the GPIO port.
 * @param pin: Pin number (0-15).
 * @param state: 1 for HIGH (Set), 0 for LOW (Reset).
 */
void pinSet(GPIO_TypeDef *port, uint8_t pin, uint8_t state) {
    if (state) {
        port->BSRR |= (1U << pin);
    } else {
        port->BSRR |= (1U << (pin + 16));
    }
}

/**
 * @brief Reads the entire Input Data Register (IDR) of a port.
 * @return 32-bit value containing the state of all pins.
 */
uint32_t portRead(GPIO_TypeDef *port) {
    return port->IDR;
}

/**
 * @brief Reads the state of a specific pin.
 * @return 1 if High, 0 if Low.
 */
uint8_t pinRead(GPIO_TypeDef *port, uint8_t pin) {
    return (uint8_t)((port->IDR >> pin) & 1U);
}

// ============================================================================
// TIMER FUNCTIONS
// ============================================================================

/**
 * @brief Generates a delay in milliseconds using TIM2.
 * @note Assumes a peripheral clock frequency of 16MHz.
 * @param ms: Number of milliseconds to wait.
 */
void delay_ms(uint32_t ms) {
    RCC->APB1ENR |= (1 << 0);       
    TIM2->PSC = 16000 - 1;          
    TIM2->ARR = ms;                 
    TIM2->EGR = (1 << 0);           
    TIM2->SR &= ~(1 << 0);          
    TIM2->CR1 |= (1 << 0);          
    while(!(TIM2->SR & (1 << 0)));  
        TIM2->CR1 &= ~(1 << 0);         
}
