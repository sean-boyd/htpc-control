#pragma once
#include "application.h"

class Receiver {
    
    public:
        Receiver();
        void powerOff();
        void powerOn();
        void setInputHDMI(int);       
        bool power;
        String input;
        
    private:
        const bool OFF = false;
        const bool ON = true;
        
        const byte ReceiverIP[4] = {192, 168, 0, 102};
        const int EthernetFlushDelayInMS = 500;     // 1000ms is known to work correctly
        
        const String requestPrefix = "<?xml version=\"1.0\" encoding=\"utf-8\"?><YAMAHA_AV cmd=\"PUT\"><Main_Zone>";
        const String requestSuffix = "</Main_Zone></YAMAHA_AV>";
        
        const String requestPowerOff = "<Power_Control><Power>Standby</Power></Power_Control>";
        const String requestPowerOn = "<Power_Control><Power>On</Power></Power_Control>";
        
        const String requestHDMI1 = "<Input><Input_Sel>HDMI1</Input_Sel></Input>";
        const String requestHDMI2 = "<Input><Input_Sel>HDMI2</Input_Sel></Input>";
        const String requestHDMI3 = "<Input><Input_Sel>HDMI3</Input_Sel></Input>";
        const String requestHDMI4 = "<Input><Input_Sel>HDMI4</Input_Sel></Input>";
        const String requestHDMI5 = "<Input><Input_Sel>HDMI5</Input_Sel></Input>";
        
        void sendMessage(String);
};

/*
Example Requests:

<?xml version="1.0" encoding="utf-8"?><YAMAHA_AV cmd="PUT"><Main_Zone><Volume><Mute>Off</Mute></Volume></Main_Zone></YAMAHA_AV>
<?xml version="1.0" encoding="utf-8"?><YAMAHA_AV cmd="PUT"><Main_Zone><Volume><Mute>On</Mute></Volume></Main_Zone></YAMAHA_AV>
<?xml version="1.0" encoding="utf-8"?><YAMAHA_AV cmd="PUT"><Main_Zone><Volume><Lvl><Val>-150</Val><Exp>1</Exp><Unit>dB</Unit></Lvl></Volume></Main_Zone></YAMAHA_AV>
<?xml version="1.0" encoding="utf-8"?><YAMAHA_AV cmd="PUT"><Main_Zone><Volume><Lvl><Val>-145</Val><Exp>1</Exp><Unit>dB</Unit></Lvl></Volume></Main_Zone></YAMAHA_AV>


Sample Request:

<?xml version="1.0" encoding="utf-8"?><YAMAHA_AV cmd="GET"><Main_Zone><Basic_Status>GetParam</Basic_Status></Main_Zone></YAMAHA_AV>


Sample Response:

<YAMAHA_AV rsp="GET" RC="0">
    <Main_Zone>
        <Basic_Status>
            <Power_Control>
                <Power>On</Power>
                <Sleep>Off</Sleep>
            </Power_Control>
            <Volume>
                <Lvl>
                    <Val>-150</Val>
                    <Exp>1</Exp>
                    <Unit>dB</Unit>
                </Lvl>
                <Mute>Off</Mute>
                <Zone_B>
                    <Feature_Availability>Not Ready</Feature_Availability>
                    <Interlock>On</Interlock>
                    <Lvl>
                        <Val>-150</Val>
                        <Exp>1</Exp>
                        <Unit>dB</Unit>
                    </Lvl>
                    <Mute>Off</Mute>
                </Zone_B>
            </Volume>
            <Input>
                <Input_Sel>HDMI1</Input_Sel>
                <Input_Sel_Item_Info>
                    <Param>HDMI1</Param>
                    <RW>RW</RW>
                    <Title>  HTPC   </Title>
                    <Icon>
                        <On>/YamahaRemoteControl/Icons/icon004.png</On>
                        <Off></Off>
                    </Icon>
                    <Src_Name></Src_Name>
                    <Src_Number>1</Src_Number>
                </Input_Sel_Item_Info>
            </Input>
            <Surround>
                <Program_Sel>
                    <Current>
                        <Straight>Off</Straight>
                        <Enhancer>On</Enhancer>
                        <Sound_Program>Surround Decoder</Sound_Program>
                    </Current>
                </Program_Sel>
                <_3D_Cinema_DSP>Off</_3D_Cinema_DSP>
            </Surround>
            <Sound_Video>
                <Tone>
                    <Bass>
                        <Val>0</Val>
                        <Exp>1</Exp>
                        <Unit>dB</Unit>
                    </Bass>
                    <Treble>
                        <Val>0</Val>
                        <Exp>1</Exp>
                        <Unit>dB</Unit>
                    </Treble>
                </Tone>
                <Direct>
                    <Mode>Off</Mode>
                </Direct>
                <HDMI>
                    <Standby_Through_Info>On</Standby_Through_Info>
                    <Output>
                        <OUT_1>On</OUT_1>
                    </Output>
                </HDMI>
                <Adaptive_DRC>Auto</Adaptive_DRC>
            </Sound_Video>
            <Speaker_Preout>
                <Speaker_AB>
                    <Speaker_A>On</Speaker_A>
                    <Speaker_B>Off</Speaker_B>
                </Speaker_AB>
            </Speaker_Preout>
        </Basic_Status>
    </Main_Zone>
</YAMAHA_AV>

*/