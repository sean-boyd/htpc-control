#include <Adafruit_SSD1306.h>
#include "application.h"
#include "computer.h"
#include "tv.h"
#include "receiver.h"

/************************************************* 
HTPCControl

Modes:
- Off: Everything off
- On: Everything on, TV on full backlight
- Night: Same as "On", but TV on mid-value backlight
- Dark: Same as "On", but TV on zero backlight
- Stealth: Computer only; no Receiver or TV
- Music: Receiver only; no Receiver or TV

INPUTS:
A4 - PC Fan Power Input - 5V input = Pin Low, 100K pull-up (hardware interrupt)

OUTPUTS:
A3 - PC Power Switch Output - Pin High = Switch pressed (Requires 50ms press + delay of 2s before next press)
D7 - Onboard LED

SERIAL COMMUNICATION:
TX - SERIAL TX (Connect to TV TRS-Ring/RX)
RX - SERIAL RX (Connect to TV TRS-Tip/TX)

OLED DISPLAY:
D0 - OLED MOSI
D1 - OLED CLK
D2 - OLED DC
D3 - OLED CS
D4 - OLED RESET

*************************************************/

//STARTUP(WiFi.selectAntenna(ANT_EXTERNAL)); // selects the external antenna

const bool OFF = false;
const bool ON = true;

// Pin Definitions
const int PC_POWER_DETECT = A4;     // PC power detection input
const int PC_POWER_SWITCH = A3;     // PC power button output
const int ONBOARD_LED = D7;         // Photon onboard LED

// OLED Pin Definitions
const int OLED_MOSI = D0;
const int OLED_CLK = D1;
const int OLED_DC = D2;
const int OLED_CS = D3;
const int OLED_RESET = D4;

Adafruit_SSD1306 display(OLED_MOSI, OLED_CLK, OLED_DC, OLED_RESET, OLED_CS);


// Variables
const int powerToggleDelayInMS = 500;   // 7500ms is known to work correctly (used to be 5000ms = 5s)

bool PCState = OFF;                     // Current state of the computer
bool lastPCState = OFF;                 // Previous state of the computer
String systemMode = "?";


STARTUP(Keyboard.begin());


Computer computer;
TV tv;
Receiver receiver;



/************************************************* 
Setup
*************************************************/
void setup() {
    
    Particle.variable("systemMode", systemMode);
    Particle.variable("computerPower", computer.power);
    Particle.variable("receiverPower", receiver.power);
    Particle.variable("receiverInput", receiver.input);
    Particle.variable("tvPower", tv.power);
    Particle.variable("tvBacklight", tv.backlight);
    Particle.variable("tvBrightness", tv.brightness);
    Particle.variable("tvInput", tv.input);
    Particle.variable("tvMode", tv.mode);
    
    Particle.variable("lastPCstate", lastPCState);
    Particle.variable("PCstate", PCState);
    
    
    // Register Cloud Functions
    Particle.function("setMode", setMode);
    
    Particle.function("setModeOff", setModeOff);
    Particle.function("setModeOn", setModeOn);
    Particle.function("setModeNight", setModeNight);
    Particle.function("setModeDark", setModeDark);
    Particle.function("setModeStealth", setModeStealth);
    Particle.function("setModeMusic", setModeMusic);
    
    Particle.function("setBacklight", setBacklight);
    Particle.function("setBrightness", setBrightness);
    
    
    Keyboard.begin();

    
    // Initialise I/O
    pinMode(PC_POWER_DETECT, INPUT);
    attachInterrupt(PC_POWER_DETECT, PCPowerDetectISR, CHANGE);    // Initialize interrupt
    
    pinMode(PC_POWER_SWITCH, OUTPUT);
    digitalWrite(PC_POWER_SWITCH, LOW);
    
    pinMode(ONBOARD_LED, OUTPUT);
    digitalWrite(ONBOARD_LED, LOW);
    
    
    /* DETERMINE INITIAL STATE */
    if (digitalRead(PC_POWER_DETECT) == LOW) {
        PCState = ON;
    }

    
    display.begin(SSD1306_SWITCHCAPVCC);
    display.clearDisplay();
}


