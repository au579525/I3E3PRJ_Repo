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
            
            CyDelayUs(50);
            
            SPI_read_req_Write(0);
            
}


void SPI_send_low_water(){
            
            SPI_1_WriteTxDataZero('c');
            
            //UART_1_PutString("Writing status - to Raspberry Pi");
            
            SPI_read_req_Write(1);
            
            CyDelayUs(50);
            
            SPI_read_req_Write(0);
            
}

void SPI_send_water_empty(){
            SPI_1_WriteTxDataZero('d');
            
            //UART_1_PutString("Writing status - to Raspberry Pi");
            
            SPI_read_req_Write(1);
            
            CyDelayUs(50);
            
            SPI_read_req_Write(0);
}

void SPI_send_flowers_watered(){
            SPI_1_WriteTxDataZero('e');
            
            //UART_1_PutString("Writing status - to Raspberry Pi");
            
            SPI_read_req_Write(1);
            
            CyDelayUs(50);
            
            SPI_read_req_Write(0);
}

void SPI_send_pigeon_shot_position(char pigeon_position_x, char pigeon_position_y){
    
            SPI_1_WriteTxDataZero('a');
            
            SPI_read_req_Write(1);
            
            CyDelayUs(50);
            
            SPI_read_req_Write(0);
            
            CyDelayUs(5000); //Thinking time for RPI
            
            //Sending position x
            
            SPI_1_WriteTxDataZero(pigeon_position_x);
            
            SPI_read_req_Write(1);
            
            CyDelayUs(50);
            
            SPI_read_req_Write(0);
            
            CyDelayUs(5000); //Thinking time for RPI
            
            //Sending position y
            
            SPI_1_WriteTxDataZero(pigeon_position_y);
            
            SPI_read_req_Write(1);
            
            CyDelayUs(50);
            
            SPI_read_req_Write(0);
            
            CyDelayUs(5000); //Thinking time for RPI
            
            
}

void Handle_SPI_recieved(){
    SPI_recieved_flag = 0;
}



/* [] END OF FILE */
