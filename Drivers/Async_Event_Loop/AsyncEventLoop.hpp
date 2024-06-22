/*
 * AsyncEventLoop.hpp
 *
 *  Created on: Jun 20, 2024
 *      Author: isaac
 */

#ifndef ASYNC_EVENT_LOOP_ASYNCEVENTLOOP_HPP_
#define ASYNC_EVENT_LOOP_ASYNCEVENTLOOP_HPP_

#include "stm32f4xx_hal.h"
#include "Types.hpp"

class Async_Event_Loop {
public:
	Async_Event_Loop();
	virtual ~Async_Event_Loop();

	virtual void enqueue(QueueableClass next) final;
	virtual void dequeue(QueueableClass current) final;
	virtual void ASYNC_LOOP(void) final;

private:
	QueueableClass* beginning;
	QueueableClass* previous;
	QueueableClass* end;

	virtual void setBeginning(QueueableClass* beginning)final;
	virtual QueueableClass* getBeginning(void) final;
	virtual void setPrevious(QueueableClass* previous)final;
	virtual QueueableClass* getPrevious(void) final;
	virtual void setEnd(QueueableClass* end)final;
	virtual QueueableClass* getEnd(void) final;
};

#endif /* ASYNC_EVENT_LOOP_ASYNCEVENTLOOP_HPP_ */
