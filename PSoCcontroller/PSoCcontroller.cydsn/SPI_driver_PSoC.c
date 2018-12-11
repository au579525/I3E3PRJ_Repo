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

#include "SPI_driver_PSoC.h"
#include "PSoCcontroller.h"
#include "MotorDriverX.h"
#include "MotorDriverY.h"
#include "WaterPump.h"

void SPI_start(){
    SPI_recieved_flag = 0;
    SPI_ISR_StartEx(ISR_SPI_RX_handler);
    SPI_1_Start();
    SPI_read_req_Write(0);
}

void SPI_send_pigeon_detected(){
            SPI_1_WriteTxDataZero('b');
            
            //UART_1_PutString("Writing status - to Raspberry Pi");
            
            SPI_read_req_Write(1);
            
            CyDelayUs(1);
            
            SPI_read_req_Write(0);
            
}


void SPI_send_resetToDefault(){
            
            SPI_1_WriteTxDataZero('c');
            
            //UART_1_PutString("Writing status - to Raspberry Pi");
            
            SPI_read_req_Write(1);
            
            CyDelayUs(1);
            
            SPI_read_req_Write(0);
            
}

void SPI_send_water_empty(){
            SPI_1_WriteTxDataZero('d');
            
            //UART_1_PutString("Writing status - to Raspberry Pi");
            
            SPI_read_req_Write(1);
            
            CyDelayUs(1);
            
            SPI_read_req_Write(0);
}

void SPI_send_flowers_watered(){
            SPI_1_WriteTxDataZero('e');
            
            //UART_1_PutString("Writing status - to Raspberry Pi");
            
            SPI_read_req_Write(1);
            
            CyDelayUs(1);
            
            SPI_read_req_Write(0);
}

void SPI_send_pigeon_shot_position(char pigeon_position_x, char pigeon_position_y){
    
            SPI_1_WriteTxDataZero('a');
            
            SPI_read_req_Write(1);
            
            CyDelayUs(1);
            
            SPI_read_req_Write(0);
            
            CyDelay(5); //Thinking time for RPI
            
            //Sending position x
            
            SPI_1_WriteTxDataZero(pigeon_position_x);
            
            SPI_read_req_Write(1);
            
            CyDelayUs(1);
            
            SPI_read_req_Write(0);
            
            CyDelay(5); //Thinking time for RPI
            
            //Sending position y
            
            SPI_1_WriteTxDataZero(pigeon_position_y);
            
            SPI_read_req_Write(1);
            
            CyDelayUs(1);
            
            SPI_read_req_Write(0);
            
            CyDelay(5); //Thinking time for RPI
            
            
}

void SPI_send_waterlevel(uint8 waterlevel) {
       
            SPI_1_WriteTxDataZero('f');
            
            SPI_read_req_Write(1);
            CyDelayUs(1);
            SPI_read_req_Write(0);
            
            CyDelay(5); //Thinking time for RPI
            
            SPI_1_WriteTxDataZero(waterlevel);
            
            SPI_read_req_Write(1);
            CyDelayUs(1);
            SPI_read_req_Write(0);
            
            CyDelay(5); //Thinking time for RPI
}

void Handle_SPI_recieved(){
    UART_1_PutString("Command received from SPI: ");
    UART_1_PutChar(SPI_recieved);
    UART_1_PutString("\n\r");
    
    switch(SPI_recieved) {
        case 'A': //NORMAL MODE
            setMode(NORMAL_MODE);
            break;
        case 'B': //MANUAL MODE
            setMode(MANUAL_MODE);
            break; 
        case 'C': //POWERSAVING MODE
            setMode(POWERSAVING_MODE);
            break;
        case 'D': //STANDBY MODE
            setMode(STANDBY_MODE);
            break;
        case 'E': //AUTOMATISK VANDING
            setMode(AUTOMATISK_VANDING);
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
        
    SPI_recieved_flag = 0;
}

/* [] END OF FILE */
