/*
 * Types.hpp
 *
 *  Created on: Jun 28, 2024
 *      Author: isaac
 */

#ifndef FRAME_BUILDER_TYPES_HPP_
#define FRAME_BUILDER_TYPES_HPP_

/****************************************************/
/*                TILE DEFINITIONS                  */
/****************************************************/
//for 240X240 display only
//
//BE AWARE OF FLASH MEMORY USAGE ON YOUR MCU!
//***************************************************/

typedef uint8_t Tile16Data[256];
typedef uint8_t Tile240Data[57600];

//a tile of side 16 is the smallest tile possible
//SIZE: 1/4KB
typedef struct {
	const Tile16Data *TileData;
	const uint16_t *Palette;
	const uint8_t TransparentColor;
	const bool HasTransp;
} FB_Tile16;

//a tile that covers the hole screen has side 240
//WARNING: it should be used only for backgrounds, masks and full screen images.
//	They take a large chunk of memory and the BlackPill can only hold 9 of them!
//SIZE: 56.25KB
typedef struct {
	const Tile240Data *TileData;
	const uint16_t *Palette;
	const uint8_t TransparentColor;
	const bool HasTransp;
} FB_Tile240;

//A layer is a collection of small tile pointers
//Size: 0.88KB
typedef struct {
	FB_Tile16 tiles[15][15];//225 tiles per Layer
	uint8_t tileOrder;
} FB_Layer;

//A Frame is a collection of layers.
//The smallest the index of the layer,
//the closer it is to the foreground.
//SIZE: NUMBER_OF_LAYERS * 0.88KB
typedef struct{
	FB_Layer *layers;
} FB_Frame;

typedef struct
{
   const void* p;
   const uint16_t width;
   const uint16_t height;
   const uint8_t palette;
} FB_BMP;

#endif /* FRAME_BUILDER_TYPES_HPP_ */
