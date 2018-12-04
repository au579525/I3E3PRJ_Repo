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
#ifndef MOTORDRIVERY_H
#define MOTORDRIVERY_H
        
    #include <project.h>
    #include <stdlib.h>
    #include <math.h>

    #define MAX_STEPS_Y 200 //180 degrees (stepper is geared wrong)

    enum state {NORTH, EAST, SOUTH, WEST};  //Steppermotorcoils 4 positioner

    int stepperPositionY;
    uint8 timerDoneFlagY;
    enum state stepperStateY;

    CY_ISR_PROTO(stepperY_isr_handler);

    void initStepperY();
    static void rotateClockwiseY();
    static void rotateCounterClockwiseY();
    static void moveStepY();
    void moveDegreesY(int deg);
    static void resetPositionY();

#endif
/* [] END OF FILE */
