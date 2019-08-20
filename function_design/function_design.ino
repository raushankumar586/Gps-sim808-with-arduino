#include <string.h>
#include "handle_gps.h"

HandleGps gps = HandleGps();
void setup()
{
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);
  Serial.println("Setup Complete!");
}

void loop()
{
  

  
}

