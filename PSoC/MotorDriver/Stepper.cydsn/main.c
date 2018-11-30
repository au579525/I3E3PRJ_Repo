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
#include "project.h"
#include "MotorDriver.h"

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    stepper_isr_StartEx(stepper_isr_handler);
    
    for(;;)
    {
        moveDegreesX(6);
        CyDelay(1000);
    }
}

/* [] END OF FILE */
