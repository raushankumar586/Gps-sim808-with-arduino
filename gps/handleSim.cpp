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
}