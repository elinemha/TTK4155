#include "joystick.h"


//#define ADC_BASE_ADDRESS 0x1400
#define NUMBER_OF_CHANNELS 4
#define JOYSTICK_DIRECTION_X 0
#define JOYSTICK_DIRECTION_Y 1
#define LEFT_SLIDER 2
#define RIGHT_SLIDER 3


void joystick_init()
{
	PORTB |= (1<<PB2);
	DDRB |= (1<<DDB2);
}

CONTROL_BOARD read_board_positions()
{
	CONTROL_BOARD pos_j;
	pos_j.x = (int)adc_read(JOYSTICK_DIRECTION_X);
	pos_j.y = (int)adc_read(JOYSTICK_DIRECTION_Y);
	pos_j.left = (int)adc_read(LEFT_SLIDER);
	pos_j.right = (int)adc_read(RIGHT_SLIDER);
	pos_j.button =  (PIND & (1<< PD5));
	return pos_j;
}

CONTROL_BOARD calibrate_positions(CONTROL_BOARD pos_in)
{
	CONTROL_BOARD pos_out;

	pos_out.x		 = pos_in.x - 127;
	pos_out.y		 = pos_in.y - 127;
	pos_out.left = pos_in.left - (255/pos_in.left) + 1;
	pos_out.right = pos_in.right - (255/pos_in.right) + 1;
	pos_out.button = pos_in.button;

	if(pos_out.x > 127)
	{
		pos_out.x = 127;
	}
	if(pos_out.y > 127)
	{
		pos_out.y = 127;
	}

	pos_out.x = pos_in.x*100/127;
	pos_out.y = pos_in.y*100/127;

	return pos_out;
}

JOYSTICK_DIR input_joystick_dir(CONTROL_BOARD pos_j)
{
	if (pos_j.x > 35)
	{
		if (pos_j.y > 40)
		{
			if(pos_j.y > pos_j.x + 7)
			{
				return UP;
			}
			else
			{
				return RIGHT;
			}
		}
		else
		{
			if(abs(pos_j.y) > pos_j.x + 1)
			{
				return DOWN;
			}
			else
			{
				return RIGHT;
			}
		}
	}
	else if (pos_j.x < -20)
	{
		if (pos_j.y > 40)
		{
			if(pos_j.y > abs(pos_j.x) + 28)
			{
				return UP;
			}
			else
			{
				return LEFT;
			}
		}
		else
		{
			if(abs(pos_j.y) > abs(pos_j.x) + 5)
			{
				return DOWN;
			}
			else
			{
				return LEFT;
			}
		}
	}
	else
	{
		if (pos_j.y > 40)
		{
			return UP;
		}
		else if (pos_j.y < -20)
		{
			return DOWN;
		}
		else
		{
			return NEUTRAL;
		}
	}
}

void print_positions(CONTROL_BOARD pos)
{
	printf("Joystick X Position: %4d\n ", pos.x);
	printf("Joystick Y Position: %4d\n ", pos.y);
	printf("Left Slider Position: %4d\n ", pos.left);
	printf("Right Slider Position: %4d\n ", pos.right);
}

void print_joystick_dir(JOYSTICK_DIR dir)
{
	switch(dir)
	{
		case UP:
			printf("Joystick Direction is UP!!!\n");
			break;
		case DOWN:
			printf("Joystick Direction is DOWN!!!\n");
			break;
		case LEFT:
			printf("Joystick Direction is LEFT!!!\n");
			break;
		case RIGHT:
			printf("Joystick Direction is RIGHT!!!\n");
			break;
		case NEUTRAL:
			printf("Joystick Direction is NEUTRAL!!!\n");
			break;
		default:
			break;
	}
}

int right_button_press(){
	if (PINB & (1<<PB1))
	{
		printf("Right button pressed\n");
		return 1;
	}
	return 0;
}

int left_button_press(){
	if (PINB & (1<<PB2))
	{
		printf("Left button pressed\n");
		return 1;
	}
	return 0;
}

int joystick_button_press(){
	return (PIND & (1<< PD4));
}