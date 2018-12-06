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
        
    #include "project.h"
    #include <stdlib.h>
    #include <math.h>
    #include "MotorDriverX.h"

    #define MAX_STEPS_Y 200 //180 degrees (stepper is geared wrong)

    int stepperPositionY;
    uint8 timerDoneFlagY;
    enum state stepperStateY;

    CY_ISR_PROTO(stepperY_isr_handler);

    void initStepperY();
    void rotateClockwiseY();
    void rotateCounterClockwiseY();
    void moveStepY();
    void moveDegreesY(int deg);
    void resetPositionY();

#endif
/* [] END OF FILE */
