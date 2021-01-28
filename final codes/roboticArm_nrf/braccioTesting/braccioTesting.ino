#include <Braccio.h>
#include <Servo.h>

#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>


Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

RF24 radio(7, 8);
const uint64_t slider[5] = { 0xF0F0F0F0D2LL, 0xF0F0F0F0C3LL, 0xF0F0F0F0B4LL, 0xF0F0F0F0A5LL, 0xF0F0F0F096LL };
const uint64_t dispatchModule[6] = { 0x3A3A3A3AD2LL, 0x3A3A3A3AC3LL, 0x3A3A3A3AB4LL, 0x3A3A3A3AA5LL, 0x3A3A3A3A96LL, 0x3A3A3A3A87LL };

int state;
uint8_t txMessage;
uint8_t rxMessage;
uint8_t source;
bool correctMessage;
bool sent = false;
char incomingSink = '0';

void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);   // you need to set HIGH the pin 12
  digitalWrite(12, HIGH);
  Braccio.begin(SOFT_START_DISABLED);

  radio.begin();
  Serial.begin(9600);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, slider[4]);

  Braccio.ServoMovement (20, 90, 90, 60, 0, 90, 10); //AGV up + gripper open
  delay(500);
}

void loop() {
  /* Sink A to AGV start*/
  Braccio.ServoMovement (20, 90, 90, 60, 0, 90, 10); //AGV up + gripper open
  delay(100);
  radio.startListening();
  Serial.println("Waiting for message");
  while (!radio.available());
  radio.read(&rxMessage, sizeof(rxMessage));
  Serial.print("Received ");
  Serial.println(rxMessage, HEX);
  radio.stopListening();
  if (rxMessage == 0xef) {
    incomingSink = 'a';
  }
  else if (rxMessage == 0xdf) {
    incomingSink = 'b';
  }
  else {
    incomingSink = '0';
  }

  if (incomingSink == 'a') {
  Braccio.ServoMovement (20, 90, 90, 60, 0, 90, 10); //AGV up + gripper open
  delay(100);
  Braccio.ServoMovement (20, 12, 90, 60, 0, 90, 10);   //Sink A up + gripper open
  delay(100);
  Braccio.ServoMovement (20, 12, 120, 5, 25, 90, 10);   //Sink A down + gripper open
  delay(100);
  Braccio.ServoMovement (20, 12, 117, 5, 25, 90, 70);   //Sink A down + gripper close
  delay(100);
  Braccio.ServoMovement (20, 12, 120, 30, 25, 90, 70);   //Sink A up + gripper close
  delay(100);

    txMessage = 0xff;
    radio.openWritingPipe(dispatchModule[2]);
    sent = radio.write(&txMessage, sizeof(txMessage));
    if(sent) {
      Serial.println("Sent message to sink");
      incomingSink == '0';
    }
  Braccio.ServoMovement (20, 95, 120, 30, 25, 90, 70); //AGV up + gripper close
  delay(100);
  Braccio.ServoMovement (20, 95, 70, 30, 25, 90, 70); //AGV down + gripper close
  delay(100);
  Braccio.ServoMovement (20, 95, 70, 30, 25, 90, 10); //AGV down + gripper open
  delay(100);
    /* Sink A to AGV end*/
  }
  else if (incomingSink == 'b') {
    /* Sink B to AGV start*/
  Braccio.ServoMovement (20, 90, 90, 60, 0, 90, 10); //AGV up + gripper open
  delay(100);
  Braccio.ServoMovement (20, 180, 90, 60, 0, 90, 10);   //Sink B up + gripper open
  delay(100);
  Braccio.ServoMovement (20, 180, 100, 30, 10, 90, 10);   //Sink B down + gripper open
  delay(100);
  Braccio.ServoMovement (20, 180, 100, 30, 10, 90, 60);   //Sink B down + gripper close
  delay(100);
  Braccio.ServoMovement (20, 180, 100, 60, 0, 90, 60);   //Sink B up + gripper close
  delay(100);
    txMessage = 0xff;
    radio.openWritingPipe(dispatchModule[1]);
    sent = radio.write(&txMessage, sizeof(txMessage));
    if(sent) {
      Serial.println("Sent message to sink");
      incomingSink == '0';
    }
  Braccio.ServoMovement (20, 85, 100, 60, 0, 90, 60); //AGV up + gripper close
  delay(100);
  Braccio.ServoMovement (20, 95, 65, 40, 15, 90, 60); //AGV down + gripper close
  delay(100);
  Braccio.ServoMovement (20, 95, 65, 40, 15, 90, 10); //AGV down + gripper open
  delay(100);
    /* Sink B to AGV end*/
  }
}
