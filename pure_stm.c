#include "stdint.h"
#include "pure_stm.h"

// ============================================================================
// RCC FUNCTIONS
// ============================================================================

/**
 * @brief Initializes the system clock.
 * @param clk_source: 0 for HSI (Internal), 1 for HSE (External).
 * @param pll_set: Enable (1) or disable (0) the PLL.
 * @param clk_frequency: Reserved for future frequency scaling logic.
 */
void clock_init(uint8_t clk_source, uint8_t pll_set, uint8_t clk_frequency) {
    if (!clk_source) {
        RCC->CR |= (1 << 0);
        if (pll_set) {
            RCC->CR |= (1 << 24);
        }
    }
    // TODO: Implement HSE logic and wait for READY bits (stability check)
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