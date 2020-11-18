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
bool correctMessage;
bool sent = false;
//void(* resetFunc) (void) = 0; //reset function declaration


void setup() {
  radio.begin();
  Serial.begin(9600);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, slider[0]);
  radio.openReadingPipe(2, slider[1]);
  
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT); //High away from storage
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT); //High towards conveyor A

  pinMode(2, INPUT);        //Sensor
  pinMode(30, INPUT_PULLUP); //Near conveyor A
  pinMode(32, INPUT_PULLUP);

  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  while (digitalRead(30)) {
    moveSlider('b');
  }
  stopSlider();
  state = 0;
}

void loop() {
  bool sensor = digitalRead(2);
  bool firstSwitch = !digitalRead(30);
  bool secondSwitch = !digitalRead(32);
  Serial.println(state);
  
    
  if (state == 0) {
    radio.startListening();
    Serial.println("Waiting for message");
    while (!radio.available());
    radio.read(&rxMessage, sizeof(rxMessage));
    radio.stopListening();
    if (rxMessage == 0xaa) {
      moveConveyor('f');
      state = 1;
    }
  }


  else if (state == 1) {
    radio.openWritingPipe(dispatchModule[0]);
    uint8_t txMessage1 = ACK;
    sent = radio.write(&txMessage1, sizeof(txMessage1));
    if (sent) {
      Serial.print("Sent Ack to Dispatch Conveyor ");
      Serial.println(txMessage1, HEX);
      state = 2;
    }
  }


  else if (state == 2) {
    radio.startListening();
    while (!radio.available());
    radio.read(&rxMessage, sizeof(rxMessage));
    Serial.print("Received ");
    Serial.println(rxMessage, HEX);
    if (rxMessage == 0xaf || rxMessage == 0xbf || rxMessage == 0xcf) {
      source = rxMessage;
      radio.stopListening();
      state = 3;
    }
  }

  else if (sensor && state == 3) {
    stopConveyor();
    uint8_t txMessage2 = ACK;
    sent = radio.write(&txMessage2, sizeof(txMessage2));
    if (sent) {
      Serial.print("Sent ");
      Serial.println(txMessage2, HEX);
      state = 4;
    }
  }

  else if (state == 4) {
    if (source == 0xaf) {
      radio.openWritingPipe(dispatchModule[1]);
      sent = radio.write(&source, sizeof(source));
      if(sent) {
       moveConveyor('f');
       state = 5; 
      }
    }
    else if (source == 0xbf) {
      radio.openWritingPipe(dispatchModule[2]);
      while (digitalRead(32)) {
        moveSlider('f');
      }
      stopSlider();
      sent = radio.write(&source, sizeof(source));
      if (sent) {
        state = 5;
        moveConveyor('f');
      }
    }
    else if (source == 0xcf) {
      radio.openWritingPipe(dispatchModule[3]);
      while (digitalRead(32)) {
        moveSlider('f');
      }
      stopSlider();
      sent = radio.write(&source, sizeof(source));
      if (sent) {
        state = 5;
        moveConveyor('b');
      }
    }
  }

  else if (state == 5) {
    uint8_t address;
    radio.startListening();
    while (!radio.available(&address));
    radio.read(&rxMessage, sizeof(rxMessage));
    radio.stopListening();
    if (rxMessage == ACK) {
      stopConveyor();
      state = 6;
      while (digitalRead(30)) {
        moveSlider('b');
      }
      stopSlider();
    }
  }

  else if(state == 6) {
    txMessage = 0xee;
    if (source == 0xaf) { 
      radio.openWritingPipe(dispatchModule[1]);
      sent = radio.write(&txMessage, sizeof(txMessage));
      if(sent) {
       state = 0; 
      }
    }
    else if (source == 0xbf) {
      radio.openWritingPipe(dispatchModule[2]);
      sent = radio.write(&txMessage, sizeof(txMessage));
      if (sent) {
        state = 0;
      }
    }
    else if (source == 0xcf) {
      radio.openWritingPipe(dispatchModule[3]);
      sent = radio.write(&txMessage, sizeof(txMessage));
      if (sent) {
        state = 0;
      }
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

void moveSlider(char direction) {
  if (direction == 'f') {
    digitalWrite(10, HIGH);
    digitalWrite(11, LOW);
  }
  if (direction == 'b') {
    digitalWrite(10, LOW);
    digitalWrite(11, HIGH);
  }
}

void stopSlider() {
    digitalWrite(10, HIGH);
    digitalWrite(11, HIGH);
}
