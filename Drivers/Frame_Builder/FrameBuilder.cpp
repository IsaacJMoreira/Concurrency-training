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

//Translates and draws
void Frame_Builder::FB_Draw8bitTile(
								uint8_t x,
								uint8_t y,
								uint16_t tileSide,
								const uint16_t palette[],
								void (*func)(UG_S16, UG_S16, UG_COLOR),
								const uint8_t tile[],
								uint8_t transColor,
								bool setTrans
								)
{

	// check if the tile is a perfect square and if its not empty
	if (tileSide == 0.0f) return;


	 for(uint16_t Y = 0; Y < (uint16_t)tileSide; Y++){
		 for(uint16_t X = 0; X < (uint16_t)tileSide; X++){
			 uint16_t position = X+Y*tileSide;
			 uint8_t color = tile[position];
			 if(setTrans){
				 if(color != transColor){
					 uint8_t pixel16bits = tile[position];
				 	 func(X + x, Y + y, palette[pixel16bits]);
			     }
			 }else{
				 uint8_t pixel16bits = tile[position];
				 func(X + x, Y + y, palette[pixel16bits]);
			 }
		 }
 	 }
 }

void Frame_Builder::FB_AssembleFrame(){

}

