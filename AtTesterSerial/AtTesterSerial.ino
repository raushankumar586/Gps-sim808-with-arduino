char* turnOnGps = "AT+CGNSPWR=1\r\n";
char* getGpsData = "AT+CGNSINF\r\n";



void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);
}
 
void loop() {
    if(Serial1.available()){
      Serial.write(Serial1.read());
    }
    if(Serial.available()){    
      Serial1.write(Serial.read());
    }
} 
