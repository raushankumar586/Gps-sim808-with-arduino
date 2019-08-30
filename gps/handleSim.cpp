#include "handleSim.h"
#include "serialcomm.h"
#include "printer.h"

extern serialcomm serialCom;
extern printer sp;

handleSim::handleSim(/* args */)
{
}

handleSim::~handleSim()
{
}

bool handleSim::Init()
{
    if (!serialCom.checkCmd("AT\r\n", "OK\r\n"))
    {
        return false;
    }
    sp.debugPrintln("AT pass");
    if (!serialCom.checkCmd("AT+CFUN=1\r\n", "OK\r\n"))
    {
        return false;
    }
    sp.debugPrintln("CFUN pass");

    if (!serialCom.checkCmd("AT+CPIN?\r\n", "+CPIN: READY\r\n"))
    {
        return false;
    }
    sp.debugPrintln("CPIN pass");

    return true;
}

bool handleSim::SendSms()
{
    if (!serialCom.checkCmd("AT+CMGF=1\r\n", "OK\r\n"))
    { // Set message mode to ASCII
        return false;
    }
    delay(500);
    // Serial1.flush();

    if (!serialCom.SendCmd("AT+CMGS=\""))
    {
        return false;
    }
    sp.debugPrintln("msz format sent ");

    if (!serialCom.SendCmd("+918969120487"))
    {
        return false;
    }
    sp.debugPrintln("phone no sent ");

    if (!serialCom.checkCmd("\"\r\n", ">"))
    {
        return false;
    }
    sp.debugPrintln("Started msz writing... ");

    delay(1000);
    serialCom.SendCmd("Hello Raushan! I am cooper2.0");
    sp.debugPrintln("my message ");
    delay(500);
    terminaitionMsz();
    sp.debugPrintln("msz writing complete ");
    if (!serialCom.CheckRes("OK\r\n"))
    {
        return false;
    }
    sp.debugPrintln("msz sent ");

    return true;
}

void handleSim::terminaitionMsz()
{
    Serial1.write((char)26);
}

bool handleSim::connectToNetwork(){
    if(!checkReg()){
        return false;
    }
    Serial.println("registration done");
    
}

bool handleSim::checkReg()
{
    if (!serialCom.checkCmd("AT+CREG?\r\n", "+CREG: 0,1\r\n"))
    {
        return false;
    }
    return true;
}

// bool handleSim::checkGprs()
// {
//     if (!serialCom.checkCmd("AT+CGATT?\r\n", "+CGATT: 1\r\n"))
//     {
//         return false;
//     }
// }

// bool handleSim::resetIPSession()
// {
//     if (!serialCom.checkCmd("AT+CIPSHUT\r\n", "SHUT OK\r\n"))
//     {
//         return false;
//     }
// }
// bool handleSim::checkIPStateInitialization()
// {
//     if (!serialCom.checkCmd("AT+CIPSTATUS\r\n", "OK\r\n"))
//     {
//         return false;
//     }
// }

// bool handleSim::setConnectionMode(byte mode)
// {
//     //singal connection mode
//     if (!serialCom.checkCmd("AT+CIPMUX=0\r\n", "OK\r\n"))
//     {
//         return false;
//     }
// }

// bool handleSim::setApn(char *apn, char *username, char *password)
// {

//     // AT + CSTT = “APN”, “UNAME”, “PWD” OK
// }

// bool handleSim::attachWirelessConnection()
// {
//     if (!serialCom.checkCmd("AT+CIICR\r\n", "OK\r\n"))
//     {
//         return false;
//     }
// }

// char *handleSim::getIpAddress()
// {
//     // AT + CIFSR
// }

// bool handleSim::connectTcp(char *ip, char *port)
// {
//     // CONNECT OK
// }

// void handleSim::sendTCPData()
// {
// }

// bool handleSim::tcpDisconnect()
// {
//     //AT+CIPSHUT
//     if (!serialCom.checkCmd("AT+CIPSHUT\r\n", "SHUT OK\r\n"))
//     {
//         return false;
//     }
// }
