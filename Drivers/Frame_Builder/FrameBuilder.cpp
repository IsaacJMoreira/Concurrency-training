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

Frame_Builder::Frame_Builder(uint16_t screenWidth, uint16_t screenHeight, void (*drawDependency)(int16_t, int16_t, uint16_t)):
		screenWidth(screenWidth),
		screenHeight(screenHeight),
		func(drawDependency)
{
	// TODO Auto-generated constructor stub
}

Frame_Builder::~Frame_Builder() {
	// TODO Auto-generated destructor stub
}

void Frame_Builder::setSpriteMap(FB_SpriteMap spriteMap){
	this->noSpritesFlag = false;//hey, now we have a prite map!
	this->spriteMap = spriteMap;
}

void Frame_Builder::setBackground(FB_8bitBMP background){
	this->noBGFlag = false;//hey, now we have a BG!
	this->background = background;
}

//Translates and draws tile on screen. Any tile
void Frame_Builder::FB_Draw8bitTile(
								uint8_t xi,
								uint8_t yi,
								uint8_t xe,
								uint8_t ye,
								const uint16_t palette[],//we need the palet here to allow each tile to have its own palette if need be
								const uint8_t tile[],
								uint8_t transColor,
								bool setTrans
								)
{

	uint8_t width = ye - yi + 1;
	uint8_t height = xe - xi + 1;

	if (
			(width < 1|| height < 1)||
			(width > screenWidth)||
			(height > screenHeight)||
			(this -> screenHeight < xi)||
			(this -> screenHeight < xe)||
			(this -> screenWidth  < yi)||
			(this -> screenWidth  < ye)) return;


	 for(uint16_t Y = 0; Y < width; Y++){
		 for(uint16_t X = 0; X < height; X++){
			 uint16_t position = X + Y * width;
			 uint8_t color = tile[position];
			 if(setTrans){
				 if(color != transColor){
					 uint8_t pixel16bits = tile[position];
				 	 this->func(X + xi, Y + yi, palette[pixel16bits]);
			     }
			 }else{
				 uint8_t pixel16bits = tile[position];
				 func(X + xi, Y + yi, palette[pixel16bits]);
			 }
		 }
 	 }
 }

void Frame_Builder::FB_SimpleBGPartialDraw(
		                        //relative to the little windows
								uint16_t xi,
								uint16_t yi,
								uint16_t xe,
								uint16_t ye
								)
{
	uint32_t tileArrSize = this->background.width * this->background.height;
	uint16_t portionWidth = xe - xi + 1;
	uint16_t portionHeight = ye - yi + 1;
	uint32_t portionArrSize = portionWidth * portionHeight;


	if ((portionArrSize > tileArrSize)||
		 (xi + portionWidth > this->background.width)||
		 (yi + portionHeight > this->background.height)||
		 (tileArrSize == 0)||
		 (portionArrSize ==0)||
		 this->noBGFlag
		 ) return;


	 for(uint16_t Y = 0; Y < portionHeight; Y++){
		 for(uint16_t X = 0; X < portionWidth; X++){
			 uint32_t position = X + xi + (Y + yi) * this->background.width;

			 uint8_t pixel16bits = this->background.p[position];
			 this->func(X + xi, Y + yi, this->background.palette[pixel16bits]);

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
								uint16_t screenY
								)
{
	//draws a piece of the background inside the screen, all relative to the background.
	//we make sure everything is in order:
	uint16_t windowWidth = windowXf - windowXi + 1;
	uint16_t windowHeight = windowYf - windowYi + 1;
	if(
			(windowWidth > this->screenWidth) ||
			(windowHeight > this->screenHeight)||
			(screenHeight > this->background.height) ||
			(screenWidth > this->background.width) ||
			(windowXi + windowWidth > this->background.width)||
			(windowYi + windowHeight > this->background.height)||
			this->noBGFlag
			) return;


	for(uint32_t Y = 0; Y < windowWidth; Y++ ){
		for(uint32_t X = 0; X < windowHeight; X++){
			uint32_t pixel8bits = (screenX +  windowXi + X) + (screenY + windowYi + Y) * this->background.width;
			this->func(X + windowXi, Y + windowYi, this->background.palette[this->background.p[pixel8bits]]);
		}
	}
}

void Frame_Builder::FB_AssembleFrame(){

}

