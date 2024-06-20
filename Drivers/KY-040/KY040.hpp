/*
 * KY040.hpp
 *
 *  Created on: Jun 19, 2024
 *      Author: isaac
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
	void handleInterrupt(void);
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
