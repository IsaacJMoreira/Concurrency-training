/*
 * AsyncEventLoop.cpp
 *
 *  Created on: Jun 20, 2024
 *      Author: isaac
 */

#include "../Async_Event_Loop/AsyncEventLoop.hpp"
#include "Types.hpp"

Async_Event_Loop::Async_Event_Loop() :
    beginning(nullptr),
    previous(nullptr),
    end(nullptr) {
}
void Async_Event_Loop::setBeginning(QueueableClass* beginning){
	this -> beginning = beginning;
}

QueueableClass* Async_Event_Loop::getBeginning(void){
	return this -> beginning;
}

void Async_Event_Loop::setPrevious(QueueableClass* previous){
	this -> previous = previous;
}

QueueableClass* Async_Event_Loop::getPrevious(void){
	return this -> previous;
}

void Async_Event_Loop::setEnd(QueueableClass* end){
	this -> end = end;
}

QueueableClass* Async_Event_Loop::getEnd(void){
	return this -> end;
}

void Async_Event_Loop::enqueue(QueueableClass* next){
	if(next -> getState() == DONE) {//IF THE OBJECT ISN'T ON THE QUEUEU, ALREADY
		next -> enqueue();//SIGNALS THE OBJECTS IT IS GOING IN THE CUEUE
		if(getEnd() == nullptr){//IF THERE IS NOTHING IN THE QUEUE
			setBeginning(next);//THE OBJECTS IS IN THE START OF THE QUEUE.
			setPrevious(next);//THERE IS NO PREVIUS OBJECT
			setEnd(next);//ITS ALSO THE LAST IN QUEUE
		}else{//IF THERE IS ALREADY OBJECTS IN QUEUE
			setPrevious(end);// THE LAST IS NOW SECOND LAST
			setEnd(next);//AND THE LAST OBJECT ASSUMS END OF QUEUE
		}
		this -> end -> setNextClass(nullptr);//IN ANY CASE, THE LAST OBJECT POINTS TO NOTHING.
	}else{
		next->requeue();
	}
}

void Async_Event_Loop::dequeue(QueueableClass* current){

	if((getBeginning() == getEnd()) && (getBeginning() != nullptr)){
		setBeginning(nullptr);
		setPrevious(nullptr);
		setEnd(nullptr);
	}
	if(getBeginning() != nullptr){//IF THE QUEUE ISN'T EMPTY
		this -> previous -> setNextClass(current->getNextClass());//MAKES THE PREVIOS OBJECT POINT TO THE NEXT CLASS
		current->setNextClass(nullptr);//MAKES SURE THE DEQUEUED OBJECT POINTS TO NOTHING
	}

}
//TODO analize this case:
//object is the last one and is DONE executing.
void Async_Event_Loop::ASYNC_LOOP(void){
	QueueableClass* current = getBeginning();

	if(current != nullptr){//IF THERE IS A QUEUE AT ALL
		//for test porpuses
		GPIOA -> ODR &= ~GPIO_PIN_3;//reset green led
		GPIOA -> ODR &= ~GPIO_PIN_4;
		do{
				uint8_t currentClassState = current -> getState();
				if(currentClassState == DONE){//IF THE OBJECT IS DONE EXECUTING
					dequeue(current);//DEQUEUES IT
				}else{//OTHERWISE, EXECUTES IT
					current -> EXECUTE();
				}
				//ADVANCES ONE CLASS
				setPrevious(current);
				current = current -> getNextClass();

			}while(current != nullptr);//IF THE CURRENT OBJECT IS NULL
			setEnd(getPrevious());
			setPrevious(getBeginning());
	}else{
		GPIOA -> ODR |= GPIO_PIN_3;//set green led
	}
}

Async_Event_Loop::~Async_Event_Loop() {
	// TODO Auto-generated destructor stub
}

