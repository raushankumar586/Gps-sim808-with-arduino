#include "printer.h"


printer::printer(/* args */)
{
}

printer::~printer()
{
}

void printer::debugPrint(String msz)
{
    if (debug)
    {
        Serial.print(msz);
    }
}
void printer::debugPrintln(String msz)
{
    if (debug)
    {
        Serial.println(msz);
    }
}
void printer::printMsz(String msz)
{
    Serial.println(msz);
}
