/*
 * Types.hpp
 *
 *  Created on: Jun 20, 2024
 *      Author: isaac
 */

#ifndef ASYNC_EVENT_LOOP_TYPES_HPP_
#define ASYNC_EVENT_LOOP_TYPES_HPP_

#include "stm32f4xx_hal.h"

/* Queueable Class return values enum  */

enum QueueableReturnValue{
	DONE        = 0b00000000,
	TODO        = 0b00000001,
	DOING       = 0b00000010,
};

/* Queueable Class interface  */

//This implementation ensures some basic things that a queuable class
//should have. It has to have methods for determining if its done executing.
//it should be done in a execute method.
 class QueueableClass{
 public:
	 //CONSTRUCTOR
	 QueueableClass(){
		 this -> state = QueueableReturnValue::DONE;
		 this -> nextClass = nullptr;
	 }

	 virtual QueueableReturnValue getState(void) final{
		 return this -> state;
	 }

	 virtual void setNextClass(QueueableClass* next)final{
	 	 this -> nextClass = next;
	 }

	 virtual QueueableClass* getNextClass(void) final{
		 return this -> nextClass;
	 }
	 //this method gives the object the ability to decide what to
	 //when the process tells it to requeue.
	 //THIS IS AN EXAMPLE OF WHAT TO DO, BUT YOU SHOULD SO WHAT SOUITS
	 //YOUR CODE BETTER. KEEP IN MIND THE INTEGRITY OF THE LINKED LIST!
	 virtual void requeue(){
		 setState(TODO);//in this case it restarts the buzzer timer.
	 }

	 //WHAT DOES THE OBJECT DO WHEN IT GETS IN QUEUE?
	 //IN THIS IMPLEMENTATION, IT JUST CHANGES THE STATE, BUT
	 //YOU COULD REWRITE THIS TO FIT YOUR NEEDS
	 virtual void enqueue(){
		 setState(TODO);
	 }

	 //this method has to be implemented, but here is an example:
	 virtual void EXECUTE(void){
		 //simple implementation of method to make a beep for 5ms;
		 #define delay 10
		 static uint32_t prevTime = 0;
		 static uint32_t currentTime = 0;
		 uint32_t elapsedTime;
		 static uint8_t state = 0;

		 if(this -> state == TODO){
		 	state = 1;
		 	setState(DOING);
		   	prevTime = HAL_GetTick();//get the time when the change accurred
		 }

		 if(state){//if the function is in the on state, turns the toPerform on;
		   	GPIOB -> ODR |= GPIO_PIN_2;//SET BUZZER PIN;
		   	//now we check if the delay time has elapsed.
		   	//first we acquire the current time
		  	currentTime = HAL_GetTick();
		   	if (currentTime >= prevTime) {//making sure to account for roll over
		   		elapsedTime = currentTime - prevTime;
		   	} else {
		   		elapsedTime = (UINT32_MAX - prevTime) + currentTime + 1;
		   	}
		   	//if the time has run out, we turn the toPerform off
		   	if(elapsedTime >= delay){
		   		GPIOB -> ODR &= ~GPIO_PIN_2; //RESET BUZZER PIN;
		   		state = 0;//we clear the state.
		   		setState(DONE);//WE SIGNAL IT ENDED EXECUTION;
		   	}
		   }
	 }

 private:
	 QueueableClass* nextClass;// points to the next class in queue
	 QueueableReturnValue state;
	 virtual void setState(QueueableReturnValue state)final{
	 		 this -> state = state;
	 	 }
 };

#endif /* ASYNC_EVENT_LOOP_TYPES_HPP_ */
