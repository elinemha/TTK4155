#ifndef oled
#define oled

#include <avr/io.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdint.h>
#include "USART.h"
#include <util/delay.h>
#include <avr/interrupt.h>
#include "basic_defs.h"
#include "SSD1308.h"

void oled_init();
void oled_write_command(uint8_t command)
void oled_write_data(uint8_t data)
void oled_goto_line(uint8_t line);
void oled_goto_column(uint8_t column);
void oled_pos(uint8_t row,uint8_t column);
void oled_reset();
void oled_clear_line(line);/*
oled_home();
oled_print(char*);

*/

#endif
