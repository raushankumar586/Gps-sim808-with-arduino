#include <string.h>
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
    serialCom.terminationMsz();
    sp.debugPrintln("msz writing complete ");
    if (!serialCom.CheckRes("OK\r\n"))
    {
        return false;
    }
    sp.debugPrintln("msz sent ");

    return true;
}


bool handleSim::connectToNetwork(){
    if(!checkReg()){
        return false;
    }
    Serial.println("registration done");

    if (!checkGprs())
    {
        return false;
    }
    Serial.println("Gprs done");
    delay(1000);
    if (!resetIPSession())
    {
        return false;
    }
    Serial.println("reset IP Session pass");
    
    if (!checkStatus())
    {
        return false;
    }
    Serial.println("check IP State Initialization pass");

    if (!setConnectionMode(0))  //single connection mode
    {
        return false;
    }
    Serial.println("set Connection Mode");

   if (!setApn("airtelgprs.com","",""))  //single connection mode
    {
        return false;
    }
    Serial.println("set Apn done");

    if (!attachWirelessConnection())  //single connection mode
    {
        return false;
    }
    Serial.println("attach Wireless Connection");
    
    // getIpAddress();

    if (!connectTcp("13.127.50.145", "80"))  //single connection mode
    {
        return false;
    }
    String data ;
    Serial.println(" connectTcp "); 

    
}

bool handleSim::checkReg()
{
    if (!serialCom.checkCmd("AT+CREG?\r\n", "+CREG: 0,1\r\n"))
    {
        return false;
    }
    return true;
}

bool handleSim::checkGprs()
{
    if (!serialCom.checkCmd("AT+CGATT?\r\n", "+CGATT: 1\r\n"))
    {
        return false;
    }
    return true;
}

bool handleSim::resetIPSession()
{
    if (!serialCom.checkCmd("AT+CIPSHUT\r\n", "SHUT OK\r\n")) 
    {
        return false;
        
    }
    return true;
}

bool handleSim::checkStatus()
{
    if (!serialCom.checkCmd("AT+CIPSTATUS\r\n", "OK\r\n"))
    {
        return false;
    }
    // sim808_read_buffer(resp, sizeof(resp), DEFAULT_TIMEOUT);
    // if (NULL != strstr(resp, "CONNECTED"))
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }
    return true;
}

bool handleSim::setConnectionMode(int mode)
{
    //singal connection mode
    if (!serialCom.checkCmd("AT+CIPMUX=0\r\n", "OK\r\n"))
    {
        return false;
    }
    // sim808_read_buffer(resp, sizeof(resp), DEFAULT_TIMEOUT);
    // if (NULL != strstr(resp, "CONNECTED"))
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }
    return true;
}

bool handleSim::setApn(char *apn, char *username, char *password)
{
    if (!serialCom.checkCmd("AT+CSTT=\"airtelgprs.com\"\r\n", "OK\r\n"))
    {
        return false;
    }
    // sim808_read_buffer(resp, sizeof(resp), DEFAULT_TIMEOUT);
    // if (NULL != strstr(resp, "CONNECTED"))
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }
    return true;
}


bool handleSim::attachWirelessConnection()
{
    if (!serialCom.checkCmd("AT+CIICR\r\n", "OK\r\n"))
    {
        return false;
    }
    // sim808_read_buffer(resp, sizeof(resp), DEFAULT_TIMEOUT);
    // if (NULL != strstr(resp, "CONNECTED"))
    // {
    //     return true;
    // }
    // else
    // {
    //     return false;
    // }
    return true;
}

bool handleSim::getIpAddress()
{
    serialCom.SendCmd("AT+CIFSR\r\n"); // if ip is not checked tcp connection req throws error
    return true;
}


bool handleSim::connectTcp(char* HOSTIP, char* port)
{       
    serialCom.SendCmd("AT+CIFSR\r\n");   // if 
    delay(100);
    int size = 1000;
    char record[size];
    serialCom.checkDelayedRes(record, size, 3000);
    Serial.println("record " + String(record));
    serialCom.clearBuffer(record,size);



    if(!serialCom.SendCmd("AT+CIPSTART=\"TCP\",\""))
        return false;
    if(!serialCom.SendCmd(HOSTIP))
        return false;
    if(!serialCom.SendCmd("\",\""))
        return false;
    if(!serialCom.SendCmd(port))
        return false;
    if(!serialCom.SendCmd("\""))
        return false;
    serialCom.SendCmd("\r\n");

    delay(3000);
    serialCom.checkDelayedRes(record, size, 3000);
    Serial.println("record tcp" + String(record));
    serialCom.clearBuffer(record,size);


    
    // later : tcp is connected without starting the server

}




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
