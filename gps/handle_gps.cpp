#include "handle_gps.h"

bool HandleGps::checkCmd(const char *cmd, const char *res, unsigned int timeout)
{
    if (SendCmd(cmd, timeout))
    {
        return CheckRes(res, timeout);
    }
}

bool HandleGps::SendCmd(const char *cmd, unsigned int timeout)
{
    int i = 0;
    unsigned long currTime = millis();
    while (cmd[i] != NULL)
    {
        if ((unsigned long)(millis() - currTime) > timeout)
        {
            return false;
        }
        Serial1.write(cmd[i++]);
    }
    Serial1.flush();
    return true;
}

bool HandleGps::CheckRes(const char *res, unsigned int timeout)
{ // will work later for internal timeout

    unsigned long currTime = millis();
    byte checklen = 0;
    while (1)
    {
        if (Serial1.available() > 0)
        {
            char ch = Serial1.read();
            checklen = (ch == res[checklen]) ? checklen + 1 : ZERO;
            if (checklen == strlen(res))
            {
                break;
            }
        }
        if ((unsigned long)(millis() - currTime) > timeout)
        {
            return false;
        }
    }
    return true; // check out flushing read buffer later
}

bool HandleGps::Init()
{
    if (!checkCmd("AT\r\n", "OK\r\n"))
    {
        return false;
    }
    return true;
}

bool HandleGps::Attach()
{
    if (!checkCmd("AT+CGNSPWR=1\r\n", "OK\r\n"))
    {
        return false;
    }
    if (!checkCmd("AT+CGNSTST=1\r\n", "OK\r\n"))
    {
        return false;
    }

    return true;
}
bool HandleGps::Detach()
{
    if (!checkCmd("AT+CGNSPWR=0\r\n", "OK\r\n"))
    {
        return false;
    }
    return true;
}

void HandleGps::GetData()
{
    // need to write
}
