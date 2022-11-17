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
} JOYSTICK_POS;


typedef enum {
	LEFT,
	RIGHT,
	UP,
	DOWN,
	NEUTRAL
} JOYSTICK_DIR;

/*typedef struct {
	int left;
	int right;
} SLIDER_POS;
*/

JOYSTICK_POS read_joystick_pos();
//SLIDER_POS read_slider_pos();
//JOYSTICK_POS calibrate_slider_pos(JOYSTICK_POS pos_s_in);
JOYSTICK_POS joystick_analog_pos(JOYSTICK_POS pos_j_in);
JOYSTICK_DIR input_joystick_dir(JOYSTICK_POS pos_j);

void print_joystick_pos();
//void print_slider_pos(SLIDER_POS pos);
void print_joystick_dir(JOYSTICK_DIR dir);
int	left_button_press();
int right_button_press();
int joystick_button_press();
void joystick_init();



#endif