/*
 * Dice.cpp
 *
 *  Created on: 5 Nov 2016
 *      Author: Konstantin Mishin
 */

#include "Dice.h"
#include "chip.h"
#include "board.h"
#include <stdint.h>

#define MAXLEDS 7
static const uint8_t diceport[] = { 0, 1, 0, 0, 0, 0, 1 };
static const uint8_t dicepins[] = { 0, 3, 16, 10, 9, 29, 9 }; //defines number of leds, their ports, and pins.

int idx=0; //declared as global variable for use in turning all leds on or off.

Dice::Dice() {

Chip_IOCON_PinMuxSet(LPC_IOCON, 0, 8, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
Chip_GPIO_SetPinDIRInput(LPC_GPIO, 0, 8); //defines port 0, pin 8 as input - pullup resistor

Chip_IOCON_PinMuxSet(LPC_IOCON, 1, 6, (IOCON_MODE_PULLUP | IOCON_DIGMODE_EN | IOCON_INV_EN));
Chip_GPIO_SetPinDIRInput(LPC_GPIO, 1, 6); //defines port 1, pin 6, as input - pullup resistor

/*initialize all leds to false state*/
for (idx = 0; idx < MAXLEDS; idx++) {
    Chip_IOCON_PinMuxSet(LPC_IOCON, diceport[idx], dicepins[idx], IOCON_MODE_INACT | IOCON_DIGMODE_EN);
    Chip_GPIO_SetPinDIROutput(LPC_GPIO, diceport[idx], dicepins[idx]);
    Chip_GPIO_SetPinState(LPC_GPIO, diceport[idx], dicepins[idx], false);
}
}


Dice::~Dice() {
}

void Dice::Show_led(){

	/*case numbers 1-6 correspond to actual numbers displayed by leds*/

	switch (Counter()){

	case 1: Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true); break;
	case 2: Chip_GPIO_SetPinState(LPC_GPIO, 0, 0, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, true); break;
	case 3: Chip_GPIO_SetPinState(LPC_GPIO, 0, 0, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true); break;
	case 4: Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 0, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 16, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 1, 9, true); break;
	case 5: Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 0, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 16, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 1, 9, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 10, true); break;
	case 6: Chip_GPIO_SetPinState(LPC_GPIO, 0, 9, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 0, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 16, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 1, 9, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 1, 3, true);
			Chip_GPIO_SetPinState(LPC_GPIO, 0, 29, true); break;
	}
}

uint8_t Dice::Counter(){
	static uint8_t counter = 0;
	Dice counter_control; //I should've simply called a function here instead of object - didn't test and got to like objects :)
	while(counter_control.Patternkey()==false){
		for(counter = 0; counter<6; counter++){
			if(counter==6){
				counter=0;
			}
			if(counter_control.Patternkey()==true){
				break;
			}
		}
	}
	return counter;
}

void Dice::Led_off(){
	for(idx = 0; idx < MAXLEDS; idx++){
	    Chip_GPIO_SetPinState(LPC_GPIO, diceport[idx], dicepins[idx], false);
	}
}

void Dice::Led_on(){
	for(idx = 0; idx < MAXLEDS; idx++){
	    Chip_GPIO_SetPinState(LPC_GPIO, diceport[idx], dicepins[idx], true);
	}
}


/*method for getting test key input - would be better done as bool function, didn't have time to test*/
uint8_t Dice::Testkey(){
	uint8_t ret_test = 0;

	if(Chip_GPIO_GetPinState(LPC_GPIO, 0, 8) == false) {
			ret_test = 1;
		}
	else if(Chip_GPIO_GetPinState(LPC_GPIO, 0, 8) == true){
			ret_test = 0;
		}
	return ret_test;
}

/*method for getting pattern key input*/
uint8_t Dice::Patternkey(){
	uint8_t ret_pattern = 0;

	if(Chip_GPIO_GetPinState(LPC_GPIO, 1, 6) == false) {
			ret_pattern = 1;
		}
	else if(Chip_GPIO_GetPinState(LPC_GPIO, 1, 6) == true){
			ret_pattern = 0;
		}
	return ret_pattern;
}
