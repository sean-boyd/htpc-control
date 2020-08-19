#include "receiver.h"

TCPClient client;       // Initialize the TCP Client library


/************************************************* 
Constructor
*************************************************/
Receiver::Receiver() {
    
    //serverConnection = false;
    power = OFF;
    input = "?";
}


/************************************************* 
Send Message
*************************************************/
void Receiver::sendMessage(String requestBody) {
    client.connect(ReceiverIP, 80);
    if (client.connected()) {
        client.println("POST /YamahaRemoteControl/ctrl HTTP/1.1");
        client.println();
        client.print(requestPrefix);
        client.print(requestBody);  
        client.println(requestSuffix);
        delay(EthernetFlushDelayInMS);
        client.flush();
        client.stop();
    }
}  


/************************************************* 
Power Off the Receiver
*************************************************/  
void Receiver::powerOff() {
    
    sendMessage(requestPowerOff);
    this->power = OFF;
}


/************************************************* 
Power On the Receiver
*************************************************/
void Receiver::powerOn() {
    
    sendMessage(requestPowerOn);
    this->power = ON;
}


/************************************************* 
Set Receiver Input to HDMI1, HDMI2, or HDMI3
*************************************************/
void Receiver::setInputHDMI(int input) {
    
    if (input == 1) {
        sendMessage(requestHDMI1);
    }
    else if (input == 2) {
        sendMessage(requestHDMI2);
    }
    else if (input == 3) {
        sendMessage(requestHDMI3);
    }
    else if (input == 4) {
        sendMessage(requestHDMI4);
    }
    else if (input == 5) {
        sendMessage(requestHDMI5);
    }
    this->input = "HDMI" + String(input);
}