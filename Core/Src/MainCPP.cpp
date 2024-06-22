/*********************************************************/
//CPP INCLUDES
#include "MainCPP.hpp"
#include "../../Drivers/KY-040/KY040.hpp"
#include "../../Drivers/Async_Event_Loop/AsyncEventLoop.hpp"
#include "../../Drivers/Async_Event_Loop/Types.hpp"
/*********************************************************/
//C INCLUDES
extern "C"
{
#include <stdint.h>
#include "main.h"
#include "stm32f4xx_hal.h"
}
/*********************************************************/


QueueableClass beep;
Async_Event_Loop AsyncEventLoop;
	//TODO FIND A WAY TO SIMPLIFY THIS
	//IT NEEDS THIS WRAPPER TO CONFORM TO THE EXPECTED FUNCTION SIGNATURE
	void beepActionWrapper(){
		AsyncEventLoop.enqueue(beep);
	}
	//Instantiate a KY-040 encoder;
KY_040 encoder(
		GPIOA,
		GPIO_PIN_2,
		GPIOA,
		GPIO_PIN_1,
		-10,
		10,
		beepActionWrapper
		);
//CPP ENTRY POINT
void MainCPP(){

	//SETUP START

	GPIOC -> ODR |= GPIO_PIN_13;//onboard blue led OFF
	//END SETUP

	//MAIN LOOP START
	while(1){

		int32_t count = encoder.getSteps();
		if(count == 10) GPIOC -> ODR &= ~GPIO_PIN_13;//onboard blue led ON
		else if (count ==-10) GPIOC -> ODR |= GPIO_PIN_13;//onboard blue led OFF

		GPIOB -> ODR ^= GPIO_PIN_10;
		HAL_Delay(100);

	}
	//END MAIN LOOP
}

/*********************************************************/
/*               AWAYS LEAVE IT FOR LAST                 */
/*********************************************************/
extern "C"//TODO FIND A WAY TO SIMPLIFY THIS
{
	void EVENT_LOOP_WRAPPER(void){
		AsyncEventLoop.ASYNC_LOOP();
	}
	void RotaryEncoderWrapper(){//TODO This needs to be done here
		encoder.handleInterrupt();
	}
	void MainC(){
		MainCPP();
	}
}

