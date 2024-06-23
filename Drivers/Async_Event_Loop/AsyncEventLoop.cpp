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

Async_Event_Loop::~Async_Event_Loop() {
    // Clean up any dynamically allocated resources if needed
}

void Async_Event_Loop::setBeginning(QueueableClass* beginning) {
    this->beginning = beginning;
}

QueueableClass* Async_Event_Loop::getBeginning() {
    return this->beginning;
}

void Async_Event_Loop::setPrevious(QueueableClass* previous) {
    this->previous = previous;
}

QueueableClass* Async_Event_Loop::getPrevious() {
    return this->previous;
}

void Async_Event_Loop::setEnd(QueueableClass* end) {
    this->end = end;
}

QueueableClass* Async_Event_Loop::getEnd() {
    return this->end;
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
            setPrevious(getEnd());
            setEnd(next);
        }
        next->enqueue(); // Signal the object it's enqueued
        next->setNextClass(nullptr); // Ensure new end points to null
    } else {
        next->requeue(); // Object is not done, requeue it
    }
}

void Async_Event_Loop::dequeue(QueueableClass* current) {
    if (getBeginning() == current && getEnd() == current) {
        // Only one item in the queue
        setBeginning(nullptr);
        setPrevious(nullptr);
        setEnd(nullptr);
    } else if (getBeginning() == current) {
        // Dequeuing the first item
        setBeginning(current->getNextClass());
    } else {
        // Dequeuing an item in the middle or end
        getPrevious()->setNextClass(current->getNextClass());
    }

    current->setNextClass(nullptr); // Ensure dequeued object points to nothing
}

void Async_Event_Loop::ASYNC_LOOP() {
    QueueableClass* current = getBeginning();
    QueueableClass* next = nullptr;

    if (current != nullptr) { // IF THERE IS A QUEUE AT ALL
        // Resetting for test purposes
        GPIOA->ODR &= ~GPIO_PIN_3; // Reset green led

        do {

            uint8_t currentClassState = current->getState();
            next = current->getNextClass(); // Save next pointer before any potential dequeue
            // Update pointers for next iteration
            if (currentClassState == DONE) {
                dequeue(current); // Dequeue the object if it's done
            } else {
                current->EXECUTE(); // Execute the object if it's not done
                setPrevious(current);
            }

            current = next; // Move to the next item in the queue

        } while (current != nullptr);

        // After the loop, update end pointer
        setEnd(getPrevious());
        // Reset previous pointer to beginning (if needed)
        setPrevious(getBeginning());

    } else {
        GPIOA->ODR |= GPIO_PIN_3; // Set green led (no queue case)
    }
}




