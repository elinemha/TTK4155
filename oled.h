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

void oled_init();/*
oled_reset();
oled_home();
oled_goto_line(line);
oled_goto_column(column);
oled_clear_line(line);
oled_pos(row,column);
oled_print(char*);

*/

#endif
