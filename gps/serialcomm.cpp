

#include "serialcomm.h"
#include <Arduino.h>

serialcomm::serialcomm(/* args */)
{
}

serialcomm::~serialcomm()
{
}

void serialcomm::Setup(){
  Serial.begin(BAUDRATE);
  Serial1.begin(BAUDRATE);
  delay(1000); // First time only : will see later
}


bool serialcomm::checkCmd(const char *cmd, const char *res, unsigned int timeout)
{
    if (SendCmd(cmd, timeout))
    {
        return CheckRes(res, timeout);  
    }
}

bool serialcomm::SendCmd(const char *cmd, unsigned int timeout)
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

bool serialcomm::CheckRes(const char *res, unsigned int timeout)
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
