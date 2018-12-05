/* ========================================
 * PIGEON EXTERMINATION SYSTEM
 * CircularBuffer.h
 * 
 * Author: Lasse Krarup
 * Date: 26-11-2018
 * ========================================
*/
#ifndef CIRCULARBUFFER_H
#define CIRCULARBUFFER_H
    
#include "project.h"
    
#define CIRCBUF_MAX_LENGTH 20
    
struct queueElement{
    void (*funcPtr)();
    int param;
};

struct CircBuf {
    struct queueElement queueItem[CIRCBUF_MAX_LENGTH];
    void (*pop)();
    void (*push)();
    uint8 (*isFull)();
    uint8 (*isEmpty)();
    void (*clearBuffer)();
    int8 front;
    int8 rear;
    uint8 maxLength; //initialized to CIRCBUF_MAX_LENGTH in init function
};

void initCircbuf(struct CircBuf * circ_ptr);

#endif
/* [] END OF FILE */