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