/************************************************* 
Main Loop
*************************************************/
void loop() {
    
    /*
    if (PCState != LastPCState) {
        if (PCState == ON) {
            computer.powerOn(); //start
            LastPCState = ON;
        }
        else {
            computer.powerOff(); //test
            LastPCState = OFF;
        }    
    }
    */
    
    
    updateScreen();
    
    delay(powerToggleDelay);  // Delay for receiver delay between toggling power
}


/************************************************* 
Display Function
*************************************************/
void updateScreen() {
    display.clearDisplay();
    
    display.setTextSize(1);
    display.setTextColor(WHITE);
    display.setCursor(0,0);

    display.print("Mode: ");
    display.println(systemMode);
    
    display.println();

    display.print("Computer: ");
    if (computer.power == ON) display.println("Off");
    else display.println("On");
        
    display.print("Receiver: ");
    if (receiver.power == ON) display.print("Off");
    else display.print("On");
    display.print(" + ");
    display.println(receiver.input);    
    
    display.print("Television: ");
    if (tv.power == ON) display.print("Off");
    else display.print("On");
    display.print(" + ");
    display.println(tv.input);

    display.print("Backlight: ");
    display.print(tv.backlight);
    display.println("/20");
    
    display.print("Brightness: ");
    display.print(tv.brightness);
    display.println("%");
    
    display.display();
}


/************************************************* 
Particle Cloud Functions
*************************************************/

int setMode(String mode) {
    
    /*
    mode.equals("on") {
        systemMode = "it worked!";
    } else if mode.equals("on") {
    
    
    modez = static_cast<SystemModez>(mode.toInt()); // If mode was passed in as type int
    
    switch (modez) {
        case off        : systemMode = "xOff";  break;
        case on         : systemMode = "xOn";  break;
        case night      : systemMode = "xNight";  break;
        case dark       : systemMode = "xDark";  break;
        case stealth    : systemMode = "xStealth";  break;
        default         : systemMode = "xError!";  return 0;
    }
    
    //systemMode = "modez!";
    //computer.powerOff();
    //receiver.powerOff();
    //tv.powerOff();
    //receiver.setInputHDMI(1);
    //tv.setInputHDMI(1);
    //tv.setBacklight(0x20);
    return 1;
    */
}

int setModeOff(String unused) {
    systemMode = "Off";
    computer.powerOff();
    receiver.powerOff();
    tv.powerOff();
    
    receiver.setInputHDMI(1);
    //tv.setInputHDMI(1);
    //tv.setBacklight(0x20);
    return 1;
}

int setModeOn(String unused) {
    
    systemMode = "On";
    computer.powerOn();
    receiver.powerOn();
    tv.powerOn();
    
    receiver.setInputHDMI(1);
    tv.setInputPC();
    tv.setBacklight(0x20);
    
    return 1;
}

int setModeNight(String unused) {
    systemMode = "Night Mode";
    computer.powerOn();
    receiver.powerOn();
    tv.powerOn();
    
    receiver.setInputHDMI(1);
    tv.setInputHDMI(1);
    tv.setBacklight(0x07);
    return 1;
}

int setModeDark(String unused) {
    systemMode = "Dark Mode";
    computer.powerOn();
    receiver.powerOn();
    tv.powerOn();
    
    receiver.setInputHDMI(1);
    tv.setInputHDMI(1);
    tv.setBacklight(0x00);
    return 1;
}

int setModeStealth(String unused) {
    systemMode = "Stealth Mode";
    computer.powerOn();
    receiver.powerOff();
    tv.powerOff();
    
    //receiver.setInputHDMI(1);
    //tv.setInputHDMI(1);
    //tv.setBacklight(0x20);
    return 1;
}

int setModeMusic(String unused) {
    systemMode = "Music Mode";
    computer.powerOff();
    receiver.powerOn();
    tv.powerOff();
    
    receiver.setInputHDMI(2);
    //tv.setInputHDMI(1);
    //tv.setBacklight(0x20);
    return 1;
}

int setBacklight(String percent) {
    byte percentByte = percent.toInt();
    tv.setBacklight(percentByte);
    return 1;
}

int setBrightness(String percent) {
    byte percentByte = percent.toInt();
    tv.setBrightness(percentByte);
    return 1;
}


/************************************************* 
Interrupt Service Routines
*************************************************/

void PCPowerDetectISR() {
    if (digitalRead(PC_POWER_DETECT) == LOW) {
        computer.power = ON;      // If the pin is low, the PC is on
    }
    else {
        computer.power = OFF;
    }
}