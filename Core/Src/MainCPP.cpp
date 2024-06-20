/*********************************************************/
//CPP INCLUDES
#include "MainCPP.hpp"
#include "../../KY-040/KY040.hpp"
/*********************************************************/
//C INCLUDES
extern "C"
{
#include <stdint.h>
#include "main.h"
#include "stm32f4xx_hal.h"
}
/*********************************************************/
void beep(void);
//Instantiate a KY-040 encoder;
KY_040 encoder(
		GPIOA,
		GPIO_PIN_2,
		GPIOA,
		GPIO_PIN_1,
		-10,
		10,
		beep
		);
//CPP ENTRY POINT
void MainCPP(){

	//SETUP START

	//END SETUP

	//MAIN LOOP START
	while(1){
		GPIOB -> ODR ^= GPIO_PIN_10;
		HAL_Delay(100);
	}
	//END MAIN LOOP
}

void beep(void){//demonstration only.
	GPIOB -> ODR |= GPIO_PIN_2;//SET BEEPER PIN
	for(uint32_t _ = 0; _ < 500000; _++){
		__NOP();
	}
    //HAL_Delay(5);//can't use this HAL function because the delay uses interrupts too, at a lower priority.
	GPIOB -> ODR &= ~GPIO_PIN_2;
}

/*********************************************************/
/*               AWAYS LEAVE IT FOR LAST                 */
/*********************************************************/
extern "C"
{
	void RotaryEncoderWrapper(){
		encoder.handleInterrupt();
	}
	void MainC(){
		MainCPP();
	}
}

