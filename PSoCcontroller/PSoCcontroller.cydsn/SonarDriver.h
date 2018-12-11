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
#ifndef SONARDRIVER_H
    #define SONARDRIVER_H
//Project Must Have A 24Bit TimerNamed: Timer_Sonar With Max Counter == 16777216 
//Project must have Input Pins Echo_1 and Echo_2, And Trigger_1 and Trigger_2

#include <stdio.h>
#include "project.h"


struct position{
    uint8_t detected;
    int width;
    double distance;
};
void Sonar_Start();
struct position Sonar_GetPosition();
uint8 sonarTimerDone;

#endif
/* [] END OF FILE */
