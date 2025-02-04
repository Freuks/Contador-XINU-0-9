#include <xinu.h>
#include <avr/io.h>

#define DATA_PIN  11 
#define CS_PIN    12 
#define CLK_PIN   13  

void start_spi();
void max7219_send(uint8 endereco, uint8 data);
void start_max7219();
void display_number(uint8 num);
void delay_ms(uint16 ms);

const uint8 number_map[10][8] = {
    {0x00, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18, 0x18}, 0x18 00011000
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

process main(void) {
    start_spi();        
    start_max7219();    

    while (1) {
        for (uint8 i = 0; i < 10; i++) {
            display_number(i);  
            delay_ms(1000);     
        }
    }

    return OK;
}

void start_spi() {
    DDRB |= (1 << PB3) | (1 << PB4) | (1 << PB5);  
    PORTB |= (1 << PB4);  
}

void max7219_send(uint8 endereco, uint8 data) { 
    PORTB &= ~(1 << PB4);  

    for (uint8 i = 0; i < 8; i++) { 
        if (endereco & 0x80) {
            PORTB |= (1 << PB3); 
        } else {
            PORTB &= ~(1 << PB3);
        }
        PORTB |= (1 << PB5);
        PORTB &= ~(1 << PB5);
        endereco <<= 1;
    }

    for (uint8 i = 0; i < 8; i++) { 
        if (data & 0x80) {
            PORTB |= (1 << PB3);
        } else {
            PORTB &= ~(1 << PB3);
        }
        PORTB |= (1 << PB5); 
        PORTB &= ~(1 << PB5); 
        data <<= 1;
    }

    PORTB |= (1 << PB4); 
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

void delay_ms(uint16 ms) { 
    for (uint16 i = 0; i < ms; i++) {
        for (uint16 j = 0; j < 4000; j++) {
            asm volatile ("nop");
        }
    }
}
