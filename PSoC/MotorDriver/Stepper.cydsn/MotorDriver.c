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

void initX() {
    Pin_X1_Write(0);
    Pin_X2_Write(0);
    
    resetPositionX();
}

static void rotateClockwiseX() {
    if(stepperStateX == WEST) { 
        stepperStateX = NORTH;
    }
    else {
        ++stepperStateX;
    }
    moveStepX();
    ++stepperPositionX;
}

static void rotateCounterClockwiseX() {
    if(stepperStateX == NORTH) {
        stepperStateX = WEST;
    }
    else {
        --stepperStateX;
    }
    moveStepX();
    --stepperPositionX;
}

static void moveStepX() {
    if(stepperStateX == NORTH) {
        Pin_X1_Write(0);
        Pin_X2_Write(0);
    }
    else if(stepperStateX == EAST) {
        Pin_X1_Write(1);
        Pin_X2_Write(0);
    }
    else if(stepperStateX == SOUTH) {
        Pin_X1_Write(1);
        Pin_X2_Write(1);
    }
    else if(stepperStateX == WEST) {
        Pin_X1_Write(0);
        Pin_X2_Write(1);
    }
}

void moveDegreesX(int deg) { //Positivt antal grader skrives hvis armen skal køre med uret og negativt gradtal skrives hvis den skal køre mod uret
    float round1 = deg / 1.8; //Grader divideret med stepvinkel = antal steps der skal køres
    int steps = round(round1); //Afrund antallet af steps
    
    if(steps > 0) {
        for(int i = 0; i < steps; i++) {
            rotateClockwiseX();
            CyDelay(TIME);
        }
    }
    else if(steps < 0) {
        if(steps < (stepperPositionX * -1)) {    //Hvis antallet af steps der skal køres tilbage er mere end vi kan køre, før proben rammes
            resetPositionX();
        }
        else if(steps > (stepperPositionX * -1)) {
            for(int i = 0; i > steps; i--) {
                rotateCounterClockwiseX();
                CyDelay(TIME);
            }
        }
    }
}

static void resetPositionX() {
    while(Pin_X3_Read() == 1) {
        rotateCounterClockwiseX();
        CyDelay(TIME);
    }
    stepperPositionX = 0;
}


/* [] END OF FILE */
