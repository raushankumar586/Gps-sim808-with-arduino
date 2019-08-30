#include <string.h>
#include "printer.h"
#include "handle_gps.h"
#include "serialcomm.h"
#include "handleSim.h"


extern serialcomm serialCom;
HandleGps gps = HandleGps();
printer sp = printer(); // serial printer
handleSim sim = handleSim();

void setup()
{
  serialCom.Setup();
  sp.printMsz("Serial Setup Complete!");
  // gps.Setup();
  sim.Init();
  // sim.SendSms();
  sim.connectToNetwork();

  
}

void loop()
{
  // gps.Print();
}

