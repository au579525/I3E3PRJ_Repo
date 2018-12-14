#ifndef PSOCCONTROLLER_H
#define PSOCCONTROLLER_H
    
    #include "CircularBuffer.h"
    #include "SonarDriver.h"
    
    #define TRUE 1
    #define FALSE 0
    #define WATER_THRESHOLD_NO_WATER 0
    #define WATER_THRESHOLD_LOW_WATER 0
    #define MOISTURE_THRESHOLD 3000
    #define DELAY_NORMAL_MODE_MS 3000 //should be 3000
    #define DELAY_POWERSAVING_MODE_MS 60000 //should be 60000

    CY_ISR_PROTO( WaterLevelISRhandler);
    CY_ISR_PROTO( DelayTimerInterrupt );
    CY_ISR_PROTO( stepperX_interrupt_handler );
    CY_ISR_PROTO( stepperY_interrupt_handler );
    
    enum Mode{ //enum for readability and for validation (on setMode function)
        NORMAL_MODE, POWERSAVING_MODE, MANUAL_MODE, AUTOMATISK_VANDING, STANDBY_MODE
    };
    
    enum Mode mode;

    int noWater; // C-language bool-like integer

    struct position pigeonPosition;
    struct CircBuf circBuf;
    
    void setMode(enum Mode);
    void checkForPigeonAndShoot(void);

    void (*currentState)(void); //function pointer for state machines
    void normalMode(void);
    void powersavingMode(void);
    void manualMode(void);
    void automatiskVanding(void);
    void standbyMode(void);
  
#endif    