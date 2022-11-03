/*
 * CFile1.c
 *
 * Created: 03.11.2022 16:07:16
 *  Author: elinemha
 */ 

#include <stdio.h>
#include "sam.h"
#include "sam3x8e.h"
#include <stdint.h>
#include <stdlib.h>

#define LED1 PIO_PA19
#define LED2 PIO_PA20

void sam_leds()
{
 PIOA->PIO_PER |= (LED1 | LED2);
 PIOA->PIO_OER |= (LED1|LED2);
 PIOA->PIO_SODR |= (LED1|LED2);
}