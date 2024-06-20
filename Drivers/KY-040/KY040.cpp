/*
 * KY040.cpp
 *
 *  Created on: Jun 19, 2024
 *      Author: isaac
 */
#include <cstdint>
#include "KY040.hpp"
#include "types.hpp"

KY_040::KY_040(
		GPIO_TypeDef* CLKPort,
		uint16_t CLKPin,
		GPIO_TypeDef* DTPort,
		uint16_t DTPin,
		int32_t minValue,
		int32_t maxValue,
		callback0Args toPerform,
		bool perform
		)
: CLKPort(CLKPort),
  CLKPin(CLKPin),
  DTPort(DTPort),
  DTPin(DTPin)
   {

	if(maxValue > minValue){//ensure that the min and max values are setup right;
	    // Clamp minValue to ensure it does not exceed int32_t boundaries
	    if (minValue < INT32_MIN) {
	        this->minValue = INT32_MIN;  // Set minValue to INT32_MIN if it's too low
	    } else if (minValue > INT32_MAX) {
	        this->minValue = INT32_MAX;  // Set minValue to INT32_MAX if it's too high
	    } else {
	        this->minValue = minValue;   // Otherwise, use the provided minValue
	    }

	    // Clamp maxValue to ensure it does not exceed int32_t boundaries
	    if (maxValue < INT32_MIN) {
	        this->maxValue = INT32_MIN;  // Set maxValue to INT32_MIN if it's too low
	    } else if (maxValue > INT32_MAX) {
	        this->maxValue = INT32_MAX;  // Set maxValue to INT32_MAX if it's too high
	    } else {
	        this->maxValue = maxValue;   // Otherwise, use the provided maxValue
	    }
	}else{//if min >= max, than defaults to int32 bounds.
		this -> minValue = INT32_MIN;
		this -> maxValue = INT32_MAX;
	}

	this -> perform = perform;
	this -> toPerform = toPerform;
}

KY_040::~KY_040(void) {

}

void KY_040::setPerform(bool perform){
	this -> perform = perform;
}

bool KY_040::getPerform(void){
	return this -> perform;
}

void KY_040::setSteps(int32_t loadToSteps){
	this -> Steps = loadToSteps;
}

int32_t KY_040::getSteps(void){
	return this -> Steps;
}

void KY_040::resetSteps(void){
	this -> Steps = 0;
}

void KY_040::handleInterrupt(void){

	static int8_t TRANS[] = {0,-1,1,14,1,0,14,-1,-1,14,0,1,14,1,-1,0};//state transition map array
	static uint8_t lrmem = 3;
	static int lrsum = 0;

	int8_t 	CLK, DT;

	CLK = (this-> CLKPort -> IDR & this -> CLKPin)? 1 : 0;//Reads the CLK pin from the encoder
	DT = (this -> DTPort -> IDR & this -> DTPin)? 1 : 0;//Reads the DT pin from the encoder


	lrmem = ((lrmem & 0x03) << 2) + 2*CLK + DT;
	lrsum = lrsum + TRANS[lrmem];

    /* encoder not in the neutral state */
	if(lrsum % 4 != 0){
		__NOP();
		return;
	}
	/* encoder in the neutral state */
	switch(lrsum){
	case 4:
		lrsum=0;
		this -> Steps = this -> Steps + 1 > this -> maxValue? this -> maxValue : this -> Steps + 1;
		if(perform) this -> toPerform();
		break;
	case -4:
		lrsum=0;
		this -> Steps = this -> Steps - 1 < this -> minValue? this -> minValue : this -> Steps - 1;
		if(perform) this -> toPerform();
		break;
	default:
		lrsum=0;
		//showDirection(0);
		break;
	}
}
