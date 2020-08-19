#include "tv.h"


/*
Sample Commands:
byte TVCommandOff[8] =  { 0x08, 0x22, 0x00, 0x00, 0x00, 0x01, 0xD5, 0x0D };  // 0x0D is Carriage Return
byte TVCommandOn[8] =   { 0x08, 0x22, 0x00, 0x00, 0x00, 0x02, 0xD4, 0x0D };
*/


/************************************************* 
Constructor
*************************************************/
TV::TV() {
    Serial1.begin(9600);    //Serial1 = Photon TX/RX pins / Serial = USB virtual COM port
    
    power = OFF;
    backlight = 7;
    brightness = 77;
    input = "?";
    mode = "?";

}


/************************************************* 
Send TV Command via Samsung Ex-Link
*************************************************/
void TV::sendMessage(const byte messageCommand[], const byte messageValue) {

    for (int i = 0; i < (sizeof(messagePreamble)/sizeof(messagePreamble[0])); i++) {
        Serial1.write(messagePreamble[i]);
        }

    for (int i = 0; i < sizeOfMessageCommand; i++) {
        Serial1.write(messageCommand[i]);
        }

    Serial1.write(messageValue);
    
    Serial1.write(calculateChecksum(messageCommand, messageValue));
    
    Serial1.write(messageEndOfFrame);

}


/************************************************* 
Calculate TV Command Checksum
*************************************************/
byte TV::calculateChecksum(const byte messageCommand[], const byte messageValue) {

    byte checksum = 0x00; // Math ==> Checksum = 2^8 - (preamble + command + value)
    
    for (int i = 0; i < (sizeof(messagePreamble)/sizeof(messagePreamble[0])); i++) {
        checksum = checksum - messagePreamble[i];
        }

    for (int i = 0; i < sizeOfMessageCommand; i++) {
        checksum = checksum - messageCommand[i];
        }

    checksum = checksum - messageValue; // + 1;
    
    return checksum;
}


/************************************************* 
Turn TV Off
*************************************************/
void TV::powerOff() {
    
    sendMessage(commandPower, valuePowerOff);
    this->power = OFF;
}  


/************************************************* 
Turn TV On
*************************************************/
void TV::powerOn() {
    
    sendMessage(commandPower, valuePowerOn);
    this->power = ON;
}


/************************************************* 
Set TV Backlight (value 0 to 20)
*************************************************/
void TV::setBacklight(byte value) {
    
    // constrain to 0 to 20
    byte backlightValue = constrain(value, 0, 20);
    
    sendMessage(commandBacklight, backlightValue);
    this->backlight = backlightValue;
}


/************************************************* 
Set TV Brightness (value 0 to 100)
*************************************************/
void TV::setBrightness(byte percent) {
    
    // constrain to 0 to 100
    byte brightnessValue = constrain(percent, 0, 100);
    
    sendMessage(commandBrightness, brightnessValue);
    this->brightness = brightnessValue;
}


/************************************************* 
Set TV Input to HDMI1, HDMI2, or HDMI3
*************************************************/
void TV::setInputHDMI(int input) {
    
    if (input == 1) {
        sendMessage(commandInputHDMI, valueInputHDMI1);    
    }
    else if (input == 2) {
        sendMessage(commandInputHDMI, valueInputHDMI2);    
    }
    else if (input == 3) {
        sendMessage(commandInputHDMI, valueInputHDMI3);    
    }
    this->input = "HDMI" + String(input);
}


/************************************************* 
Set TV Input to PC
*************************************************/
void TV::setInputPC() {
    
    sendMessage(commandInputPC, valueInputPC);
    this->input = "PC";
}


/************************************************* 
Set TV Mode to Movie
*************************************************/
void TV::setModeEntertain() {
    
    sendMessage(commandSetMode, valueEntertain);
    this->mode = "Entertain";
}


/************************************************* 
Set TV Mode to Standard
*************************************************/
void TV::setModeStandard() {
    
    sendMessage(commandSetMode, valueStandard);
    this->mode = "Standard";
}