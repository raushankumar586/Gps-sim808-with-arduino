#include <string.h>
#include "printer.h"
#include "handle_gps.h"
#define BAUDRATE 9600

HandleGps gps = HandleGps();
printer sp = printer(); // serial printer
void serialSetup(){
  Serial.begin(BAUDRATE);
  Serial1.begin(BAUDRATE);
  delay(1000);
  sp.printMsz("Setup Complete!");
}

void setup()
{
  serialSetup();
  gps.Setup();
  
}

void loop()
{
  gps.Print();
}

