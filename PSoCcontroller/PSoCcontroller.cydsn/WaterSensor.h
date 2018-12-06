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
#ifndef WATERSENSOR_H
#define WATERSENSOR_H
    
#include "project.h"

void WaSensInit()
{
    ADC_SAR_WaSens_Start();
    PWM_WaSens_Start();
}

int WaSensMeasure()
{
    ADC_SAR_WaSens_StartConvert();
    // OBS - værdier skal omkalibreres når kredsløb er færdigt
    double Factor1 = 0.000297;
    double Factor2 = -2.579;
    double Offset1 = 5783;
    uint16_t result;
    uint16_t result2;
    
    CyDelayUs(100); //Tid til at konvertere
    if (ADC_SAR_WaSens_IsEndConversion(ADC_SAR_WaSens_WAIT_FOR_RESULT))
        {
            result = ADC_SAR_WaSens_GetResult16(); //ADC ukonverteret resultat
            if(result < 4090) //Er vandstanden under 500 mL
            {
                result2 = (result*result*Factor1) + (result*Factor2) + Offset1; //Resultat konverteres til mL
                if(Pin_Low_WL_Read())
                {
                    Pin_Low_WL_Write(0);
                }
            }
            else //Eller over 500 mL
            {
                result2 = 0; //Resultat konverteres til mL
                if(!Pin_Low_WL_Read())
                {
                    Pin_Low_WL_Write(1);
                }
            }
            return result2;
        }
    else
        return 0;
}
    
#endif

/* [] END OF FILE */
