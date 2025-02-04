#ifndef AVR_GPIO_H
#define AVR_GPIO_H

#include <avr/io.h>


#define GPIO_OUTPUT 1
#define GPIO_INPUT  0
#define HIGH        1
#define LOW         0

static inline void gpio_setmode(volatile uint8_t *ddr, uint8_t pin, uint8_t mode) {
    if (mode == GPIO_OUTPUT) {
        *ddr |= (1 << pin);
    } else {
        *ddr &= ~(1 << pin);
    }
}


static inline void gpio_write(volatile uint8_t *port, uint8_t pin, uint8_t value) {
    if (value == HIGH) {
        *port |= (1 << pin);
    } else {
        *port &= ~(1 << pin);
    }
}

#endif

