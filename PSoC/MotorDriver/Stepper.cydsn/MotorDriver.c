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
#include <math.h>

CY_ISR(stepper_isr_handler) {
    Timer_StepperX_Stop();
    timerDoneFlag = 1;
}

void initX() {
    Pin_X1_Write(0);
    Pin_X2_Write(0);
    
    stepper_isr_StartEx(stepper_isr_handler);
    timerDoneFlag = 0;
    
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
    
    UART_1_PutString("Rotated clockwise once\n\r");
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
//    UART_1_PutString("Starting moveDegreesX function...\n\r");
    float round1 = deg / 0.9; //Grader divideret med stepvinkel = antal steps der skal køres
    int steps = (int)round(round1); //Afrund antallet af steps
    
    if(steps > 0) {
        for(int i = 0; i < steps; i++) {
            Timer_StepperX_Start();
//            UART_1_PutString("Starting timer\n\r");
            while(timerDoneFlag == 0); //wait here
            rotateClockwiseX();
            timerDoneFlag = 0;
        }
    }
    else if(steps < 0) {
        if(steps < (stepperPositionX * -1)) {    //Hvis antallet af steps der skal køres tilbage er mere end vi kan køre, før proben rammes
            resetPositionX();
        }
        else if(steps > (stepperPositionX * -1)) {
            for(int i = 0; i > steps; i--) {
                Timer_StepperX_Start();
                while(timerDoneFlag == 0);
                rotateCounterClockwiseX();
                timerDoneFlag = 0;
            }
        }
    }
}

static void resetPositionX() {
    while(Pin_X3_Read() == 1) {
        Timer_StepperX_Start();
        while(timerDoneFlag == 0);
        rotateCounterClockwiseX();
        timerDoneFlag = 0;
    }
    stepperPositionX = 0;
    UART_1_PutString("Stepper reset\n\r");
}

/* [] END OF FILE */