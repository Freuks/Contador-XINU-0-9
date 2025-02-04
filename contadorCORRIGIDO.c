#include <xinu.h>
#include "avr_gpio.h"

#define DATA_PIN  11 
#define CS_PIN    12 
#define CLK_PIN   13  
#define LED_PIN   PB0  

void start_spi();
void max7219_send(uint8 endereco, uint8 data);
void start_max7219();
void display_number(uint8 num);
void toggle_led();

sid32 display_ready;

const uint8 number_map[10][8] = {
    {0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18},
    {0x3C, 0x42, 0x02, 0x1C, 0x20, 0x42, 0x42, 0x3C},  
    {0x3C, 0x42, 0x02, 0x1C, 0x02, 0x42, 0x42, 0x3C},  
    {0x08, 0x18, 0x28, 0x48, 0x7E, 0x08, 0x08, 0x08},  
    {0x7E, 0x40, 0x40, 0x7C, 0x02, 0x02, 0x42, 0x3C},  
    {0x1C, 0x20, 0x40, 0x7C, 0x42, 0x42, 0x42, 0x3C},  
    {0x7E, 0x42, 0x02, 0x04, 0x08, 0x10, 0x10, 0x10},  
    {0x3C, 0x42, 0x42, 0x3C, 0x42, 0x42, 0x42, 0x3C},  
    {0x3C, 0x42, 0x42, 0x3E, 0x02, 0x04, 0x08, 0x70},  
    {0x3C, 0x42, 0x42, 0x42, 0x42, 0x42, 0x42, 0x3C},  
};

void start_spi() {
    gpio_setmode(&DDRB, PB3, GPIO_OUTPUT);
    gpio_setmode(&DDRB, PB4, GPIO_OUTPUT);
    gpio_setmode(&DDRB, PB5, GPIO_OUTPUT);
    gpio_write(&PORTB, PB4, HIGH);
}

void max7219_send(uint8 endereco, uint8 data) { 
    gpio_write(&PORTB, PB4, LOW);

    for (uint8 i = 0; i < 8; i++) { 
        gpio_write(&PORTB, PB3, (endereco & 0x80) ? HIGH : LOW);
        gpio_write(&PORTB, PB5, HIGH);
        gpio_write(&PORTB, PB5, LOW);
        endereco <<= 1;
    }

    for (uint8 i = 0; i < 8; i++) { 
        gpio_write(&PORTB, PB3, (data & 0x80) ? HIGH : LOW);
        gpio_write(&PORTB, PB5, HIGH);
        gpio_write(&PORTB, PB5, LOW);
        data <<= 1;
    }

    gpio_write(&PORTB, PB4, HIGH);
}

void start_max7219() { 
    max7219_send(0x09, 0x00);
    max7219_send(0x0A, 0x0F);
    max7219_send(0x0B, 0x07);
    max7219_send(0x0C, 0x01);
    max7219_send(0x0F, 0x00);
}

void display_number(uint8 num) { 
    for (uint8 row = 0; row < 8; row++) {
        max7219_send(row + 1, number_map[num][row]);
    }
}

void toggle_led() {
    gpio_write(&PORTB, LED_PIN, !(*(&PORTB) & (1 << LED_PIN)));
}

int display_process(int nargs, char *args[]) {
    while (1) {
        wait(display_ready);
        for (uint8 i = 0; i < 10; i++) {
            display_number(i);
            toggle_led();
            sleep(1);
        }
        signal(display_ready);
    }
    return 0;
}

process main(void) {
    start_spi();        
    start_max7219();    

    gpio_setmode(&DDRB, LED_PIN, GPIO_OUTPUT);
    gpio_write(&PORTB, LED_PIN, LOW);

    display_ready = semcreate(1);

    resume(create(display_process, 256, 20, "DisplayProcess", 0));

    return OK;
}