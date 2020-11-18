#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>

#define ACK 0xff

RF24 radio(7, 8);

const uint64_t slider[5] = { 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL, 0xF0F0F0F0A5LL, 0xF0F0F0F096LL };
const uint64_t dispatchModule[5] = { 0x3A3A3A3AD2LL, 0x3A3A3A3AC3LL, 0x3A3A3A3AB4LL, 0x3A3A3A3AA5LL, 0x3A3A3A3A96LL };

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
uint8_t incomingData;
bool sent = false;


void setup() {
  radio.begin();
  Serial.begin(9600);
  Serial3.begin(9600);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, dispatchModule[0]);
  radio.openWritingPipe(slider[0]);
  radio.stopListening();
  pinMode(6, OUTPUT); //high towards slider
  pinMode(9, OUTPUT);
  pinMode(2, INPUT); //near slider
  pinMode(3, INPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  
  state = 0;
}

void loop() {
  bool firstSensor = digitalRead(3);
  bool secondSensor = digitalRead(2);

  Serial.println(state);

  if (state == 0) {
    while(!Serial3.available());
    incomingData = Serial3.read();
    Serial.println(incomingData);
    if(incomingData == 0xa1) {
      source = 0xaf;
      moveConveyor('f');
      state = 1;
    } 
    
    if(incomingData == 0xb1) {
    source = 0xbf;
    moveConveyor('f');
    state = 1;  
    }

    if(incomingData == 0xc1) {
    source = 0xcf;
    moveConveyor('f');
    state = 1;  
    }
    
   else
   Serial.println("Invalid Source");
  }

  else if (state == 1 && firstSensor) {
    Serial3.write(ACK); //write to highbay shelf
    state = 2;
  }
  else if (state == 2 && secondSensor) {
    txMessage = 0xaa;
    stopConveyor();
    sent = radio.write(&txMessage, sizeof(txMessage));
    if (sent) {
      Serial.println("Sent message to Slider");
      state = 3;
    }
  }
  else if (state == 3) {

    radio.startListening();
    while (!radio.available());
    radio.stopListening();
    radio.read(&rxMessage, sizeof(rxMessage));
    if (rxMessage == ACK) {
      Serial.println("Received Ack from Slider");
      state = 4;
    }
  }
  else if (state == 4) {
    
    sent = radio.write(&source, sizeof(source));
    if (sent) {
      Serial.println("Sending palette and source name to Slider");
      moveConveyor('f');
      state = 5;
    }
  }
  else if (state == 5) {
    radio.startListening();
    while (!radio.available());
    radio.stopListening();
    radio.read(&rxMessage, sizeof(rxMessage));
    if (rxMessage == ACK) {
      Serial.println("Sent palette to Slider");
      stopConveyor();
      state = 0;
    }
  }
}

void moveConveyor(char direction) {
  if (direction == 'f') {
    digitalWrite(6, HIGH);
    digitalWrite(9, LOW);
  }
  if (direction == 'b') {
    digitalWrite(6, LOW);
    digitalWrite(9, HIGH);
  }
}
void stopConveyor() {
    digitalWrite(6, LOW);
    digitalWrite(9, LOW);
}
