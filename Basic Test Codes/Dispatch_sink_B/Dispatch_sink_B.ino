#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

#define ACK 0xff

RF24 radio(7, 6);

const uint64_t talking_pipes[5] = { 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL, 0xF0F0F0F0A5LL, 0xF0F0F0F096LL };
const uint64_t listening_pipes[5] = { 0x3A3A3A3AD2LL, 0x3A3A3A3AC3LL, 0x3A3A3A3AB4LL, 0x3A3A3A3AA5LL, 0x3A3A3A3A96LL };


const byte txAddr[6] = "11800";
const byte rxAddr[6] = "11802";
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
  radio.openReadingPipe(1, listening_pipes[2]);
  radio.openWritingPipe(talking_pipes[2]);
  
  pinMode(9,OUTPUT); //high towards slider
  pinMode(8,OUTPUT);
  pinMode(2,INPUT); //towards slider
  pinMode(3,INPUT);
  state = 0;
}

void loop() {
  bool firstSensor = digitalRead(2);
  bool secondSensor = digitalRead(3);
  
  Serial.println(state);
 
 
  if(state == 0) {
    txMessage = 0x11;
   radio.startListening();
   Serial.println("Waiting for message");
  while(!radio.available());
  radio.read(&rxMessage, sizeof(rxMessage));
  Serial.println("Received ");
  Serial.print(rxMessage, HEX);
  radio.stopListening();
  if(rxMessage == 0xbf) {
     digitalWrite(8, HIGH);
     digitalWrite(9, LOW);
     state = 1;
  }

  }
  
  else if(state == 1 && firstSensor) {
    txMessage = 0xff;
    sent = radio.write(&txMessage, sizeof(txMessage));
    if(sent) {
      Serial.println("Sent Ack to slider");
      state = 2;
    }
  }
  else if(state == 2 && secondSensor) {
    txMessage = 0xdf;
    digitalWrite(8, LOW);
    digitalWrite(9, LOW);
    sent = radio.write(&txMessage, sizeof(txMessage));
    if(sent) {
      Serial.println("Sent message to Arm");
      state = 0;
    }
  }
  else if(state == 3 && secondSensor) {
    
    radio.startListening();
    while(!radio.available());
    radio.read(&rxMessage, sizeof(rxMessage));
    if(rxMessage == 0xff) {
      Serial.println("Received Ack from Arm");
      state = 0;
    }
  }
}
