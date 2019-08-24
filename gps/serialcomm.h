#ifndef __SERIALCOMM_H__
#define __SERIALCOMM_H__
#define TIMEOUT 4000 // 4 sec
#define ZERO 0
#define BAUDRATE 9600


class serialcomm
{
private:
    /* data */
public:
    serialcomm(/* args */);
    ~serialcomm();
    void Setup();
    bool checkCmd(const char *cmd, const char *res, unsigned int timeout = TIMEOUT);
    bool SendCmd(const char *cmd, unsigned int timeout = TIMEOUT);
    bool CheckRes(const char *res, unsigned int timeout = TIMEOUT);
};




#endif