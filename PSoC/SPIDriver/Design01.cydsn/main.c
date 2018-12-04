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

#include <stdio.h>
#include "SPI_driver_PSoC.h"
#include "project.h"
static char outputBuffer[256];

CY_ISR_PROTO(ISR_UART_RX_handler);
CY_ISR_PROTO(ISR_SPI_RX_handler);

void handleByteReceived(uint8_t);


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    /* Place your initialization/startup code here (e.g. MyInst_Start()) */
    
    SPI_start();
    UART_RX_interrupt_StartEx(ISR_UART_RX_handler);
    UART_1_Start();
    
    
    UART_1_PutString("Program Startet");
    
    
    for(;;)
    {
       
        if (SPI_recieved_flag == 1){
            Handle_SPI_recieved();
            UART_1_PutString("Something recieved");
            snprintf(outputBuffer, sizeof(outputBuffer), "Data recived from pi: %c\n\r", SPI_recieved); 
            UART_1_PutString(outputBuffer);
            
        }
    }
}



CY_ISR(ISR_UART_RX_handler) //interrupt rutine til at læse UART input
{
    uint8_t bytesToRead = UART_1_GetRxBufferSize();
    while (bytesToRead > 0)
    {
        uint8_t byteReceived = UART_1_ReadRxData();
        UART_1_WriteTxData(byteReceived); // echo back
        
        handleByteReceived(byteReceived);
        
        bytesToRead--;
    }
}

void handleByteReceived(uint8_t byteReceived)// funktion til at håndterer modtaget UART data
{
    switch(byteReceived)
    {
        case 'a' :
        {
            //SPI_send_pigeon_shot_position(55,3);
            SPI_send_pigeon_shot_position(55,3);        
        }
        break;

        case 'b' :
        {
           SPI_send_low_water();
        }
        break;
        
        default :
        {
            // nothing
        }
        break;
    }
}



/* [] END OF FILE */
