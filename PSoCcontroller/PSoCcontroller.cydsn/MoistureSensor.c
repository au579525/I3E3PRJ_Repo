/* ========================================
 * PIGEON EXTERMINATION SYSTEM
 * Moisture Sensor Driver
 * Source-file
 * 
 * Author: Lasse Krarup
 *
 * ========================================
*/
#include "MoistureSensor.h"

void MoistureSensor_init(void) {
    ADC_Moisture_Start();   
}

int MoistureSensor_getResult(void) {
    ADC_Moisture_StartConvert();
    while(!ADC_Moisture_IsEndConversion(ADC_Moisture_WAIT_FOR_RESULT)); //wait for result
    
    return ADC_Moisture_GetResult16();
}

/* [] END OF FILE */
