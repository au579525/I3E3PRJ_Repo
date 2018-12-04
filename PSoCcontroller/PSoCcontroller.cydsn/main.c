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

// =============== DEFINES, DECLARATIONS & GLOBAL VARS ===================
#define TRUE 1
#define FALSE 0
#define WATER_THRESHOLD_NO_WATER 0
#define WATER_THRESHOLD_LOW_WATER 0
#define MOISTURE_THRESHOLD 3000
#define DELAY_NORMAL_MODE_MS 1000 //should be 3000
#define DELAY_POWERSAVING_MODE_MS 5000 //should be 60000

enum Mode{ //enum for readability and for validation (on setMode function)
    NORMAL_MODE, POWERSAVING_MODE, MANUAL_MODE, AUTOMATISK_VANDING, STANDBY_MODE
};

static void (*currentState)(void); //function pointer for state machines
static void normalMode(void);
static void powersavingMode(void);
static void manualMode(void);
static void automatiskVanding(void);
static void standbyMode(void);
//Array of function pointer for ability to iterate through modes if necessary
static void (*states[5])(void) = {normalMode, powersavingMode, manualMode, automatiskVanding, standbyMode};
static enum Mode mode;

static void setMode(enum Mode);
static void checkForPigeonAndShoot(void);

static int noWater = TRUE; // C-language bool-like integer

static struct position pigeonPosition;
static struct CircBuf circBuf;

CY_ISR_PROTO( WaterLevelISRhandler);
CY_ISR_PROTO( DelayTimerInterrupt );
CY_ISR_PROTO( stepperX_interrupt_handler );
CY_ISR_PROTO( stepperY_interrupt_handler );

// =========== FOR TESTING ===========
CY_ISR_PROTO( UARTisr );
char msg[256];

// ===================== START MAIN ===================================
int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    
    // ~~~~~~~~~~~~ INITIALIZATION ~~~~~~~~~~~~~~~~
    ISR_uart_StartEx(UARTisr);
    UART_1_Start();
    
    UART_1_PutString("Starting program...\n\r");
    
    ISR_delay_StartEx( DelayTimerInterrupt );
//    ISR_WaterLevel_StartEx( WaterLevelISRhandler ); //DONT LEAVE FLOATING!!! WILL CAUSE INTERRUPT
    
    initStepperX();
    initStepperY();
    initCircbuf(&circBuf);
    Sonar_Start();
    WaSensInit();
//    SPI_start();
    
    if (WaSensMeasure() < WATER_THRESHOLD_NO_WATER) {
        UART_1_PutString("Water low! Entering standby\n\r");
        noWater = TRUE;
        setMode(STANDBY_MODE);
    } else {
        noWater = FALSE;
        UART_1_PutString("Starting in normal mode\n\r");
        setMode(NORMAL_MODE); //default initial state
    }
    
    while(1) {
        currentState();     //perform state operations in while loop
    }
}

// ================ FOR TESTING ============
CY_ISR(UARTisr) {
    char input = UART_1_ReadRxData();
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
    UART_1_PutString("Water level ISR was triggered!\n\r");
    WaterPump_fireWater(FALSE);
    setMode(STANDBY_MODE);
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
    SPI_recieved = SPI_1_ReadRxData();
    
    if (SPI_recieved >= 'A' && SPI_recieved <= 'E') {
        switch(SPI_recieved) {
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
            default:
                break;
        }
    } else {
        SPI_recieved_flag = 1;
    }
}
// ===================== FUNCTION DEFINITIONS ===================================
static void setMode(enum Mode newMode){
    if (mode >= NORMAL_MODE && mode < STANDBY_MODE) {
        currentState = states[newMode];
        mode = newMode;
    }
}

static void checkForPigeonAndShoot(void) {
//    pigeonPosition = Sonar_GetPosition();
//    struct position detectedPosition = pigeonPosition;
//        
//    if (pigeonPosition.detected == 1) { //if pigeon detected...
//        SPI_send_pigeon_detected();
//        moveDegreesX(pigeonPosition.width); //move steppers...
//        moveDegreesY(pigeonPosition.distance);
//        
//        while(detectedPosition.width == pigeonPosition.width && detectedPosition.distance == pigeonPosition.distance) { //fire while pigeon hasn't moved
//            if (noWater == FALSE)
//                WaterPump_fireWater(TRUE);
//            else {
//                WaterPump_fireWater(FALSE);
//                setMode(STANDBY_MODE);
//            }    
//            pigeonPosition = Sonar_GetPosition(); //renew position
//        }

//    if (WaterSensor_getWaterLevel() < WATER_THRESHOLD_LOW_WATER) {
//        //LowWaterLEDon();
//        SPI_send_low_water();
//    }
//    }
//    SPI_send_pigeon_shot_position((char)pigeonPosition.width, (char)pigeonPosition.distance);
    
    Pin_1_Write(!Pin_1_Read());
}

// ===================== STATE FUNCTIONS =========================================
void normalMode(void) {
    checkForPigeonAndShoot();

    Delay_Timer_Stop();
    Delay_Timer_WritePeriod(DELAY_NORMAL_MODE_MS);
    Delay_Timer_WriteCounter(DELAY_NORMAL_MODE_MS);
    Delay_Timer_Start();
    CyPmAltAct(PM_ALT_ACT_TIME_NONE, PM_ALT_ACT_SRC_INTERRUPT);
}

void powersavingMode(void) {
    checkForPigeonAndShoot();
    
    Delay_Timer_Stop();
    Delay_Timer_WritePeriod(DELAY_POWERSAVING_MODE_MS);
    Delay_Timer_WriteCounter(DELAY_POWERSAVING_MODE_MS);
    Delay_Timer_Start();
    CyPmAltAct(PM_ALT_ACT_TIME_NONE, PM_ALT_ACT_SRC_INTERRUPT);
}

void manualMode(void) {
    if (SPI_recieved_flag == 1) {
        switch(SPI_recieved) {
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
            default:
                break;
        }
        
        SPI_recieved_flag = 0;
    }
    
    circBuf.pop(&circBuf); //pop from queue. pop function checks for empty queue and does nothing if it is empty
    CyDelay(10); //introduce small delay to reduce risk of getting trapped in interrupt
}

void automatiskVanding(void) {
    if (MoistureSensor_getResult() > MOISTURE_THRESHOLD) {
        SPI_sendMoisture(MoistureSensor_getResult());
        //move to top left corner
        //start firing
        //move to top right corner
        //move down to middle
        //move to middle move to middle left side
        //move down to bottom
        //move to bottom right side
        //stop firing
    }
}

void standbyMode(void) {
    UART_1_PutString("Sleepy time - entering hibernation!\n\r");
    CyPmHibernate(); //Hibernate - use hardware reset to start PSoC again
}

/* [] END OF FILE */