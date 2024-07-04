//TODO get rid of UGUI inside the LCD lib.

/*********************************************************/
//CPP INCLUDES
#include <string>
#include <stdio.h>
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

FB_8bitBMP DESERT = {
	 .p = LONG_BG,
	 .width = 731,
	 .height = 240,
	 .palette = main8bitsPalette,
};

#define DEFAULT_FONT FONT_6X8
QueueableClass beep;
Frame_Builder FB(240,240,&LCD_DrawPixelFB);

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
		-1,
	   36,
		beepActionWrapper
		);

void floatToString(float value, char* buffer, int bufferSize, int precision = 2) {
    int intPart = (int)value;  // Integer part
    int decPart = 0;

    // Compute decimal part manually
    float remainder = value - intPart;
    for (int i = 0; i < precision; ++i) {
        remainder *= 10;
        decPart = decPart * 10 + int(remainder) % 10;
        remainder -= int(remainder);
    }

    snprintf(buffer, bufferSize, "%d.%0*d fps", intPart, precision, decPart);
}
//CPP ENTRY POINT
void MainCPP(){

	//SETUP START
	LCD_init();
	FB.setBackground(DESERT);
	GPIOC -> ODR |= GPIO_PIN_13;//onboard blue led OFF
   FB.FB_LongBGPartialDraw(
									0,
									0,
									239,
									239,
									0,
									0
									);
	//FB.FB_SimpleBGPartialDraw(0, 0, 239, 239, 240, 240, main8bitsPalette, &LCD_DrawPixelFB, SKULL);
	uint16_t x = 0, y = 100;
	uint16_t X = 0;
	uint16_t prevX = x;
	uint16_t prevY = y;
	//END SETUP

	//MAIN LOOP START
	while(1){
		uint32_t startTime = HAL_GetTick();
		GPIOB -> ODR ^= GPIO_PIN_10;







		uint16_t steps =(uint16_t)encoder.getSteps();
		if((steps < 36) && (steps > -1)){
			x = steps * 5;
			FB.FB_LongBGPartialDraw(
														prevX,
														prevY,
														prevX + 64,
														prevY + 64,
														X,
														0
														);
		}else{
			if(steps == 36){
				X = X + 10 > 731-240? 731-240 : X+10;
				encoder.setSteps(35);
			}else{
				X = X - 10 < 0? 0 : X-10;
				encoder.setSteps(0);
			}
			FB.FB_LongBGPartialDraw(
														0,
														0,
														239,
														239,
														X,
														0
														);
		}

		//FB.FB_SimpleBGPartialDraw(prevX, prevY, prevX+63, prevY+63, 240, 240, main8bitsPalette, &LCD_DrawPixelFB, SKULL);
		FB.FB_Draw8bitTile(x, y, x+63, y+63, main8bitsPalette, SHIP, 0xff, true);//sprite
		//FB.FB_Draw8bitTile((240-64)/2, (240-64)/2, (240-64)/2 + 63, (240-64)/2 + 63, main8bitsPalette, &LCD_DrawPixelFB, SHIP, 0xff, true);//sprite
		prevX = x;
		prevY = y;

		std::string str;


		// Assuming startTime is defined elsewhere and HAL_GetTick() returns time in milliseconds
		float FPS = 1000.0f / (HAL_GetTick() - startTime);
		    char strBuffer[20]; // Adjust the size as per your requirement

		    floatToString(FPS, strBuffer, sizeof(strBuffer));

		    // Assuming LCD_PutStr() function displays the string on LCD
		    //LCD_PutStr(10, 15, strBuffer, DEFAULT_FONT, 0x0000, 0xffff);//TODO
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

