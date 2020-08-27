#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

RF24 radio(7, 8);

const byte txAddr[6] = "11801";
const byte rxAddr[6] = "11800";
char text[] = "Hi";
char rxText[] = "";

/*
   NRF Connections with Arduino Mega:
   CE - 7
   CSN - 8
   M1/MISO - 50
   M0/MOSI - 51
   SCK - 52
*/

int state = 0;
uint8_t txMessage;
uint8_t rxMessage;
bool correctMessage;
bool sent = false;

void setup() {
  pinMode(2, INPUT);
  radio.begin();
  Serial.begin(9600);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, txAddr);
  radio.openWritingPipe(rxAddr);
  radio.stopListening();

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT); //High forward
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT); // High towards wall

  pinMode(2, INPUT);        //Sensor
  pinMode(3, INPUT_PULLUP); //Towards wall
  pinMode(4, INPUT_PULLUP);

  while(digitalRead(4)) {
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
  }
}
void loop() {

  bool sensor = digitalRead(2);

  if(sensor && state == 2) {
    state = 3;
  }


  Serial.println(state);
  switch(state) {
    case 0:
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);

      digitalWrite(11,LOW);
      digitalWrite(12,LOW);
      correctMessage = false;
      radio.startListening();
      while(!correctMessage) {
        Serial.println("Waiting for message");
        while (!radio.available());
        radio.read(&rxMessage, sizeof(rxMessage));
        radio.stopListening();
        Serial.println("Received " + rxMessage);
        if(rxMessage == 0xaa) {
          Serial.println("Received 0xaa");
          correctMessage = true;
          state = 1;
        }
      }
      break;
    case 1:
      digitalWrite(9,LOW);
      digitalWrite(10,HIGH);

      digitalWrite(11,LOW);
      digitalWrite(12,LOW);
      
      
      state = 2;
      break;

    case 2:
      txMessage = 0xff;
      radio.write(&txMessage, sizeof(txMessage));
      break;
      
    case 3:
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);

      digitalWrite(11,LOW);
      digitalWrite(12,LOW);
      
        
      state = 4;
      break;
      
    case 4:
    radio.stopListening();
      txMessage = 0xaf;
      radio.write(&txMessage, sizeof(txMessage));
      break;
  }


//  bool sent = false;
//  if (digitalRead(2)) {
//    sent = radio.write(&text, sizeof(text));
//    if (sent) {
//      //motor start
//      Serial.println("Motor Start");
//      radio.startListening();
//      while (!radio.available());
//      //motor stop
//      radio.read(&rxText, sizeof(rxText));
//      radio.stopListening();
//      if (strcmp(rxText, "AA"))
//        Serial.println("Motor A Stop");
//      else if (strcmp(rxText, "BB"))
//        Serial.println("Motor B Stop");
//      else if (strcmp(rxText, "CC"))
//        Serial.println("Motor C Stop");
//
//    }
//  }

  //    if(radio.available()) {
  //      radio.stopListening();
  //      Serial.println("Transmitted");
  //    }
}
