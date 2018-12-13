

#include "WaterSensor.h"
#include "PSoCcontroller.h"
void WaSensInit()
{
    ADC_SAR_WaSens_Start();
    //PWM_WaSens_Start();
}


int WaSensMeasure()
{
    ADC_SAR_WaSens_StartConvert();
    // OBS - værdier skal omkalibreres når kredsløb er færdigt
    double Factor1 = 0.0002783;
    double Factor2 = -2.486;
    double Offset1 = 5683;
    uint16_t result;
    uint16_t result2;

    if (ADC_SAR_WaSens_IsEndConversion(ADC_SAR_WaSens_WAIT_FOR_RESULT))
        {
            result = ADC_SAR_WaSens_GetResult16(); //ADC ukonverteret resultat
//            char msg[256];
//            snprintf(msg, sizeof(msg), "ADC result: %d\n\r", result);
//            UART_1_PutStringConst(msg);
            if(result < 3920) //Skal vandbeholderen fyldes...
            {
                result2 = (result*result*Factor1) + (result*Factor2) + Offset1; //Resultat konverteres til mL
//                if(Pin_Low_WL_Read())
//                {
//                    Pin_Low_WL_Write(0);
//                }
            }
            else //Ellers
            {
                result2 = 0; //Resultat konverteres til mL
//                if(!Pin_Low_WL_Read())
//                {
//                    Pin_Low_WL_Write(1);
//                }
            }
            return result2;
        }
    else
        return 0;
}