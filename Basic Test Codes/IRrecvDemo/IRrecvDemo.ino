/*
   IRremote: IRrecvDemo - demonstrates receiving IR codes with IRrecv
   An IR detector/demodulator must be connected to the input RECV_PIN.
   Version 0.1 July, 2009
   Copyright 2009 Ken Shirriff
   http://arcfn.com
*/

#include <IRremote.h>

int RECV_PIN = 17;

IRrecv irrecv(RECV_PIN);

decode_results results;

void setup()
{
  Serial.begin(9600);
  irrecv.enableIRIn(); // Start the receiver
  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
}

void loop() {
  if (irrecv.decode(&results)) {
    if (results.value == 0xa80) {
      digitalWrite(5, HIGH);
      digitalWrite(12, LOW);
      digitalWrite(6, HIGH);
      digitalWrite(7, LOW);
    }
    else if (results.value == 0xa90){
      digitalWrite(5, LOW);
      digitalWrite(12, LOW);
      digitalWrite(6, LOW);
      digitalWrite(7, LOW);
    }
    Serial.println(results.value, HEX);
    irrecv.resume(); // Receive the next value
  }
}
