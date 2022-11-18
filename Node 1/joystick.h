#ifndef joystick_h_
#define joystick_h_

#include <avr/io.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdio.h>
#include "basic_defs.h"
#include "adc_driver.h"
#include <math.h>

typedef struct {
	int x;
	int y;
	int left;
	int right;
	int button;
} CONTROL_BOARD;


typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL
} JOYSTICK_DIR;

void joystick_init();
CONTROL_BOARD read_board_positions();
CONTROL_BOARD calibrate_positions(CONTROL_BOARD pos_in);
JOYSTICK_DIR input_joystick_dir(CONTROL_BOARD pos_j);
void print_positions();
void print_joystick_dir(JOYSTICK_DIR dir);
int	left_button_press();
int right_button_press();
int joystick_button_press();

#endif