#ifndef __HANDLESIM_H__
#define __HANDLESIM_H__

class handleSim
{
private:
    /* data */
public:
    handleSim(/* args */);
    ~handleSim();
    bool Init();
    bool SendSms();
    void terminaitionMsz();
    bool checkReg();
    bool connectToNetwork();
    
};



#endif