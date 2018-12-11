    #include "WaterPump.h"
    
    void initWaterPump(void) {
        Pin_WaterPump_Write(0);
    }

    void WaterPump_fireWater(int x) {
        if (x == 0) {
            Pin_WaterPump_Write(0);
        }
        else if (x == 1) {
            Pin_WaterPump_Write(1);
        }
    }
    