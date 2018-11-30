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
#include <project.h>
#include <stdlib.h>
#include <math.h>

#define TIME 15

enum state {NORTH, EAST, SOUTH, WEST};  //Steppermotorcoils 4 positioner

int stepperPositionX;
enum state stepperStateX;

CY_ISR_PROTO(stepper_isr_handler);

void initX();
static void rotateClockwiseX();
static void rotateCounterClockwiseX();
static void moveStepX();
void moveDegreesX(int deg);
static void resetPositionX();

/* [] END OF FILE */
