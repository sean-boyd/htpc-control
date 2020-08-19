#include "computer.h"


/************************************************* 
Constructor
*************************************************/
Computer::Computer() {
   STARTUP(Keyboard.begin());
   //Keyboard.begin();
   
   power = OFF;
}


/************************************************* 
Turn the computer off
*************************************************/
void Computer::powerOff() {
    
    Keyboard.click(KEY_POWER);
    
    this->power = OFF;
}


/************************************************* 
Turn the computer on
*************************************************/
void Computer::powerOn() {
    
    Keyboard.click(KEY_LSHIFT);
    
    this->power = ON;
}