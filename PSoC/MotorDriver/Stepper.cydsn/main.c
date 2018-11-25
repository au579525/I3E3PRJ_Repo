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

#define TIME 15

int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    Pin_1_Write(0);
    Pin_2_Write(0);

    while(Pin_3_Read() == 0) {
        Pin_1_Write(1);
        CyDelay(TIME);
        Pin_2_Write(1);
        CyDelay(TIME);
        Pin_1_Write(0);
        CyDelay(TIME);
        Pin_2_Write(0);
        CyDelay(TIME);
    }
    for(;;)
    {
        
        Pin_1_Write(1);
        CyDelay(TIME);
        Pin_2_Write(1);
        CyDelay(TIME);
        Pin_1_Write(0);
        CyDelay(TIME);
        Pin_2_Write(0);
        CyDelay(TIME);
    }
}

/* [] END OF FILE */
