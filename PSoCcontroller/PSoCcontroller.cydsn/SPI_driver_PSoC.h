/* ========================================
 *
 * Copyright ASE, 2018
 * All Rights Reserved
 * UNPUBLISHED, LICENSED SOFTWARE.
 *
 * SPI Slave driver til Pigeon Exterminations System
 * Frederik Midtgaard
 *
 * ========================================

*/


/*
Driver expects a SPI_slave device named SPI_1. The SPI_slave has an interrupt named SPI_ISR. 
SPI_slave uses internal clock, and bitrate of 1000kbps
*/

#pragma once

#include <stdio.h>
#include "project.h"



uint8_t SPI_recieved_flag;
char SPI_recieved;
CY_ISR_PROTO( ISR_SPI_RX_handler );

void SPI_start();

void SPI_send_pigeon_detected();

void SPI_send_resetToDefault();

void SPI_send_water_empty();

void SPI_send_flowers_watered();

void SPI_send_pigeon_shot_position(char,char);
void SPI_send_waterlevel(uint8 waterlevel);

void Handle_SPI_recieved();



/* [] END OF FILE */


