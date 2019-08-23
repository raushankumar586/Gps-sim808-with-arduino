#include <string.h>
#include "handle_gps.h"

HandleGps gps = HandleGps();
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);
  Serial.println("Setup Complete!");
  while (!gps.Init()){
    delay(1000);
    Serial.println("sim com device pair failed...");
  }
  Serial.println("init success!");
  if(gps.Attach())
  Serial.println("gps attached Complete!");
  else
  Serial.println("gps attached failed");


}

void loop()
{
  if(gps.GetData()){
    Serial.println("got data");

  }
  else {
    Serial.println("not  data");

  }

  
}

