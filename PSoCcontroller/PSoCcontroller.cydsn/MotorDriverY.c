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
#include "MotorDriverY.h"

CY_ISR(stepperY_isr_handler) {
    Timer_StepperY_Stop();
    timerDoneFlagY = 1;
}

void initStepperY() {
    Pin_Y1_Write(0);
    Pin_Y2_Write(0);
    
    ISR_stepperY_StartEx(stepperY_isr_handler);
    timerDoneFlagY = 0;
    
    resetPositionY();
    moveDegreesY(-90-OFFSET_Y);
}

void rotateClockwiseY() {
    if(stepperStateY == WEST) { 
        stepperStateY = NORTH;
    }
    else {
        ++stepperStateY;
    }
    moveStepY();
    ++stepperPositionY;
}

void rotateCounterClockwiseY() {
    if(stepperStateY == NORTH) {
        stepperStateY = WEST;
    }
    else {
        --stepperStateY;
    }
    moveStepY();
    --stepperPositionY;
}

void moveStepY() {
    if(stepperStateY == NORTH) {
        Pin_Y1_Write(0);
        Pin_Y2_Write(0);
    }
    else if(stepperStateY == EAST) {
        Pin_Y1_Write(1);
        Pin_Y2_Write(0);
    }
    else if(stepperStateY == SOUTH) {
        Pin_Y1_Write(1);
        Pin_Y2_Write(1);
    }
    else if(stepperStateY == WEST) {
        Pin_Y1_Write(0);
        Pin_Y2_Write(1);
    }
}

void moveDegreesY(int deg) { //Positivt antal grader skrives hvis armen skal køre med uret og negativt gradtal skrives hvis den skal køre mod uret
    // OBS! Y-stepper er gearet forkert! 0.9 grader pr. full step, ikke 1.8 som der står i databladet
    float round1 = deg / 1.8; //Grader divideret med stepvinkel = antal steps der skal køres
    int steps = (int)round(round1); //Afrund antallet af steps
    
    if(steps < 0) {
        if (stepperPositionY+steps < MAX_STEPS_Y) { //limit to max number of steps
            steps = MAX_STEPS_Y-stepperPositionY;
        }
        for(int i = 0; i > steps; i--) {
            Timer_StepperY_Start();
            while(timerDoneFlagY == 0); //wait here
            rotateCounterClockwiseY();
            timerDoneFlagY = 0;
        }
    }
    else if(steps > 0) {
        if(steps >= (stepperPositionY * -1)) {    //Hvis antallet af steps der skal køres tilbage er mere end vi kan køre, før proben rammes
            resetPositionY(); //move to zero position
        }
        else {
            for(int i = 0; i < steps; i++) {
                Timer_StepperY_Start();
                while(timerDoneFlagY == 0);
                rotateClockwiseY();
                timerDoneFlagY = 0;
            }
        }
    }
}

void resetPositionY() {
    while(Pin_Y3_Read() == 1) {
        Timer_StepperY_Start();
        while(timerDoneFlagY == 0);
        rotateClockwiseY();
        timerDoneFlagY = 0;
    }
    stepperPositionY = 0;
}