#include <avr/io.h>
#include <stdint.h>
#include "lcd.h"
#define F_CPU 16000000UL
#include <util/delay.h>

void adc_init(uint8_t);
void adc_read();

uint8_t btn_prev_state = 0;

int main() {
    DDRB &= ~1;

    adc_init(0);

    lcd_init();

	while(1) {
		uint8_t curr_btn_state = PINB & 1;
		if(curr_btn_state && !btn_prev_state) {
			adc_read();
			lcd_clear();
			write_int(ADC);
		}
		btn_prev_state = curr_btn_state;
	}

    return 0;
}

void adc_init(uint8_t pin) {
	ADMUX |= (1 << REFS0) | pin;
	ADCSRA |= (1 << ADEN);
}

void adc_read() {
	ADCSRA |= (1 << ADSC) | (1 << ADPS2) | (1 << ADPS1) | (1 << ADPS0);

	while(ADCSRA & 0x40);
}