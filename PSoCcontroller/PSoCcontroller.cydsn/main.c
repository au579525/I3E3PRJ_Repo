/* ========================================
 * PIGEON EXTERMINATION SYSTEM
 * 
 * PSoCcontroller Source File
 * 
 * Author: Lasse Krarup
 * Version: 1.0
 *
 * ========================================
*/

// ========================== INCLUDES ===================================
#include "project.h"
#include "SonarDriver.h"
#include "WaterPump.h"
#include "MotorDriverX.h"
#include "MotorDriverY.h"
#include "WaterSensor.h"
#include "CircularBuffer.h"
#include "MoistureSensor.h"
#include "SPI_driver_PSoC.h"
#include "PSoCcontroller.h"

//Array of function pointer for ability to iterate through modes if necessary
void (*states[5])(void) = {normalMode, powersavingMode, manualMode, automatiskVanding, standbyMode};

// =========== FOR TESTING ===========
CY_ISR_PROTO( UARTisr );
char msg[256];

// ===================== START MAIN ===================================
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // ~~~~~~~~~~~~ INITIALIZATION ~~~~~~~~~~~~~~~~
    
    
    
    //ISR_WaterLevel_StartEx( WaterLevelISRhandler ); //DONT LEAVE FLOATING!!! WILL CAUSE INTERRUPT
    ISR_delay_StartEx( DelayTimerInterrupt );
    initStepperX();
    initStepperY();
    initCircbuf(&circBuf);
    Sonar_Start();
    WaSensInit();
    initWaterPump();
    MoistureSensor_init();
    SPI_start();
    
    SPI_send_resetToDefault();
    CyDelay(1);
    setMode(NORMAL_MODE); //default initial state
    noWater = FALSE;
    while(1) {
//        if(Pin_ISR_WaSens_Read() == 1){//noWater == TRUE) {
//            WaterPump_fireWater(FALSE);
//            SPI_send_waterlevel(0);
//            Pin_Low_WL_Write(1);
//            setMode(STANDBY_MODE);
//        }
//        else {
//            noWater = FALSE;
//            Pin_Low_WL_Write(0);
//        }
        
        if (SPI_recieved_flag == 1) {
            Handle_SPI_recieved();
        }
        
        currentState();
        
    }
}

// ================ FOR TESTING ============
CY_ISR(UARTisr) {
    char input = UART_1_ReadRxData();
    UART_1_PutString("Command received from UART\n\r");
    switch(input) {
        case 'A': //NORMAL MODE
            setMode(NORMAL_MODE);
            UART_1_PutString("Setting mode to Normal mode\n\r");
            break;
        case 'B': //MANUAL MODE
            setMode(MANUAL_MODE);
            UART_1_PutString("Setting mode to Manual mode\n\r");
            break; 
        case 'C': //POWERSAVING MODE
            setMode(POWERSAVING_MODE);
            UART_1_PutString("Setting mode to Powersaving mode\n\r");
            break;
        case 'D': //STANDBY MODE
            setMode(STANDBY_MODE);
            UART_1_PutString("Setting mode to Standby mode\n\r");
            break;
        case 'E': //AUTOMATISK VANDING
            setMode(AUTOMATISK_VANDING);
            UART_1_PutString("Setting mode to Automatisk vanding mode\n\r");
            break;
        case 'F': //LEFT
            if (mode == MANUAL_MODE) {
                circBuf.push(&circBuf, moveDegreesX, -5);
            }
            break;
        case 'G': //RIGHT
            if (mode == MANUAL_MODE) {
                circBuf.push(&circBuf, moveDegreesX, 5);
            }
            break;
        case 'H': //UP
            if (mode == MANUAL_MODE) {
                circBuf.push(&circBuf, moveDegreesY, 5);
            }
            break;
        case 'I': //DOWN
            if (mode == MANUAL_MODE) {
                circBuf.push(&circBuf, moveDegreesY, -5);
            }
            break;
        case 'J': //START FIRING
            if (mode == MANUAL_MODE) {
                circBuf.push(&circBuf, WaterPump_fireWater, TRUE);
            }
            break;
        case 'K': //STOP FIRING
            if (mode == MANUAL_MODE) {
                circBuf.push(&circBuf, WaterPump_fireWater, FALSE);
            }
            break;
        case 'L': //test
            UART_1_PutString("Send pigeon detected\n\r");
            SPI_send_pigeon_detected();
            break;
        default:
            break;
    }
}

// =================== INTERRUPT SERVICE ROUTINES ==============================

CY_ISR( DelayTimerInterrupt ) {
    Delay_Timer_Stop(); //stop timer
    Delay_Timer_ReadStatusRegister(); //clear interrupt
}

CY_ISR( WaterLevelISRhandler ) {
    noWater = TRUE;   
}

CY_ISR( stepperX_interrupt_handler ){
    Timer_StepperX_Stop();
    timerDoneFlagX = 1;
}

