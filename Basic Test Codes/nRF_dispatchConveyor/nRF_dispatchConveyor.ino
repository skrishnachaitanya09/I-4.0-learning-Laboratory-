#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
RF24 radio(7, 8);

const byte txAddr[6] = "11800";
const byte rxAddr[6] = "11801";
const char text[] = "Hi";
char rxText = 'f';
char palletType = '0';

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
char userInput;

const uint64_t talking_pipes[5] = { 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL, 0xF0F0F0F0A5LL, 0xF0F0F0F096LL };
const uint64_t listening_pipes[5] = { 0x3A3A3A3AD2LL, 0x3A3A3A3AC3LL, 0x3A3A3A3AB4LL, 0x3A3A3A3AA5LL, 0x3A3A3A3A96LL };

void setup(){
  pinMode(2,INPUT);
  radio.begin();
  Serial.begin(9600);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, listening_pipes[0]);
  radio.openWritingPipe(talking_pipes[0]);
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
      if(palletType == '0') {
        Serial.println("Please enter the pallet type:");
        while(!Serial.available());
        userInput = Serial.read();
//        char userInput = 'a';
        if(userInput == 'a') {
          palletType = 'a';
        }
        else if (userInput == 'b') {
          palletType = 'b';
        }
        else if (userInput == 'c') {
          palletType = 'c';
        }
        else {
          palletType = '0';
        }
      }
      if(palletType != '0') {
        digitalWrite(9, LOW);
        digitalWrite(10, HIGH);
      }
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
      if(palletType == 'a') {
        txMessage = 0xaf;
      }
      else if(palletType == 'b') {
        txMessage = 0xbf;
      }
      else if(palletType == 'c') {
        txMessage = 0xcf;
      }
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
          palletType = '0';
        }
      }
      break;
    
  }
}
