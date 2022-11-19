/*
 * controller.h
 *
 * Created: 16.11.2022 13:20:17
 *  Author: emmalle
 */ 


#ifndef CONTROLLER_H_
#define CONTROLLER_H_

#include "sam.h"
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>

void controller_init();
int16_t position_controller(int16_t enc_data, uint8_t slider_pos);

#endif /* CONTROLLER_H_ */