#include "pure_stm.h"

int main(void) {
    clock_init(HSI); 
    periph_enable(PERIPH_GPIOA);
    pinMode(GPIOA, 5, OUTPUT);
    while(1) {
        pinSet(GPIOA, 5, HIGH);
        delay_ms(500);
        pinSet(GPIOA, 5, LOW);
        delay_ms(500);
    }
}