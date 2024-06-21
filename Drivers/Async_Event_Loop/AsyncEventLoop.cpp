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

void Async_Event_Loop::enqueue(QueueableClass* next) {

    if (next->getState() == DONE) {
        if (getEnd() == nullptr) {
            // Queue is empty, add the first item
            setBeginning(next);
            setPrevious(next);
            setEnd(next);
        } else {
            // Queue is not empty, add to the end
            getEnd()->setNextClass(next);
            setPrevious(next);
            setEnd(next);
        }
        next->enqueue(); // Signal the object it's enqueued
        next->setNextClass(nullptr); // Ensure new end points to null
    } else {
        next->requeue(); // Object is not done, requeue it
    }
}


void Async_Event_Loop::dequeue(QueueableClass* current) {
    if (current == nullptr || getBeginning() == nullptr) {
        return; // Nothing to dequeue if queue is empty or current is nullptr
    }

    if (getBeginning() == current && getEnd() == current) {
        // Only one item in the queue
        setBeginning(nullptr);
        setPrevious(nullptr);
        setEnd(nullptr);
    } else if (getBeginning() == current) {
        // Dequeuing the first item
        setBeginning(current->getNextClass());
        if (getEnd() == current) {
            // Adjust end pointer if current was also the last item
            setEnd(getBeginning());
        }
    } else {
        // Dequeuing an item in the middle or end
        QueueableClass* prev = getBeginning();
        while (prev != nullptr && prev->getNextClass() != current) {
            prev = prev->getNextClass();
        }
        if (prev != nullptr) {
            prev->setNextClass(current->getNextClass());
            if (getEnd() == current) {
                // Adjust end pointer if current was the last item
                setEnd(prev);
            }
        }
    }

    current->setNextClass(nullptr); // Ensure dequeued object points to nothing
}


//TODO analize this case:
//object is the last one and is DONE executing.
void Async_Event_Loop::ASYNC_LOOP(void){

    QueueableClass* current = getBeginning();
    QueueableClass* next = nullptr;

    if(current != nullptr){//IF THERE IS A QUEUE AT ALL
        // Resetting for test purposes
        GPIOA->ODR &= ~GPIO_PIN_3; // Reset green led

        do {
            uint8_t currentClassState = current->getState();
            next = current->getNextClass(); // Save next pointer before any potential dequeue

            if(currentClassState == DONE){
                dequeue(current); // Dequeue the object if it's done
            } else {
                current->EXECUTE(); // Execute the object if it's not done
            }

            // Update pointers for next iteration
            setPrevious(current);
            current = next;

        } while(current != nullptr);

        // After the loop, update end pointer
        setEnd(getPrevious());
        // Reset previous pointer to beginning (if needed)
        setPrevious(getBeginning());

    } else {
        GPIOA->ODR |= GPIO_PIN_3; // Set green led (no queue case)
    }
}


Async_Event_Loop::~Async_Event_Loop() {
	// TODO Auto-generated destructor stub
}

