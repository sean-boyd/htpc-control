# HTPC Control

This control board connects my HTPC (Home Theatre Personal Computer), TV, and home theatre receiver to the internet. I can use my keyboard to wake up my computer with the keyboard and it will automatically turn on my receiver and TV, with everything set to the correct inputs and settings. I can also put the system into other modes (PC only for remote access, PC+receiver for music, etc) and change settings using Google Assistant commands.

The PCB is designed with the mounting pattern of a 2.5” HDD so that it could be mounted into a PCI-slot drive mount with a rear-mounted external antenna.

I leveraged the Particle Cloud and reverse-engineered the Samsung Ex-Link protocol and Yamaha AV Controller command structure.

## Hardware

The Particle Photon can detect if the PC is on or off, and can turn it on or off. The Photon also communicates via RS-232 with the Ex-Link connector on the Samsung TV. The Photon can read data and send commands to the Yamaha receiver. In addition, there is an optional OLED display which displays the state and settings of all the components of the system.

The components of the system are 
* Custom-built PC with ASUS Motherboard
* Samsung UN46EH5000 TV
* Yamaha RX-V575 AV Receiver

## Built With

* [Particle](https://www.particle.io/) - Hardware and cloud IoT platform