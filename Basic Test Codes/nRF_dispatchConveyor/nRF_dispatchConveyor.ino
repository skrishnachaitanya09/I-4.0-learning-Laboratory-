#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
RF24 radio(7, 8);

const byte txAddr[6] = "11800";
const byte rxAddr[6] = "11801";
const char text[] = "Hi";
char rxText = 'f';

/*
 * NRF Connections with Arduino Mega:
 * CE - 7
 * CSN - 8
 * M1/MISO - 50
 * M0/MOSI - 51
 * SCK - 52
 */

int state = 0;
uint8_t txMessage;
uint8_t rxMessage;
bool correctMessage;
bool sent;

void setup(){
  pinMode(2,INPUT);
  radio.begin();
  Serial.begin(9600);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, txAddr);
  radio.openWritingPipe(rxAddr);
  radio.stopListening();

  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT); //High forward

  pinMode(2, INPUT);  //towards hibay
  pinMode(3, INPUT);  //towards dispatch
  
}  
void loop(){  
  bool startingSensor = digitalRead(2);
  bool endingSensor = digitalRead(3);

  if(startingSensor && state == 0) {
    state = 1;
  }
  else if(endingSensor && state == 1) {
    state = 2;
  }

  Serial.println(state);
  switch(state) {
    case 0:
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);
      break;

    case 1:
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      break;

    case 2:
      digitalWrite(9, LOW);
      digitalWrite(10, LOW);

      radio.stopListening();
      txMessage = 0xaa;
      Serial.println("Sending 0xaa");
      sent = radio.write(&txMessage, sizeof(txMessage));
      if(sent) {
        Serial.println("Sent 0xaa");
        state = 3;
      }
      break;

    case 3:
      radio.startListening();
      correctMessage = false;
      while(!correctMessage) {
        while(!radio.available());
        radio.read(&rxMessage, sizeof(rxMessage));
        Serial.print("Received ");
        Serial.println(rxMessage);
        if(rxMessage == 0xbb) {
          correctMessage = true;
          state = 4;
        }
      }
      break;

    case 4:
      digitalWrite(9, LOW);
      digitalWrite(10, HIGH);
      radio.stopListening();
      txMessage = 0xcc;
      Serial.println("Sending 0xcc");
      sent = radio.write(&txMessage, sizeof(txMessage));
      if(sent) {
        Serial.println("Sent 0xcc");
      }
      state = 5;
      break;

    case 5:
      radio.startListening();
      correctMessage = false;
      while(!correctMessage) {
        while(!radio.available());
        radio.read(&rxMessage, sizeof(rxMessage));
        Serial.print("Received ");
        Serial.println(rxMessage);
        if(rxMessage == 0xdd) {
          correctMessage = true;
          state = 0;
        }
      }
      break;
    
  }
}
