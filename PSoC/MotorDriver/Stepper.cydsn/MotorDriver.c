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
#include "MotorDriver.h"


void init() {
    Pin_1_Write(0);
    Pin_2_Write(0);
    
    resetPosition();
}

int getPosition() {
    return stepperPosition;
}

void rotateClockwise() {
    if(stepperState == WEST) {
        stepperState = NORTH;
    }
    else {
        ++stepperState;
    }
}

void rotateCounterClockwise() {
    if(stepperState == NORTH) {
        stepperState = WEST;
    }
    else {
        --stepperState;
    }
}

void moveStep() {
    
}

void moveDegrees(int deg) { //Positivt antal grader skrives hvis armen skal kører med uret og negativt gradtal skrives hvis den skal køre mod uret
    if(deg > 0) {
        for(int i = 0; i < deg; i++) {
            Pin_1_Write(1);
            CyDelay(TIME);
            Pin_2_Write(1);
            CyDelay(TIME);
            Pin_1_Write(0);
            CyDelay(TIME);
            Pin_2_Write(0);
            CyDelay(TIME);
            i++;
        }
    }
    else if(deg < 0) {
        if((stepperPosition + deg) < 0) { //Hvis der forsøges at gå længere tilbage end til proben
            
        }
    }
}

void resetPosition() {
        while(Pin_3_Read() == 1) { //Her kører stepperen fremad (med uret). Hvis den skal køre den anden vej for at ramme proben, byttes om på pin 1 og 2
        Pin_1_Write(1);
        CyDelay(TIME);
        Pin_2_Write(1);
        CyDelay(TIME);
        Pin_1_Write(0);
        CyDelay(TIME);
        Pin_2_Write(0);
        CyDelay(TIME);
    }
    stepperPosition = 0;
}


/* [] END OF FILE */
