/*
 * FrameBuilder.cpp
 *
 *  Created on: Jun 26, 2024
 *      Author: isaac
 */

/****************************************************/
/*                 C includes                       */
/****************************************************/
extern "C"
{
#include "../LCD/lcd.h"
}
/****************************************************/
/*                 CPP includes                     */
/****************************************************/
#include <cstdint>
#include "FrameBuilder.hpp"
#include "Assets.hpp"
#include <cmath>
using namespace std;
//////////////////////////////////////////////////////

Frame_Builder::Frame_Builder() {
	// TODO Auto-generated constructor stub

}

Frame_Builder::~Frame_Builder() {
	// TODO Auto-generated destructor stub
}

//Translates and draws tile on screen. Any tile
void Frame_Builder::FB_Draw8bitTile(
								uint8_t xi,
								uint8_t yi,
								uint8_t xe,
								uint8_t ye,
								const uint16_t palette[],
								void (*func)(UG_S16, UG_S16, UG_COLOR),
								const uint8_t tile[],
								uint8_t transColor,
								bool setTrans
								)
{
	// check if the tile is not empty
	uint8_t width = ye - yi + 1;
	uint8_t height = xe - xi + 1;
	if (width < 1|| height < 1) return;


	 for(uint16_t Y = 0; Y < width; Y++){
		 for(uint16_t X = 0; X < height; X++){
			 uint16_t position = X + Y * width;
			 uint8_t color = tile[position];
			 if(setTrans){
				 if(color != transColor){
					 uint8_t pixel16bits = tile[position];
				 	 func(X + xi, Y + yi, palette[pixel16bits]);
			     }
			 }else{
				 uint8_t pixel16bits = tile[position];
				 func(X + xi, Y + yi, palette[pixel16bits]);
			 }
		 }
 	 }
 }

void Frame_Builder::FB_SimpleBGPartialDraw(
								uint16_t xi,
								uint16_t yi,
								uint16_t xe,
								uint16_t ye,
								uint16_t BGHeight,
								uint16_t BGWidth,
								const uint16_t palette[],
								void (*func)(UG_S16, UG_S16, UG_COLOR),
								const uint8_t tile[]
								)
{
	uint32_t tileArrSize = BGHeight*BGWidth;
	uint16_t portionWidth = xe - xi + 1;
	uint16_t portionHeight = ye - yi + 1;
	uint32_t portionArrSize = portionWidth * portionHeight;

	//condom against dumb programmer AIDS
	if ((portionArrSize > tileArrSize)||
		 (xi + portionWidth > BGWidth)||
		 (yi + portionHeight > BGHeight)||
		 (tileArrSize == 0)||
		 (portionArrSize ==0)) return;


	 for(uint16_t Y = 0; Y < portionHeight; Y++){
		 for(uint16_t X = 0; X < portionWidth; X++){
			 uint32_t position = X + xi + (Y + yi) * BGWidth;
			 uint8_t color = tile[position];

			 uint8_t pixel16bits = tile[position];
			 func(X + xi, Y + yi, palette[pixel16bits]);

		 }
 	 }
 }

void Frame_Builder::FB_LongBGPartialDraw(
								//window coordinates, relative to the screen
								uint16_t windowXi,
								uint16_t windowYi,
								uint16_t windowXf,
								uint16_t windowYf,
								//visible area of the background (screen) relative to the background
								uint16_t screenX,
								uint16_t screenY,
								uint8_t  screenHeight,
								uint8_t  screenWidth,
								//background data
								uint16_t BGHeight,
								uint16_t BGWidth,
								const uint16_t palette[],
								void (*func)(UG_S16, UG_S16, UG_COLOR),
								const uint8_t tile[]
								)
{
	//draws a piece of the background inside the screen, all relative to the background.
	//we make sure everything is in order:
	uint16_t windowWidth = windowXf - windowXi + 1;
	uint16_t windowHeight = windowYf - windowYi + 1;
	if(
			(windowWidth > screenWidth) ||
			(windowHeight > screenHeight)||
			(screenHeight > BGHeight) ||
			(screenWidth > BGWidth) ||
			(windowXi + windowWidth > BGWidth)||
			(windowYi + windowHeight > BGHeight)
			) return;


	for(uint32_t Y = 0; Y < windowWidth; Y++ ){
		for(uint32_t X = 0; X < windowHeight; X++){
			uint32_t pixel8bits = (screenX +  windowXi + X) + (screenY + windowYi + Y) * BGWidth;
			func(X + windowXi, Y + windowYi, palette[tile[pixel8bits]]);
		}
	}
}

void Frame_Builder::FB_AssembleFrame(){

}

