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
  while (!gps.Init()){
    delay(1000);
    sp.printMsz("sim com device pair failed...");
  }
  sp.printMsz("init success!");

  if(gps.Attach()){
    sp.printMsz("gps started");
  }
  else{
    sp.printMsz("gps not started");

  }

}

void loop()
{
  if(gps.GetData()){
   
   String msz = "lattitude : " + String(gps.GpsData.lat)+ "longitude " + String(gps.GpsData.lon) ;
   sp.debugPrintln(msz);
  }
  else {

  }

  
}

