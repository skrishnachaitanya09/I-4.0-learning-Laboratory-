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
bool sent = false;
void(* resetFunc) (void) = 0; //reset function declaration

void setup() {
  radio.begin();
  Serial.begin(9600);
  Serial1.begin(9600);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, dispatchModule[3]);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT); //high towards slider and towards conveyor
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT); //high towards conveyor
  pinMode(11, OUTPUT);
  pinMode(2, INPUT);
  pinMode(30, INPUT_PULLUP);
  pinMode(32, INPUT_PULLUP);

  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  state = 0;
  turn('b');
  
}

void loop() {
  bool sensor = digitalRead(2);
  Serial.println(state);


  if (state == 0) {
    uint8_t address;
    radio.startListening();
    Serial.println("Waiting for message");
    while (!radio.available());
    radio.read(&rxMessage, sizeof(rxMessage));
    Serial.print("Received ");
    Serial.println(rxMessage, HEX);
    radio.stopListening();
    state = 1;
  }

  else if (state == 1) {
    if (rxMessage == 0xcf) {
      moveConveyor('f');
      state = 2;
    }
    else
      state = 0;
  }

  else if (state == 2 && sensor) {
    stopConveyor();
    radio.openWritingPipe(slider[1]);
    txMessage = 0xff;
    sent = radio.write(&txMessage, sizeof(txMessage));
    if (sent) {
      Serial.println("Sent Ack to slider");
      state = 3;
    }
  }

  else if (state == 3) {
    radio.startListening();
    while (!radio.available());
    radio.read(&rxMessage, sizeof(rxMessage));
    radio.stopListening();
    if (rxMessage == 0xee) {
      Serial.print("Received ");
      Serial.println(rxMessage, HEX);
      state = 4;
    }
  }

  else if (state == 4) {
    uint8_t finalAck;
    turn('f');
    moveConveyor('b');
    Serial1.write(0xcf);
    while (!Serial1.available());
    finalAck = Serial1.read();
    if (finalAck == 0xff) {
      stopConveyor();
      turn('b');
      state = 0;
    }
  }
}

void moveConveyor(char direction) {
  if (direction == 'b') {
    digitalWrite(9, HIGH);
    digitalWrite(6, LOW);
  }
  if (direction == 'f') {
    digitalWrite(9, LOW);
    digitalWrite(6, HIGH);
  }
}

void stopConveyor() {
  digitalWrite(9, LOW);
  digitalWrite(6, LOW);
}

void turn(char direction) {
  if (direction == 'f') {
   while(digitalRead(32)) {
   digitalWrite(10, HIGH);
      digitalWrite(11, LOW);
    }
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  }
  if (direction == 'b') {
    while (digitalRead(30)) {
      digitalWrite(10, LOW);
      digitalWrite(11, HIGH);
    }
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
  }
}
