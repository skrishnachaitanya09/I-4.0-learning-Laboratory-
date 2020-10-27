#include <Braccio.h>
#include <Servo.h>

Servo base;
Servo shoulder;
Servo elbow;
Servo wrist_rot;
Servo wrist_ver;
Servo gripper;

void setup() {
  // put your setup code here, to run once:
  pinMode(12, OUTPUT);   // you need to set HIGH the pin 12
  digitalWrite(12, HIGH);
  Braccio.begin(SOFT_START_DISABLED);

  Braccio.ServoMovement (20, 90, 90, 90, 90, 90, 10);
  delay(3000);
  
  Braccio.ServoMovement (20, 90, 80, 0, 90, 90, 10);
  delay(1000);
  Braccio.ServoMovement (20, 90, 80, 0, 90, 90, 73);
  delay(1000);
  Braccio.ServoMovement (20, 90, 90, 45, 90, 90, 73);
  delay(1000);
  Braccio.ServoMovement (20, 0, 80, 45, 90, 90, 73);
  delay(1000);
  Braccio.ServoMovement (20, 0, 80, 0, 90, 90, 73);
  delay(1000);
  Braccio.ServoMovement (20, 0, 80, 0, 90, 90, 10);

  delay(3000);
  Braccio.ServoMovement (20, 0, 90, 90, 90, 90, 10);
  
}

void loop() {
  // put your main code here, to run repeatedly:

}
