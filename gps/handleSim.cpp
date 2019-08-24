#include "handleSim.h"
#include "serialcomm.h"

extern serialcomm serialCom;


handleSim::handleSim(/* args */)
{
}

handleSim::~handleSim()
{
}

void handleSim::init()
{
    if (serialCom.checkCmd("AT\r\n", "OK\r\n"))
    {
        return true;
    }
    if (serialCom.checkCmd("AT+CFUN=1\r\n", "OK\r\n"))
    {
        return true;
    }
    if (serialCom.checkCmd("AT\r\n", "OK\r\n"))
    {
        return true;
    }

    return false;
}