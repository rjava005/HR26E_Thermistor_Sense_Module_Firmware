#include "stm32f4xx.h"

void delay(volatile uint32_t count) {
    while(count--) { __asm__("nop"); }
}

int main(void) {
    //REPLACE with main thermistor watchdog function (for faulting) as well as CAN1 tx rx set up
    //ADC clock set up in here as well, and function call for reading ADC from MUX pin 

    // Enable GPIOD clock
    RCC->AHB1ENR |= RCC_AHB1ENR_GPIODEN;


    GPIOD->MODER |= (1 << (12 * 2));

    while (1) {
        GPIOD->ODR ^= (1 << 12);  // Toggle LED
        delay(1000000);
    }
}