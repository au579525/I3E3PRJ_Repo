/* ========================================
 * PIGEON EXTERMINATION SYSTEM
 * CircularBuffer.c
 * 
 * Author: Lasse Krarup
 * Date: 26-11-2018
 * ========================================
*/
#include "CircularBuffer.h"
#include "project.h"

static uint8 isFull(struct CircBuf * circ_ptr){
    if ((circ_ptr->rear + 1) % circ_ptr->maxLength ==  circ_ptr->front) {
        UART_1_PutString("Buffer full\n\r");
        return 1;
    } else
        return 0;
}

static uint8 isEmpty(struct CircBuf * circ_ptr){
    if (circ_ptr->rear == -1 && circ_ptr->front == -1) {
//        UART_1_PutString("Buffer empty\n\r");
        return 1;
    } else
        return 0;
}

void push(struct CircBuf * circ_ptr, void (*newFuncPtr)(), int newParam) {
    struct queueElement * QIhandle;
    
    if (isFull(circ_ptr)) {
        ; //do nothing
    } else if (isEmpty(circ_ptr)) {
        UART_1_PutString("Pushing first element in buffer\n\r");
        circ_ptr->front = 0;
        circ_ptr->rear = 0;
        QIhandle = &circ_ptr->queueItem[circ_ptr->rear];
        QIhandle->funcPtr = newFuncPtr;
        QIhandle->param = newParam;
    } else {
        UART_1_PutString("Pushing element\n\r");
        circ_ptr->rear = (circ_ptr->rear + 1) % circ_ptr->maxLength;
        QIhandle = &circ_ptr->queueItem[circ_ptr->rear];
        QIhandle->funcPtr = newFuncPtr; //place function pointer in queue
        QIhandle->param = newParam; //place parameter in queue
    }
};

void pop(struct CircBuf * circ_ptr) {
    struct queueElement * QIhandle = &circ_ptr->queueItem[circ_ptr->front];
    
    if (!isEmpty(circ_ptr)) {
        UART_1_PutString("Popping element\n\r");
        (*QIhandle->funcPtr)(QIhandle->param); //perform operation in queue
        
        if (circ_ptr->front == circ_ptr->rear) {
            circ_ptr->front = -1;
            circ_ptr->rear = -1;
        } else {
            circ_ptr->front = (circ_ptr->front + 1) % circ_ptr->maxLength;
        }
    }
};

static void clearBuffer(struct CircBuf * circ_ptr) {
    circ_ptr->front = -1;
    circ_ptr->rear = -1;
}

void initCircbuf(struct CircBuf * circ_ptr) {
    UART_1_PutString("Buffer initializing\n\r");
    
    circ_ptr->maxLength = CIRCBUF_MAX_LENGTH;
    circ_ptr->front = -1;
    circ_ptr->rear = -1;
    circ_ptr->isFull = isFull;
    circ_ptr->isEmpty = isEmpty;
    circ_ptr->clearBuffer = clearBuffer;
    circ_ptr->push = push;
    circ_ptr->pop = pop;
}

/* [] END OF FILE */