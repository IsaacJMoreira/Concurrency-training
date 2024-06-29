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
			uint8_t x,
			uint8_t y,
			uint16_t tileSide,
			const uint16_t palette[],
			void (*func)(UG_S16, UG_S16, UG_COLOR),
			const uint8_t tile[],
			uint8_t transColor = 0x0000,
			bool setTrans = false
			);
	void FB_AssembleFrame();
};

#endif /* FRAME_BUILDER_FRAMEBUILDER_HPP_ */
