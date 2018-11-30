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

CY_ISR_PROTO(uart_isr_handler);

uint8 moveFlag = 0;

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_1_Start();
    uart_isr_StartEx( uart_isr_handler );
    
    initX();

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    
    for(;;)
    {
        if (moveFlag == 1) {
            moveDegreesX(15);
            moveFlag = 0;
        }
    }
}

CY_ISR( uart_isr_handler ){
    switch(UART_1_ReadRxData()) {
        case 1:
            moveFlag = 1;
            break;
        default:
            break;
    }
}

/* [] END OF FILE */
