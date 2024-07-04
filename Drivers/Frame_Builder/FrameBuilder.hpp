/*
 * FrameBuilder.hpp
 *
 *  Created on: Jun 26, 2024
 *      Author: isaac
 */

#ifndef FRAME_BUILDER_FRAMEBUILDER_HPP_
#define FRAME_BUILDER_FRAMEBUILDER_HPP_

#include "Types.hpp"
extern "C"{

}

class Frame_Builder {
public:
	Frame_Builder(uint16_t screenWidth, uint16_t screenHeight, void (*drawDependency)(int16_t, int16_t, uint16_t));
	virtual ~Frame_Builder();
	void setBackground(FB_8bitBMP background);
	void setSpriteMap(FB_SpriteMap spriteMap);
	void FB_Draw8bitTile(
			uint8_t xi,
			uint8_t yi,
			uint8_t xe,
			uint8_t ye,
			const uint16_t palette[],
			const uint8_t tile[],
			uint8_t transColor = 0x00,
			bool setTrans = false
			);
	void FB_SimpleBGPartialDraw(
			uint16_t xi,
			uint16_t yi,
			uint16_t xe,
			uint16_t ye
			);
	void FB_LongBGPartialDraw(
			//window coordinates, relative to the screen
			uint16_t windowXi,
			uint16_t windowYi,
			uint16_t windowXf,
			uint16_t windowYf,
			//visible area of the background (screen) relative to the background
			uint16_t screenX,
			uint16_t screenY
			);
	void FB_AssembleFrame();
private:
	bool noBGFlag = true;
	bool noSpritesFlag = true;
	uint16_t screenWidth;
	uint16_t screenHeight;
	FB_8bitBMP background;
	FB_SpriteMap spriteMap;
	void (*func)(int16_t, int16_t, uint16_t);
};

#endif /* FRAME_BUILDER_FRAMEBUILDER_HPP_ */
