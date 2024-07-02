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
#include "../UGUI/ugui.h"
}

class Frame_Builder {
public:
	Frame_Builder();
	virtual ~Frame_Builder();
	void FB_Draw8bitTile(
			uint8_t xi,
			uint8_t yi,
			uint8_t xe,
			uint8_t ye,
			const uint16_t palette[],
			void (*func)(UG_S16, UG_S16, UG_COLOR),
			const uint8_t tile[],
			uint8_t transColor = 0x00,
			bool setTrans = false
			);
	void FB_SimpleBGPartialDraw(
			uint16_t xi,
			uint16_t yi,
			uint16_t xe,
			uint16_t ye,
			uint16_t tileHeight,
			uint16_t tileWidth,
			const uint16_t palette[],
			void (*func)(UG_S16, UG_S16, UG_COLOR),
			const uint8_t tile[]
			);
	void FB_LongBGPartialDraw(
			uint16_t WindowXi,
			uint16_t WindowYi,
			uint16_t WindowXf,
			uint16_t WindowYf,
			uint16_t screenX,
			uint16_t screenY,
			uint8_t screenHeight,
			uint8_t screenWidth,
			uint16_t BGHeight,
			uint16_t BGWidth,
			const uint16_t palette[],
			void (*func)(UG_S16, UG_S16, UG_COLOR),
			const uint8_t tile[]
			);
	void FB_AssembleFrame();
};

#endif /* FRAME_BUILDER_FRAMEBUILDER_HPP_ */
