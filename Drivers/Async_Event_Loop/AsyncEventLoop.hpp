/*
 * AsyncEventLoop.hpp
 *
 *  Created on: Jun 20, 2024
 *      Author: isaac
 */

#ifndef ASYNC_EVENT_LOOP_ASYNCEVENTLOOP_HPP_
#define ASYNC_EVENT_LOOP_ASYNCEVENTLOOP_HPP_

#include "stm32f4xx_hal.h"

class Async_Event_Loop {
public:
	Async_Event_Loop();
	virtual ~Async_Event_Loop();
};

#endif /* ASYNC_EVENT_LOOP_ASYNCEVENTLOOP_HPP_ */
