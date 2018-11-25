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
#include <project.h>
#define TIME 15

enum state {NORTH, EAST, SOUTH, WEST};  //Steppermotorcoils 4 positioner

int stepperPosition;
enum state stepperState;

void init();
int getPosition();
void rotateClockwise();
void rotateCounterClockwise();
void moveStep();
void moveDegrees(int deg);
void resetPosition();

/* [] END OF FILE */
