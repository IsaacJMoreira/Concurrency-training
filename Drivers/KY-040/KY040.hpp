/*
 * KY040.hpp
 *
 *  Created on: Jun 19, 2024
 *      Author: Isaac Jerônimno Moreira
 *
 *  Description: Just a simple class that is responsible for
 *  decoding a rotary encoder with the use of the external
 *  interrupt. Note that a it receives a callback function
 *  called to perform whenever e click of the encoder is sensed.
 */

#ifndef KY_040_KY040_HPP_
#define KY_040_KY040_HPP_

#include "types.hpp"
#include "stm32f4xx_hal.h"

//weak placeholder function declaration.
__weak void toPerformPlaceholder(){
	__NOP();
}

//actual class
class KY_040 {
public:
	KY_040(
			GPIO_TypeDef* CLKPort,
			uint16_t CLKPin,
			GPIO_TypeDef* DTPort,
			uint16_t DTPin,
			int32_t minValue,
			int32_t maxValue,
			callback0Args toPerform = toPerformPlaceholder,
			bool perform = true
			);
	virtual ~KY_040();
	void setPerform(bool perform);
	bool getPerform(void);
	void setSteps(int32_t loadToSteps);
	int32_t getSteps(void);
	void resetSteps(void);
	void handleInterrupt(void);//needs to be wrapped by a C function and placed in the main.c file.
private:
	GPIO_TypeDef *CLKPort;
	uint16_t CLKPin;
	GPIO_TypeDef *DTPort;
	uint16_t DTPin;
	callback0Args toPerform;
	bool perform;
	int32_t minValue, maxValue, Steps = 0;
};



#endif /* KY_040_KY040_HPP_ */
