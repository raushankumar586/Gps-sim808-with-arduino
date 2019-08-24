#ifndef __printer_H__
#define __printer_H__
#include <Arduino.h>
#include <string.h>


class printer
{
private:
    /* data */
    bool debug = true;
public:
    printer(/* args */);
    ~printer();
    void debugPrint(String);
    void debugPrintln(String);
    void printMsz(String);
};








#endif
