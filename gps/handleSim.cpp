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

void handleSim::Init()
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
    terminationMsz();
    sp.debugPrintln("msz writing complete ");
    if(!serialCom.CheckRes("OK\r\n")){
        return false;
    }
    sp.debugPrintln("msz sent ");

    return true; 
}

void handleSim::terminationMsz(){
    Serial1.write((char)26);
}