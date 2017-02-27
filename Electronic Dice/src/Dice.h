/*
 * Dice.h
 *
 *  Created on: 5 Nov 2016
 *      Author: Obj.M19-Gloria
 */

#ifndef DICE_H_
#define DICE_H_
#include <stdint.h>

class Dice {
public:
	Dice();
	virtual ~Dice();
	void Show_led();
	void Led_on();
	void Led_off();
	uint8_t Testkey();
	uint8_t Patternkey();
private:
	uint8_t Counter();
};

#endif /* DICE_H_ */
