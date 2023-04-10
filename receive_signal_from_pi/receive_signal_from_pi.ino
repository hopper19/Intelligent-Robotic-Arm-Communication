/*
Program: Receive Integers From Raspberry Pi
File: receive_ints_from_raspberrypi.ino
Description: Receive integers from a Raspberry Pi
Author: Cuong Nguyen
*/
 
// Initialize the integer variables
int signal = 0;
 
void setup(){
  pinMode(LED_BUILTIN, OUTPUT);
  // Set the baud rate  
  Serial.begin(115200);   
}
 
void loop(){
 
  if(Serial.available() > 1) {
    // signal = Serial.parseInt();
 
    digitalWrite(LED_BUILTIN, HIGH);

    delay(500);

    digitalWrite(LED_BUILTIN, LOW);

    delay(500);
    // Serial.flush();
    signal = 0;
  }
}