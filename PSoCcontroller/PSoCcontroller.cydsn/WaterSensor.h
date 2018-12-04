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
        UART_1_PutString("Initiating Water Sensor\n\r");  
        ADC_SAR_WaSens_Start();
        PWM_WaSens_Start();
        Pin_Low_WL_Write(0);
    }

    int WaSensMeasure()
    {
        UART_1_PutString("Returning water level\n\r"); 
        
        return 1; // FOR TESTING!! REMOVE!!!!!!!!!
        
        ADC_SAR_WaSens_StartConvert();
        // OBS - værdier skal omkalibreres når kredsløb er færdigt
        double Factor1 = -0.6984;
        double Offset1 = 740;
        uint16_t result;
        uint16_t result2;
        
        CyDelayUs(100); //Tid til at konvertere
        if (ADC_SAR_WaSens_IsEndConversion(ADC_SAR_WaSens_WAIT_FOR_RESULT))
            {
                result = ADC_SAR_WaSens_GetResult16(); //ADC ukonverteret resultat
                result2 = result*Factor1 + Offset1; //Resultat konverteres til mL - skal omkalibreres når kredsløb er færdigt
                
                //Tjek for lav vandstand. Pin går til LED på PSU
                if(result2 < 200 && !Pin_Low_WL_Read())
                {
                    Pin_Low_WL_Write(1);
                }
                else if(result2 > 200 && Pin_Low_WL_Read())
                {
                    Pin_Low_WL_Write(0);
                }
                
                return result2;
            }
        else
            return 0;
    }
    
#endif

/* [] END OF FILE */
