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

//  Braccio.ServoMovement (20, 90, 90, 90, 90, 90, 10);
//  delay(3000);
//  
//  Braccio.ServoMovement (20, 90, 80, 0, 90, 90, 10);
//  delay(1000);
//  Braccio.ServoMovement (20, 90, 80, 0, 90, 90, 73);
//  delay(1000);
//  Braccio.ServoMovement (20, 90, 90, 45, 90, 90, 73);
//  delay(1000);
//  Braccio.ServoMovement (20, 0, 80, 45, 90, 90, 73);
//  delay(1000);
//  Braccio.ServoMovement (20, 0, 80, 0, 90, 90, 73);
//  delay(1000);
//  Braccio.ServoMovement (20, 0, 80, 0, 90, 90, 10);
//
//  delay(3000);
//  Braccio.ServoMovement (20, 0, 90, 90, 90, 90, 10);



}

void loop() {
  /* Sink A to AGV start*/
  Braccio.ServoMovement (20, 90, 90, 60, 0, 90, 10); //AGV up + gripper open
  delay(500);
  Braccio.ServoMovement (20, 0, 90, 60, 0, 90, 10);   //Sink A up + gripper open
  delay(500);
  Braccio.ServoMovement (20, 10, 100, 30, 0, 90, 10);   //Sink A down + gripper open
  delay(500);
  Braccio.ServoMovement (20, 10, 100, 30, 0, 90, 60);   //Sink A down + gripper close
  delay(500);
  Braccio.ServoMovement (20, 10, 100, 60, 0, 90, 60);   //Sink A up + gripper close
  delay(500);
  Braccio.ServoMovement (20, 90, 100, 60, 0, 90, 60); //AGV up + gripper close
  delay(500);
  Braccio.ServoMovement (20, 90, 60, 45, 0, 90, 60); //AGV down + gripper close
  delay(500);
  Braccio.ServoMovement (20, 90, 60, 45, 0, 90, 10); //AGV down + gripper open
  delay(500);
  /* Sink A to AGV end*/

  /* Sink B to AGV start*/
  Braccio.ServoMovement (20, 90, 90, 60, 0, 90, 10); //AGV up + gripper open
  delay(500);
  Braccio.ServoMovement (20, 172, 90, 60, 0, 90, 10);   //Sink B up + gripper open
  delay(500);
  Braccio.ServoMovement (20, 172, 95, 30, 10, 90, 10);   //Sink B down + gripper open
  delay(500);
  Braccio.ServoMovement (20, 172, 95, 30, 10, 90, 60);   //Sink B down + gripper close
  delay(500);
  Braccio.ServoMovement (20, 172, 90, 60, 0, 90, 60);   //Sink B up + gripper close
  delay(500);
  Braccio.ServoMovement (20, 80, 90, 60, 0, 90, 60); //AGV up + gripper close
  delay(500);
  Braccio.ServoMovement (20, 80, 60, 45, 0, 90, 60); //AGV down + gripper close
  delay(500);
  Braccio.ServoMovement (20, 80, 60, 45, 0, 90, 10); //AGV down + gripper open
  delay(500);
  /* Sink B to AGV end*/
}
