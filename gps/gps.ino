#include <string.h>
#include "printer.h"
#include "handle_gps.h"
#include "serialcomm.h"

HandleGps gps = HandleGps();
printer sp = printer(); // serial printer
extern serialcomm serialCom;

void setup()
{
  serialCom.Setup();
  sp.printMsz("Serial Setup Complete!");
  gps.Setup();
  
}

void loop()
{
  gps.Print();
}

