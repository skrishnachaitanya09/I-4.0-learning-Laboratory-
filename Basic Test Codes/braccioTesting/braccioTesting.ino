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

}

void loop() {
  /* Sink A to AGV start*/
  Braccio.ServoMovement (20, 90, 90, 60, 0, 90, 10); //AGV up + gripper open
  delay(100);
  Braccio.ServoMovement (20, 0, 90, 60, 0, 90, 10);   //Sink A up + gripper open
  delay(100);
  Braccio.ServoMovement (20, 0, 120, 5, 25, 90, 10);   //Sink A down + gripper open
  delay(100);
  Braccio.ServoMovement (20, 0, 117, 5, 25, 90, 70);   //Sink A down + gripper close
  delay(100);
  Braccio.ServoMovement (20, 0, 120, 30, 25, 90, 70);   //Sink A up + gripper close
  delay(100);
  Braccio.ServoMovement (20, 95, 120, 30, 25, 90, 70); //AGV up + gripper close
  delay(100);
  Braccio.ServoMovement (20, 95, 70, 30, 25, 90, 70); //AGV down + gripper close
  delay(100);
  Braccio.ServoMovement (20, 95, 70, 30, 25, 90, 10); //AGV down + gripper open
  delay(100);
  Braccio.ServoMovement (20, 90, 90, 60, 0, 90, 10); //AGV up + gripper open
  delay(100);
  /* Sink A to AGV end*/

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
  Braccio.ServoMovement (20, 85, 100, 60, 0, 90, 60); //AGV up + gripper close
  delay(100);
  Braccio.ServoMovement (20, 95, 65, 40, 15, 90, 60); //AGV down + gripper close
  delay(100);
  Braccio.ServoMovement (20, 95, 65, 40, 15, 90, 10); //AGV down + gripper open
  delay(100);
  /* Sink B to AGV end*/
}
