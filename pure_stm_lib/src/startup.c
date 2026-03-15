#include <stdint.h>

extern uint32_t _estack;
extern void main(void);

void Reset_Handler(void);

__attribute__((section(".isr_vector")))
uint32_t *vector_table[] = {
    (uint32_t *)&_estack,     
    (uint32_t *)Reset_Handler  
};

void Reset_Handler(void) {
    main();
    while(1);
}