#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

#define ACK 0xff

RF24 radio(7, 8);
const uint64_t talking_pipes[5] = { 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL, 0xF0F0F0F0A5LL, 0xF0F0F0F096LL };
const uint64_t listening_pipes[5] = { 0x3A3A3A3AD2LL, 0x3A3A3A3AC3LL, 0x3A3A3A3AB4LL, 0x3A3A3A3AA5LL, 0x3A3A3A3A96LL };

uint8_t rxAddr[5] = "11800";
uint8_t txAddr[5] = "11801";
uint8_t sinkReadAddr[2] = "02";
uint8_t sinkWriteAddr[5] = "11803";
uint8_t sinkAddr;

/*
   NRF Connections with Arduino Mega:
   CE - 7
   CSN - 8
   M1/MISO - 50
   M0/MOSI - 51
   SCK - 52
*/

int state;
uint8_t txMessage;
uint8_t rxMessage;
uint8_t source;
bool correctMessage;
bool sent = false;

void setup() {
  pinMode(2, INPUT);
  radio.begin();
  Serial.begin(9600);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, talking_pipes[0]);
  radio.openReadingPipe(2, talking_pipes[1]);
  radio.openReadingPipe(3, talking_pipes[2]);
  radio.openReadingPipe(4, talking_pipes[3]);
  

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
  digitalWrite(11,LOW);
  state = 0;
}
void loop() {
  
  
  bool sensor = digitalRead(2);

  if(sensor && state == 3) {
      digitalWrite(9,LOW);
      digitalWrite(10,LOW);
      uint8_t txMessage2 = 0xdd;
      sent = radio.write(&txMessage2, sizeof(txMessage2));
      if(sent) {
        Serial.print("Sent ");
        Serial.println(txMessage2, HEX);
        state = 4;
      }
  }
  Serial.println(state);
  
  
      if(state == 0) {
      radio.startListening();
      Serial.println("Waiting for message");
      while(!radio.available());
      radio.read(&rxMessage, sizeof(rxMessage));
      Serial.print("Received ");
      Serial.println(rxMessage, HEX);
      radio.stopListening();
      if(rxMessage == 0xaa) {
        digitalWrite(9,LOW);
        digitalWrite(10,HIGH);
        state = 1;
      }

      }
      
      

    else if(state == 1) {
      radio.openWritingPipe(listening_pipes[0]);
      uint8_t txMessage1 = 0xbb;
      sent = radio.write(&txMessage1, sizeof(txMessage1));
      if(sent) {
        Serial.print("Sent ");
        Serial.println(txMessage1, HEX);
        state = 2;
      }
    }
      
      

    else if(state == 2) {
      state = 1;
      radio.startListening();
      while(!radio.available());
      radio.read(&rxMessage, sizeof(rxMessage));
      Serial.print("Received ");
      Serial.println(rxMessage, HEX);
      if(rxMessage == 0xaf || rxMessage == 0xbf || rxMessage == 0xcf) {
        source = rxMessage;
        radio.stopListening();
        state = 3;
      }
    }
      
     
     
      else if(state == 4) {
       
      if(source == 0xaf) {
        radio.openWritingPipe(listening_pipes[1]);
        sent = radio.write(&source, sizeof(source));
        if(sent) {
          digitalWrite(9, LOW);
          digitalWrite(10,HIGH);
          Serial.println("Sent to A");
          state = 5;
        }

      }
      else if(source == 0xbf) {
        radio.openWritingPipe(listening_pipes[2]);
        state = 5;
        while(digitalRead(3)) {
          digitalWrite(11, LOW);
          digitalWrite(12, HIGH);
        }
        digitalWrite(12,LOW);
        sent = radio.write(&source, sizeof(source));
        if(sent) {
          Serial.println("Sent to B");
          state = 5;
        digitalWrite(9, LOW);
        digitalWrite(10,HIGH);  
        }
        
      }
      else if(source == 0xcf) {
        radio.openWritingPipe(listening_pipes[3]);
        
        while(digitalRead(3)) {
          digitalWrite(11, LOW);
          digitalWrite(12, HIGH);
        }
        digitalWrite(12,LOW);
        sent = radio.write(&source, sizeof(source));
        if(sent) {
          Serial.println("Sent to C");
          state = 5;
          digitalWrite(9, HIGH);
          digitalWrite(10,LOW);
        }
        
      }
      }

      else if(state == 5) {
      uint8_t address;
        radio.startListening();
        while(!radio.available(&address));
        radio.read(&rxMessage, sizeof(rxMessage));
        radio.stopListening();
        if(rxMessage == 0xff) {
          digitalWrite(9, LOW);
          digitalWrite(10, LOW);
          while(digitalRead(4)) {
            digitalWrite(11, HIGH);
            digitalWrite(12, LOW);
          }
          digitalWrite(11,LOW);
          state = 0;
        }
      }
      
  

  
}
