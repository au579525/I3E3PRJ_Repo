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
#include "project.h"
#include "SonarDriver.h"

#define  FREQUENZY 24000000.0 

CY_ISR_PROTO(ISR_UART_RX_handler); //Prototype for UART interrupt
//CY_ISR_PROTO(isr_echo_recieved_handler);
//CY_ISR_PROTO(isr_1_handler);

void handleByteReceived(uint8_t); //Prototype for UART funktion
static char outputBuffer[256];
uint8_t flag = 1;
uint8_t flagstart = 0;


int main(void)
{
    CyGlobalIntEnable; /* Enable global interrupts. */
    UART_RX_interrupt_StartEx(ISR_UART_RX_handler);
    //isr_echo_recieved_StartEx(isr_echo_recieved_handler);
    Sonar_Start();
    //Klargører hardware:
    UART_1_Start();
   
    //Timer_1_EnableTrigger();
   
    UART_1_PutString("Program Startet\n Type: 1 to start \n");

    /* Place your initialization/startup code here (e.g. MyInst_Start()) */

    for(;;)
    {
        /* Place your application code here. */
        
        
        while(flagstart != 1){}
        flagstart = 0;
        
        struct position p = Sonar_GetPosition();
        
        if (p.detected == 1){
        snprintf(outputBuffer, sizeof(outputBuffer), "Pigeon detected in position: %d, with the distance: %.3f\n\r",p.width,p.distance); 
        }
        else
        {
         snprintf(outputBuffer, sizeof(outputBuffer), "Pigeon not detected\n\r");    
        }

        UART_1_PutString(outputBuffer);
        
        
        /*
        Trigger_1_Write(1);
        CyDelayUs(10);
        Trigger_1_Write(0);
        
        
        while(Echo_1_Read() != 1){}
       
        Timer_Sonar_WriteCounter(16777215);
       
        while(Echo_1_Read() == 1){}
        
        uint32_t timervaerdi = Timer_Sonar_ReadCounter();
    
        double time = ((double)16777215.0 - (double)timervaerdi)/(double)24.0;
        double distance = time/58.0;
         //double distance = (time * 340.0)/2; 
   
        snprintf(outputBuffer, sizeof(outputBuffer), "Sensor 1: %.3f\n\r",distance); 

        UART_1_PutString(outputBuffer);
        
        //Delay between readings:
        CyDelay(60);
        
        //Sonar 2 reading:
        
        Trigger_2_Write(1);
        CyDelayUs(10);
        Trigger_2_Write(0);
        
        //UART_1_PutString("Waiting for echo_2_read != 0");
        while(Echo_2_Read() != 1){}
       
        Timer_Sonar_WriteCounter(16777215);
       
        //UART_1_PutString("Waiting for echo_2_read == 1");
        while(Echo_2_Read() == 1){}
        
        timervaerdi = Timer_Sonar_ReadCounter();
    
        double timeus = ((double)16777215.0 - (double)timervaerdi)/(double)24.0;
        double distance2 = timeus/58.0;
         //double distance = (time * 340.0)/2; 
   
        snprintf(outputBuffer, sizeof(outputBuffer), "Sensor 2: %.3f\n\r", distance2); 

        UART_1_PutString(outputBuffer);
        */
        
    }
        
       
    
    
}

/*CY_ISR_PROTO(isr_echo_recieved_handler){
    CyGlobalIntDisable;
    
    UART_1_PutString("interrupt");
    uint32_t timervaerdi = Timer_1_ReadCapture();
    
    double time = ((double)16777216.0 - (double)timervaerdi)/(double)24.0;
    double distance = time/58.0;
    //double distance = (time * 340.0)/2; 
   
    snprintf(outputBuffer, sizeof(outputBuffer), "Sensor %d: %.3f\n\r", counter,distance); 

    UART_1_PutString(outputBuffer);
    
    counter++;
    
    //flag = 1;
    
    if (counter == 3){
        counter = 1;}
   
    
    Timer_1_ClearFIFO();
    //CyDelay(1);
    CyGlobalIntEnable
   
}


*/
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
        case '1' :
        {
            flagstart = 1;
        }
        break;

        case '0' :
        {
            
           //LED_status sættes til 0, så LED ønskes slukket
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
