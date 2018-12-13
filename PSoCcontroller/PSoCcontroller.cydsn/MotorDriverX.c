#include "MotorDriverX.h"

CY_ISR(stepperX_isr_handler) {
    Timer_StepperX_Stop();
    timerDoneFlagX = 1;
}

void initStepperX() {
    Pin_X1_Write(0);
    Pin_X2_Write(0);
    
    ISR_stepperX_StartEx(stepperX_isr_handler);
    timerDoneFlagX = 0;
    
    resetPositionX();
    moveDegreesX(90+OFFSET_X);
}

void rotateClockwiseX() {
    if(stepperStateX == WEST) { 
        stepperStateX = NORTH;
    }
    else {
        ++stepperStateX;
    }
    moveStepX();
    ++stepperPositionX;
}

void rotateCounterClockwiseX() {
    if(stepperStateX == NORTH) {
        stepperStateX = WEST;
    }
    else {
        --stepperStateX;
    }
    moveStepX();
    --stepperPositionX;
}

void moveStepX() {
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
    int steps = (int)round(round1); //Afrund antallet af steps
    
    if(steps > 0) {
        if (stepperPositionX+steps > MAX_STEPS_X) { //limit to max
            steps = MAX_STEPS_X-stepperPositionX;   
        }
        for(int i = 0; i < steps; i++) {
            Timer_StepperX_Start();
            while(timerDoneFlagX == 0); //wait here
            rotateClockwiseX();
            timerDoneFlagX = 0;
        }
    }
    else if(steps < 0) {
        if(steps <= (stepperPositionX * -1)) {    //Hvis antallet af steps der skal køres tilbage er mere end vi kan køre, før proben rammes
            resetPositionX(); //move to zero position
        }
        else if(steps > (stepperPositionX * -1)) {
            for(int i = 0; i > steps; i--) {
                Timer_StepperX_Start();
                while(timerDoneFlagX == 0);
                rotateCounterClockwiseX();
                timerDoneFlagX = 0;
            }
        }
    }
}

void resetPositionX() {
    while(Pin_X3_Read() == 1) {
        Timer_StepperX_Start();
        while(timerDoneFlagX == 0);
        rotateCounterClockwiseX();
        timerDoneFlagX = 0;
    }
    stepperPositionX = 0;
}

/* [] END OF FILE */