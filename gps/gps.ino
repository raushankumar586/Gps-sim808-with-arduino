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
    Serial.println("sim com device pair failed...");
    sp.printMsz("sim com device pair failed...");
  }
  Serial.println("init success!");
  if(gps.Attach())
  Serial.println("gps attached Complete!");
  else
  Serial.println("gps attached failed");
  sp.printMsz("init success!");

    sp.printMsz("gps started");
    sp.printMsz("gps not started");

}

void loop()
{
  if(gps.GetData()){
    Serial.println("got data");
   
   String msz = "lattitude : " + String(gps.GpsData.lat)+ "longitude " + String(gps.GpsData.lon) ;
   sp.debugPrintln(msz);
  }
  else {
    Serial.println("not  data");

  }

  
}

