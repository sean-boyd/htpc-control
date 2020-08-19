#pragma once
#include "application.h"

class TV {

    public:
        bool power;
        int backlight;
        int brightness;
        String input;
        String mode;
        
        TV();
        void powerOff();
        void powerOn();
        void setBacklight(byte);
        void setBrightness(byte);
        void setInputHDMI(int);
        void setInputPC();
        void setModeEntertain();
        void setModeStandard();

    private:

        const bool OFF = false;
        const bool ON = true;
        
        const int sizeOfMessageCommand = 3;
        
        const byte messagePreamble[2] =  {0x08, 0x22};
        const byte messageEndOfFrame =  0x0D;  // 0x0D is Carriage Return
        
        const byte commandPower[3] =  {0x00, 0x00, 0x00};
        const byte valuePowerOff =  0x01;
        const byte valuePowerOn =  0x02;
        
        const byte commandInputPC[3] =  {0x0A, 0x00, 0x04};
        const byte valueInputPC =  0x00;
                
        const byte commandInputHDMI[3] =  {0x0A, 0x00, 0x05};
        const byte valueInputHDMI1 =  0x00;
        const byte valueInputHDMI2 =  0x01;
        const byte valueInputHDMI3 =  0x02;     
                
        const byte commandSetMode[3] =  {0x0B, 0x00, 0x00};
        const byte valueEntertain =  0x00;
        const byte valueStandard =  0x01;
        
        const byte commandBacklight[3] =  {0x0B, 0x01, 0x00};
                
        const byte commandBrightness[3] =  {0x0B, 0x03, 0x00};

        void sendMessage(const byte[], const byte);
        byte calculateChecksum(const byte[], const byte);
        
};