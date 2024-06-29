/*********************************************************/
//CPP INCLUDES
#include <string>
#include "MainCPP.hpp"
#include "../../Drivers/KY-040/KY040.hpp"
#include "../../Drivers/Async_Event_Loop/AsyncEventLoop.hpp"
#include "../../Drivers/Async_Event_Loop/Types.hpp"
#include "../../Drivers/Frame_Builder/Assets.hpp"
#include "../../Drivers/Frame_Builder/FrameBuilder.hpp"
/*********************************************************/
//C INCLUDES
extern "C"
{
#include <stdint.h>
#include "main.h"
#include "stm32f4xx_hal.h"
#include "../../Drivers/LCD/lcd.h"//ST7789 driver
}
/*********************************************************/

#define DEFAULT_FONT FONT_6X8
QueueableClass beep;
Frame_Builder FB;

//Extension of QueueableClass for demonstration purposes only. Must me done in other file.
class flashOnce: public QueueableClass{
public:
	void EXECUTE(void){
			 //simple implementation of method to make a beep for 5ms;

			 static uint32_t prevTime = 0;
			 static uint32_t currentTime = 0;
			 uint32_t elapsedTime;
			 static uint8_t state = 0;

			 if(getState() == TODO){
			 	state = 1;
			 	setState(DOING);
			   	prevTime = HAL_GetTick();//get the time when the change accurred
			 }

			 if(state){//if the function is in the on state, turns the toPerform on;
			   	GPIOA -> ODR |= GPIO_PIN_4;//SET BUZZER PIN;
			   	//now we check if the delay time has elapsed.
			   	//first we acquire the current time
			  	currentTime = HAL_GetTick();
			   	if (currentTime >= prevTime) {//making sure to account for roll over
			   		elapsedTime = currentTime - prevTime;
			   	} else {
			   		elapsedTime = (UINT32_MAX - prevTime) + currentTime + 1;
			   	}
			   	//if the time has run out, we turn the toPerform off
			   	if(elapsedTime >= 1000){
			   		GPIOA -> ODR &= ~GPIO_PIN_4; //RESET BUZZER PIN;
			   		state = 0;//we clear the state.
			   		setState(DONE);//WE SIGNAL IT ENDED EXECUTION;
			   	}
			   }
		 }

};

flashOnce flashOnce;
Async_Event_Loop AsyncEventLoop;
	//TODO FIND A WAY TO SIMPLIFY THIS
	//IT NEEDS THIS WRAPPER TO CONFORM TO THE EXPECTED FUNCTION SIGNATURE
	void beepActionWrapper(){
		AsyncEventLoop.enqueue(&beep);
	}
	void ButtonEncoderWrapper(){
		AsyncEventLoop.enqueue(&flashOnce);
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
	LCD_init();
	GPIOC -> ODR |= GPIO_PIN_13;//onboard blue led OFF
	//END SETUP

	//MAIN LOOP START
	while(1){
		uint32_t startTime = HAL_GetTick();
		//UG_FillFrame(0, 0, 64, 32, 0xffff);
		GPIOB -> ODR ^= GPIO_PIN_10;
		//HAL_Delay(100);
		FB.FB_Draw8bitTile(0,0, 240,main8bitsPalette, &LCD_DrawPixelFB, SKULL, 0x00, false);
		std::string str;
		uint8_t t = UG_FontGetTransparency();
		uint32_t FPF = 1000/(HAL_GetTick()-startTime);
		str = std::to_string(FPF) + " fps";
		LCD_PutStr(10, 15, &str[0], DEFAULT_FONT, 0x0000, 0xffff );

		LCD_Update();
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

