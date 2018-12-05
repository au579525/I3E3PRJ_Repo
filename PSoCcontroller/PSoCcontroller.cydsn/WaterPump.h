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
#ifndef WATERPUMP_H
#define WATERPUMP_H
    #include "project.h"

    void initWaterPump(void) {
        UART_1_PutString("Initiating Water Pump\n\r");   
        Pin_WaterPump_Write(0);
    }

    void WaterPump_fireWater(int x) {
        if (x == 0) {
            UART_1_PutString("Stopping Water Pump\n\r");  
            Pin_WaterPump_Write(0);
        }
        else if (x == 1) {
            UART_1_PutString("Starting Water Pump\n\r");  
            Pin_WaterPump_Write(1);
        }
    };

#endif    
/* [] END OF FILE */
