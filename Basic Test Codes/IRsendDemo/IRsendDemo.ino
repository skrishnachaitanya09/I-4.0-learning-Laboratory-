/*
   IRremote: IRsendDemo - demonstrates sending IR codes with IRsend
   An IR LED must be connected to Arduino PWM pin 3.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include <IRremote.h>


char input = '0';
IRsend irsend;

void setup()
{
  Serial.begin(9600);
}

void loop() {
  if(Serial.available()) {
    input = Serial.read();
  }
  else {
    input = '0';
  }
  if (input == 'a') {
    Serial.println("Sending message");
    irsend.sendSony(0xa80, 12);
    delay(40);
  }
  else if (input == 'b') {
    Serial.println("Sending message");
    irsend.sendSony(0xa90, 12);
  }
}