CY_ISR( stepperY_interrupt_handler) {
    Timer_StepperY_Stop();
    timerDoneFlagY = 1;
}

CY_ISR(ISR_SPI_RX_handler)
{
    SPI_1_ReadRxStatus();
    //SPI_1_ClearRxBuffer();
    
    SPI_recieved = SPI_1_ReadRxData();
    SPI_recieved_flag = 1;
}
// ===================== FUNCTION DEFINITIONS ===================================
void setMode(enum Mode newMode){
    if (mode >= NORMAL_MODE && mode < STANDBY_MODE) {
        currentState = states[newMode];
        mode = newMode;
    }
}

void checkForPigeonAndShoot(void) {
    
    pigeonPosition = Sonar_GetPosition();
    struct position detectedPosition = pigeonPosition;
    
    if (pigeonPosition.detected == 1) {
        SPI_send_pigeon_detected(); //log
        SPI_send_waterlevel(WaSensMeasure());
        while(pigeonPosition.detected == 1) { //if pigeon detected...
            
            int targetX, targetY; //assign target X position
            switch(pigeonPosition.width){
                case 1:
                    targetX = (90-35) + pigeonPosition.distance/3;
                    break;
                case 2:
                    targetX = (90-30);
                    break;
                case 3:
                    targetX = (90-25) - pigeonPosition.distance/3;
                    break;
                default: break;
            }
            
            if (pigeonPosition.distance < 20) { //assign target Y position
                targetY = -90;
            } else if (pigeonPosition.distance > 20 && pigeonPosition.distance < 40) {
                targetY = -80;
            } else if (pigeonPosition.distance > 40) {
                targetY = -70;   
            } else {
                targetY = stepperPositionY;
            }
            
            moveDegreesX(targetX - stepperPositionX); //move steppers...
            moveDegreesY(targetY - stepperPositionY);
            
            while(  detectedPosition.width == pigeonPosition.width &&
                    round(detectedPosition.distance)+5 > round(pigeonPosition.distance) &&
                    round(detectedPosition.distance)-5 < round(pigeonPosition.distance)) { //fire while pigeon hasn't 
                if (noWater == FALSE)
                    WaterPump_fireWater(TRUE);
                else if (noWater == TRUE) {
                    WaterPump_fireWater(FALSE);
                }    
                pigeonPosition = Sonar_GetPosition(); //renew position
            }
                   
                    
            pigeonPosition = Sonar_GetPosition(); //renew position
        }
        SPI_send_pigeon_shot_position((char)detectedPosition.width, (char) round(detectedPosition.distance));
        WaterPump_fireWater(FALSE);
    }
    //exit_noWater:
       // WaterPump_fireWater(FALSE);
}

// ===================== STATE FUNCTIONS =========================================
void normalMode(void) {
    checkForPigeonAndShoot();
    
    Delay_Timer_Stop();
    Delay_Timer_WritePeriod(DELAY_NORMAL_MODE_MS); //set period
    Delay_Timer_WriteCounter(DELAY_NORMAL_MODE_MS); //reset
    Delay_Timer_Start();
    CyPmAltAct(PM_ALT_ACT_TIME_NONE, PM_ALT_ACT_SRC_INTERRUPT);
}

void powersavingMode(void) {
    checkForPigeonAndShoot();
    CyDelay(5);
    
    Delay_Timer_Stop();
    Delay_Timer_WritePeriod(DELAY_POWERSAVING_MODE_MS);
    Delay_Timer_WriteCounter(DELAY_POWERSAVING_MODE_MS);
    Delay_Timer_Start();
    CyPmAltAct(PM_ALT_ACT_TIME_NONE, PM_ALT_ACT_SRC_INTERRUPT);
}

void manualMode(void) {
    circBuf.pop(&circBuf); //pop from queue. pop function checks for empty queue and does nothing if it is empty
    CyDelay(10); //introduce small delay to reduce risk of getting trapped in interrupt
}

void automatiskVanding(void) {
    int moisture = MoistureSensor_getResult();
    if (moisture > MOISTURE_THRESHOLD) {
        //SPI_sendMoisture(moisture);
        moveDegreesX(165-stepperPositionX); //move to top left
        moveDegreesY(-120-stepperPositionY);
        WaterPump_fireWater(TRUE);//start firing
        moveDegreesX(195-stepperPositionX); //move to top right corner 
        moveDegreesY(-150-stepperPositionY);//move down to middle
        moveDegreesX(165-stepperPositionX); //move to middle left side
        moveDegreesY(-180-stepperPositionY); //move down to bottom
        moveDegreesX(165-stepperPositionX);//move to bottom right side
        WaterPump_fireWater(FALSE);//stop firing
    }
}

void standbyMode(void) {
    CyPmHibernate(); //Hibernate - use hardware reset to start PSoC again
}

/* [] END OF FILE */