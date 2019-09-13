#include "handle_gps.h"
#include "printer.h"
#include "serialcomm.h"

extern printer sp;
serialcomm serialCom = serialcomm();

bool HandleGps::Init()
{
    if (serialCom.checkCmd("AT\r\n", "OK\r\n"))
    {
        return true;
    }
    return false;
}

bool HandleGps::Attach()
{
    if (!serialCom.checkCmd("AT+CGNSPWR=1\r\n", "OK\r\n"))
    {
        return false;
    }
    if (!serialCom.checkCmd("AT+CGNSTST=1\r\n", "OK\r\n"))
    {
        return false;
    }

    return true;
}
bool HandleGps::Detach()
{
    if (!serialCom.checkCmd("AT+CGNSPWR=0\r\n", "OK\r\n"))
    {
        return false;
    }
    return true;
}

bool HandleGps::GetData()
{
    if (!LoadData())
        return false; // getting data into buffer

    // sp.debugPrintln("\n\n\n---------------reading done-----------");
    // sp.debugPrintln("");

    if (!IsValidData(bufferGps))
        return false;

    // sp.debugPrintln("\n\n\n---------------validation done-----------");
    if (!parseGpgllData(bufferGps))
        return false;

    // sp.debugPrintln("\n\n\n---------------parsing done-----------");
    return true;
}
//char *receivedStack="$Gpgga,165445.000,A,3110.8635,N,12133.4627,E,0.58,70.26,220916,,,A*57";

bool HandleGps::LoadData()
{
    char readChar;
    byte lastTwoBytes;
    bool dataEnd = false;

    while (Serial1.available())
    {
        readChar = Serial1.read();
        // debuPrint("data reading--");
        delay(2); // will solve later;

        if (dataEnd) // will look this part later
        {
            if (lastTwoBytes--)
            {
                bufferGps[bufferIndex] = readChar;
            }
            else
            {
                dataEnd = false;
                bufferGps[bufferIndex] = '\0';
                // sp.debugPrintln("\n------------data complete------------");
                return true;
            }
        }
        else
        {
            switch (readChar)
            {
            case '$':
                bufferIndex = 0;
                bufferGps[bufferIndex++] = readChar;

                break;
            case '*':
                lastTwoBytes = 2;
                bufferGps[bufferIndex] = readChar;
                dataEnd = true;
                break;
            default:
                if (bufferIndex < MAX_GPS_BUFFER_SIZE)
                {
                    bufferGps[bufferIndex++] = readChar;
                    // sp.debugPrintln("index:" + String(bufferIndex));
                }
                break;
            }
            if (!dataEnd)
            {
                return false;
            }
        }
        if (!dataEnd)
        {
            return false;
        }
    }
    return false; // return asap when serial not available
}

//char *receivedStack="$Gpgga,165445.000,A,3110.8635,N,12133.4627,E,0.58,70.26,220916,,,A*57";
bool HandleGps::IsValidData(char *data)
{
    // Serial.print(data);
    if (!strstr(data, GpggaToken) == NULL)
    {
        // if (data[18] == "A")  // will do more validation later
        // {
        //     return true;
        // }
        // else
        // {
        //     return false;
        // }
        return true;
    }
    else
    {
        bufferIndex = 0;
        // sp.debugPrintln("token mismatch--");
        return false;
    }
}
bool HandleGps::parseGprmcData(char *data)
{
    char *token = strstr(data, ",");
    if (!token)
        return false;
    char *time = strstr(NULL, ",");
    if (!time)
    {
        return false;
    }
    else
    {
        // will parse the time data later
    }
    char *lat = strstr(NULL, ",");
    if (!lat)
    {
        return false;
    }
    else
    {
    }

    char *latdir = strstr(NULL, ",");
    if (!latdir)
    {
        return false;
    }
    else
    {
    }
    char *lon = strstr(NULL, ",");
    if (!lon)
    {
        return false;
    }
    else
    {
    }
    char *londir = strstr(NULL, ",");
    if (!londir)
    {
        return false;
    }
    else
    {
    }
    return true;
}

bool HandleGps::parseGpgllData(char *data)
{
    char *token = strtok(data, ",");
    if (!token)
        return false;

    char *lat = strtok(NULL, ",");
    if (!lat)
        return false;
    else
        GpsData.lat = atof(lat);

    char *latdir = strtok(NULL, ",");
    if (!latdir)
        return false;
    else
    {
        // GpsData.latdir = latdir;
    }

    char *lon = strtok(NULL, ",");
    if (!lon)
        return false;
    else
        GpsData.lon = atof(lon);
    char *londir = strtok(NULL, ",");
    if (!londir)
        return false;
    else
    {
        // GpsData.londir = londir;
    }

    return true;
}

void HandleGps::Setup()
{
    while (!Init())
    {
        delay(1000);
        sp.printMsz("sim com device pair failed...");
    }
    sp.printMsz("init success!");

    if (Attach())
    {
        sp.printMsz("gps started");
    }
    else
    {
        sp.printMsz("gps not started");
    }
}

void HandleGps::Print()
{
    if (GetData())
    {
        String msz = "lattitude : " + String(GpsData.lat) + "longitude " + String(GpsData.lon);
        sp.debugPrintln(msz);
    }
}

String HandleGps::Loop()
{
    GetData();
    String msz = "lattitude : " + String(GpsData.lat) + "longitude " + String(GpsData.lon);
    return msz;
}
