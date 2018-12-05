/* ========================================
 *
 * Copyright YOUR COMPANY, THE YEAR
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * CONFIDENTIAL AND PROPRIETARY INFORMATION
 * WHICH IS THE PROPERTY OF your company.
 *
 * ========================================
*/

#ifndef MOTORDRIVERX_H
#define MOTORDRIVERX_H
    
    #include <project.h>
    #include <stdlib.h>
    #include <math.h>

    #define MAX_STEPS_X 100 //180 degrees

    enum state {NORTH, EAST, SOUTH, WEST};  //Steppermotorcoils 4 positioner

    int stepperPositionX;
    uint8 timerDoneFlagX;
    enum state stepperStateX;

    CY_ISR_PROTO(stepperX_isr_handler);

    void initStepperX();
    static void rotateClockwiseX();
    static void rotateCounterClockwiseX();
    static void moveStepX();
    void moveDegreesX(int deg);
    static void resetPositionX();
    
#endif

/* [] END OF FILE */
