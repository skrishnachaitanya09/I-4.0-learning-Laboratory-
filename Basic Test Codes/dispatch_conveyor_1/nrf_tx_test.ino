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


  if(startingSensor) {
    state = 1;
  }
  else if(endingSensor) {
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
      radio.write(&txMessage, sizeof(txMessage));
      Serial.println("Sent 0xaa");
      state = 3;
      break;
    case 3:
      correctMessage = false;
      radio.startListening();
      while(!correctMessage) {
        while (!radio.available());
        radio.read(&rxMessage, sizeof(rxMessage));
//        Serial.println("Received" + rxMessage);
        radio.stopListening();
        if(rxMessage == 0xff) {
          correctMessage = true;
          digitalWrite(9, LOW);
          digitalWrite(10, HIGH);
          state = 4;
          radio.startListening();        
          }
      }
      break;
    case 4:
      correctMessage = false;
      while(!correctMessage) {
        while (!radio.available());
        radio.read(&rxMessage, sizeof(rxMessage));
        Serial.println("Received" + rxMessage);
        radio.stopListening();
        if(rxMessage == 0xaf) {
          correctMessage = true;
          digitalWrite(9, LOW);
          digitalWrite(10, LOW);
          state = 0;
        }
      }
      
  }
    
//    bool sent = false;
//    if(digitalRead(2)) {
//      sent = radio.write(&text,sizeof(text));
//      if(sent) {
//        //motor start
//        Serial.println("Motor Start");
//        radio.startListening();
//        while(!radio.available());
//        //motor stop
//        radio.read(&rxText, sizeof(rxText));
//        
//        if(!strcmp(rxText, 'A'))
//        Serial.println("Motor A Stop");
//        else if(!strcmp(rxText, 'B'))
//        Serial.println("Motor B Stop");
//        else if(!strcmp(rxText, 'C'))        
//        Serial.println("Motor C Stop");
//        else
//        Serial.println("Error");
//      }
//    }

//    if(radio.available()) {
//      radio.stopListening();
//      Serial.println("Transmitted");
//    }
}
