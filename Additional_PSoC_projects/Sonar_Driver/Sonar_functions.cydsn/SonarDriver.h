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

//Project Must Have A 24Bit TimerNamed: Timer_Sonar With Max Counter == 16777216 
//Project must have Input Pins Echo_1 and Echo_2, And Trigger_1 and Trigger_2

#include <stdio.h>
#include "project.h"


struct position{
    uint8_t detected;
    int width;
    double distance;
};

void SonarDriverStart(){
    Trigger_1_Write(0);
    Trigger_2_Write(0);
    Timer_Sonar_Start();
}

struct position GetPigeonPos(){
         //Start Sonar 1, with 10 us pulse on Trigger 1: 
        Trigger_1_Write(1);
        CyDelayUs(10);
        Trigger_1_Write(0);
        
        //Wait for Echo_1 to go high 
        while(Echo_1_Read() != 1){}
        
        //Reset timer:
        Timer_Sonar_WriteCounter(16777215);
       
        //Wait for Echo_1 to go low (Sonar has recieved echo)
        while(Echo_1_Read() == 1){}
        
        //Calculate the time Echo_1 was high:
        uint32_t timervaerdi = Timer_Sonar_ReadCounter();
        double time = ((double)16777215.0 - (double)timervaerdi)/(double)24.0;
        
        //Calculate distance to object 
        double distance_sonar_1 = time/58.0;
    
        //Delay between readings:
        CyDelay(60);
        
        //Sonar 2 reading:
        Trigger_2_Write(1);
        CyDelayUs(10);
        Trigger_2_Write(0);
        
        //UART_1_PutString("Waiting for echo_2_read != 0");
        while(Echo_2_Read() != 1){}
        Timer_Sonar_WriteCounter(16777215);
        //UART_1_PutString("Waiting for echo_2_read == 1");
        while(Echo_2_Read() == 1){}
        
        timervaerdi = Timer_Sonar_ReadCounter();
    
        double timeus = ((double)16777215.0 - (double)timervaerdi)/(double)24.0;
        double distance_sonar_2 = timeus/58.0;
        
        
        
         //double distance = (time * 340.0)/2; 
        if(distance_sonar_1 < 2.5 || distance_sonar_1 > 55){
            //Pigeon not detected
            distance_sonar_1 = 0;
        }
            
        if(distance_sonar_2 < 2.5 || distance_sonar_2 > 55){
            //Pigeon not detected
            distance_sonar_2 = 0;
        }
            
        if (
            distance_sonar_1 !=0 && distance_sonar_2 != 0){
                
                uint8_t width = 2; //Both Sonars detect pigeon, so assumed to be in position 2 of 3.
                //Average distance is calculated
                double calculated_distance = ((distance_sonar_1+distance_sonar_2)/2)-5;
                
                //Struct holding, pigeon detected positive, width, and distance.  
                struct position p = {1,width,calculated_distance};
                return  p; 
            }
            
        else if(distance_sonar_1 !=0 && distance_sonar_2 == 0){
                 uint8_t width = 3; //Only Sonar 1 detects pigeon, so assumed to be in position 3 of 3.
               
                
                //Struct holding, pigeon detected positive, width, and distance.  
                struct position p = {1,width,distance_sonar_1-5};
                return  p;         
        }
         else if(distance_sonar_1 ==0 && distance_sonar_2 != 0){
                 uint8_t width = 1; //Only Sonar 1 detects pigeon, so assumed to be in position 1 of 3.
               
                //Struct holding, pigeon detected positive, width, and distance.  
                struct position p = {1,width,distance_sonar_2-5};
                return  p;         
        }
        else {
            //Pigeon Not detected. An empty struct is returned
            
                //Struct holding, pigeon detected positive, width, and distance.  
                struct position p = {0,0,0};
                return  p;   
        }
    
}

/* [] END OF FILE */
