#ifndef __HANDLESIM_H__
#define __HANDLESIM_H__
#include<Arduino.h>
class handleSim
{
private:
    /* data */
public:
    handleSim(/* args */);
    ~handleSim();
    bool Init();
    bool SendSms();
    bool checkReg();
    bool connectToNetwork();
    bool checkGprs();
    bool resetIPSession();
    bool checkStatus();
    bool setConnectionMode(int );
    bool setApn(char* , char* , char* );
    bool attachWirelessConnection();
    bool getIpAddress();
    bool connectTcp(char*, char* );
    bool sendTCPData(char *data);
    bool tcpDisconnect();
};



#endif