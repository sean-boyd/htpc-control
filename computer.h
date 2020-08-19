#pragma once
#include "application.h"

class Computer {
    
    public:
        Computer();
        void powerOff();
        void powerOn();      
        bool power;
        
    private:
        const bool OFF = false;
        const bool ON = true;
        
};
