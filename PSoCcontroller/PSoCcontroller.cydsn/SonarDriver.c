#include "SonarDriver.h"

void Sonar_Start(){
    Trigger_1_Write(0);
    Trigger_2_Write(0);
    sonarTimerDone = 0;
    Timer_Sonar_Start();
}

struct position Sonar_GetPosition(){
        Trigger_1_Write(1);
        CyDelayUs(10);
        Trigger_1_Write(0);
        
        while(Echo_1_Read() != 1){}
       
        Timer_Sonar_WriteCounter(16777215);
        while(Echo_1_Read() == 1){}
        
        uint32_t timervaerdi = Timer_Sonar_ReadCounter();
    
        double time = ((double)16777215.0 - (double)timervaerdi)/(double)24.0;
        double distance_sonar_1 = time/58.0;
         //double distance = (time * 340.0)/2; 
   
        UART_1_PutString("read 1 done \n\r");
        //Delay between readings:
        CyDelay(60);
        
        //Sonar 2 reading:
        Trigger_2_Write(1);
        CyDelayUs(10);
        Trigger_2_Write(0);
        
        while(Echo_2_Read() != 1){}
        Timer_Sonar_WriteCounter(16777215);
        while(Echo_2_Read() == 1){}
        
        timervaerdi = Timer_Sonar_ReadCounter();
    
        double timeus = ((double)16777215.0 - (double)timervaerdi)/(double)24.0;
        double distance_sonar_2 = timeus/58.0;
         //double distance = (time * 340.0)/2; 
        
        UART_1_PutString("read 2 done \n\r");
        if(distance_sonar_1 < 2.5 || distance_sonar_1 > 55){
            //Pigeon not detected
            distance_sonar_1 = 0;
        }
            
        if(distance_sonar_2 < 2.5 || distance_sonar_2 > 55){
            //Pigeon not detected
            distance_sonar_2 = 0;
        }
   
        if (distance_sonar_1 !=0 && distance_sonar_2 != 0){
                
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
                struct position p = {1,width,distance_sonar_2-2};
                return  p;         
        }
        else {
            //Pigeon Not detected. An empty struct is returned
            
                //Struct holding, pigeon detected positive, width, and distance.  
                struct position p = {0,0,0};
                return  p;   
        }
    
}
