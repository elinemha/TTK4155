#ifndef oled_h_
#define oled_h_

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "USART.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "basic_defs.h"
//#include "SSD1308.h"

void oled_init();
void oled_write_command(uint8_t command);
void oled_write_data(uint8_t data);
void display_on();
void oled_goto_line(uint8_t page);
void oled_goto_column(uint8_t column);
void oled_pos(uint8_t page,uint8_t column);
void oled_reset();
void oled_clear_line(uint8_t page);/*
oled_home();
oled_print(char*);

*/

#endif
