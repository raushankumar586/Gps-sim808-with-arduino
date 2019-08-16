char frame[200];
char latitude[15];
char longitude[15];
char altitude[6];
char date[16];
char time[7];
char satellites[3];
char speedOTG[10];
char course[10];
void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  Serial1.begin(9600);
  delay(1000);
  Serial.println("Setup Complete!");
  //  start_GPS();
  // get_GPS();

}

void loop() {
  sendATcommand( "AT+CGNSINF\r\n" , "OK");
  delay(2000);
}

int8_t sendATcommand(char* ATcommand, char* expected_answer) {
  uint8_t  answer = 0;
  char response[120];
  unsigned long previous;
  memset(response, '\0', 120);    // Initialice the string
  delay(100);
  while (Serial1.available() > 0) Serial1.read();   // Clean the input buffer
  if (ATcommand[0] != '\0')
  {
    Serial1.println(ATcommand);    // Send the AT command
  }
  int   x = 0;
  // this loop waits for the answer
  do {
    if (Serial1.available() != 0) {  // if there are data in the UART input buffer, reads it and checks for the asnwer
      response[x] = Serial1.read();
      Serial.print(response[x]);
      x++;
      if (strstr(response, expected_answer) != NULL)    // check if the desired answer (OK) is in the response of the module
      {
        answer = 1;
      }
    }
  } while (answer == 0);   // Waits for the asnwer with time out
  return answer;
}

int8_t start_GPS() {
  Serial.println("turning on gps...");
  sendATcommand("AT+CGNSPWR=1\r\n", "OK", 2000);
  Serial.println();
}
int8_t get_GPS() {

  int   counter = 0;
  int answer = 0;
  Serial.println("Gps data found :.....................");
  sendATcommand("AT+CGNSINF\r\n", "OK", 2000);
  memset(frame, '\0', 120); // Initialize the string
  do {
    if (Serial.available() != 0) {
      frame[counter] = Serial.read();
      counter++;
      // check if the desired answer is in the response of the module
      if (strstr(frame, "OK") != NULL)
      {
        answer = 1;
      }
    }
    // Waits for the asnwer with time out
  } while (answer == 0);   // Waits for the asnwer with time out
}

