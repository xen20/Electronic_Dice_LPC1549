/*
===============================================================================
 Name        : main.c
 Author      : Konstantin Mishin
 Version     :
 Copyright   : $(copyright)
 Description : main definition
===============================================================================
*/

#if defined (__USE_LPCOPEN)
#if defined(NO_BOARD_LIB)
#include "chip.h"
#else
#include "board.h"
#endif
#endif

#include <cr_section_macros.h>
#include "Dice.h"

// TODO: insert other include files here

// TODO: insert other definitions and declarations here

int main(void) {

#if defined (__USE_LPCOPEN)
    // Read clock settings and update SystemCoreClock variable
    SystemCoreClockUpdate();
#if !defined(NO_BOARD_LIB)
    // Set up and initialize all required blocks and
    // functions related to the board hardware
    Board_Init();
    // Set the LED to the state of "On"
    Board_LED_Set(0, true);
#endif
#endif

	Dice gamble;

    while(1) {
    	if(gamble.Testkey()){
    		gamble.Led_off();
    	}
    	else if(gamble.Testkey() == false){
    		gamble.Led_on();
    	}
    	if(gamble.Patternkey() == false){
    		while(gamble.Testkey() == true){
        		gamble.Show_led();
    		}
    	}
		gamble.Testkey();
		gamble.Patternkey(); //consistently polls the two buttons while program is running
    }
}
