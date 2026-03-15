#include "pure_stm.h"

uint32_t SystemCoreClock = 16000000;

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
                SystemCoreClock = HSI_VALUE;
                break;
            case HSE:
                FLASH->ACR &= ~0x7;
                RCC->CR |= (1 << 16);
                while(!(RCC->CR & (1 << 17)));
                RCC->CFGR &= ~((1 << 1) | (1 << 0));
                RCC->CFGR |= (1 << 0);
                while((RCC->CFGR & (0x3 << 2)) != (1 << 2));
                RCC->CR &= ~(1 << 24);
                SystemCoreClock = HSE_VALUE;
                break;
            case PLL:
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
                SystemCoreClock = PPL_VALUE;
                break;
            default: break;
        }
    }
/**
 * @brief  Enables the clock for all peripherals on a specific bus.
 * @param  bus: The target bus to be enabled (e.g., BUS_AHB1, BUS_APB2).
 */
void periph_bus_enable(Bus_t bus){
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
        default: break;
    }
    __asm("nop");
    __asm("nop");
}

/**
 * @brief  Enables the clock for a specific peripheral.
 * @param  periph: The peripheral to be enabled (from Peripheral_t enum).
 * @retval None
 */
void periph_enable(Peripheral_t periph) {
    switch(periph) {
        case PERIPH_GPIOA:  RCC->AHB1ENR |= (1 << 0);  break;
        case PERIPH_GPIOB:  RCC->AHB1ENR |= (1 << 1);  break;
        case PERIPH_GPIOC:  RCC->AHB1ENR |= (1 << 2);  break;
        case PERIPH_GPIOD:  RCC->AHB1ENR |= (1 << 3);  break;
        case PERIPH_GPIOH:  RCC->AHB1ENR |= (1 << 7);  break;
        case PERIPH_CRC:    RCC->AHB1ENR |= (1 << 12); break;
        case PERIPH_DMA1:   RCC->AHB1ENR |= (1 << 21); break;
        case PERIPH_DMA2:   RCC->AHB1ENR |= (1 << 22); break;
        case PERIPH_OTGFS:  RCC->AHB2ENR |= (1 << 7);  break;
        case PERIPH_TIM2:   RCC->APB1ENR |= (1 << 0);  break;
        case PERIPH_TIM3:   RCC->APB1ENR |= (1 << 1);  break;
        case PERIPH_TIM4:   RCC->APB1ENR |= (1 << 2);  break;
        case PERIPH_TIM5:   RCC->APB1ENR |= (1 << 3);  break;
        case PERIPH_WWDG:   RCC->APB1ENR |= (1 << 11); break;
        case PERIPH_SPI2:   RCC->APB1ENR |= (1 << 14); break;
        case PERIPH_SPI3:   RCC->APB1ENR |= (1 << 15); break;
        case PERIPH_USART2: RCC->APB1ENR |= (1 << 17); break;
        case PERIPH_I2C1:   RCC->APB1ENR |= (1 << 21); break;
        case PERIPH_I2C2:   RCC->APB1ENR |= (1 << 22); break;
        case PERIPH_I2C3:   RCC->APB1ENR |= (1 << 23); break;
        case PERIPH_PWR:    RCC->APB1ENR |= (1 << 28); break;
        case PERIPH_TIM1:   RCC->APB2ENR |= (1 << 0);  break;
        case PERIPH_USART1: RCC->APB2ENR |= (1 << 4);  break;
        case PERIPH_USART6: RCC->APB2ENR |= (1 << 5);  break;
        case PERIPH_ADC1:   RCC->APB2ENR |= (1 << 8);  break;
        case PERIPH_SPI1:   RCC->APB2ENR |= (1 << 12); break;
        case PERIPH_SPI4:   RCC->APB2ENR |= (1 << 13); break;
        case PERIPH_SYSCFG: RCC->APB2ENR |= (1 << 14); break;
        case PERIPH_TIM9:   RCC->APB2ENR |= (1 << 16); break;
        case PERIPH_TIM10:  RCC->APB2ENR |= (1 << 17); break;
        case PERIPH_TIM11:  RCC->APB2ENR |= (1 << 18); break;
        default: break;
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


void delay_ms(uint32_t ms) {
 
    SysTick->LOAD = (SystemCoreClock / 1000) - 1;
    SysTick->VAL = 0; 
    SysTick->CTRL = 5; 
    for (uint32_t i = 0; i < ms; i++) {
        while (!(SysTick->CTRL & (1 << 16)));
    }
    SysTick->CTRL = 0;
}