#include <IRremote.h>
int RECV_PIN = 17;
IRrecv irrecv(RECV_PIN);
decode_results results;
int Tjunction = 0;

bool IR = true;
int sensors[5] = {0, 0, 0, 0, 0};
float error = 0, accError = 0, prevError = 0, correction = 0;
//int sensorLimits[5] = {800, 550, 979, 700, 750};

int sensorLimits[5] = {613, 763, 580, 835, 959};

float Kp = 30, Ki = 0, Kd = 30;
float baseMotorSpeed = 60;

bool enablePID = false;
char destinationSink = '0';

void setup() {
  Serial.begin(9600);

  irrecv.enableIRIn(); // Start the receiver

  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
}

void loop() {
  Serial.println(Tjunction);
  if (destinationSink == '0') {
    if (irrecv.decode(&results)) {
      Serial.println("Waiting for message");

      if (results.value == 0x45555550) {
        destinationSink = 'a';
        Serial.println("Message received_A");
      }
      else if (results.value == 0xF124B0B6) {
        destinationSink = 'b';
        Serial.println("Message received_B");
      }
      irrecv.resume(); // Receive the next value
    }
  }
  if (destinationSink != '0') {
    for (int i = 0; i < 5; i++) {
      sensors[i] = analogRead(i);
    }

    if (sensors[0] < sensorLimits[0]  && sensors[1] > sensorLimits[1]
        && sensors[2] > sensorLimits[2] && sensors[3] > sensorLimits[3]
        && sensors[4] > sensorLimits[4]) {
      enablePID = true;
      //Serial.println("PID Left most");
      error = -4; //Left most
    }
    else if (sensors[0] < sensorLimits[0]  && sensors[1] < sensorLimits[1]
             && sensors[2] > sensorLimits[2] && sensors[3] > sensorLimits[3]
             && sensors[4] > sensorLimits[4]) {
      enablePID = true;
      //Serial.println("PID Left most & Left");
      error = -3; //Left most & Left
    }
    else if (sensors[0] > sensorLimits[0]  && sensors[1] < sensorLimits[1]
             && sensors[2] > sensorLimits[2] && sensors[3] > sensorLimits[3]
             && sensors[4] > sensorLimits[4]) {
      enablePID = true;
      //Serial.println("PID Left");
      error = -2; //Left
    }
    //    else if (sensors[0] < sensorLimits[0]  && sensors[1] < sensorLimits[1]
    //             && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
    //             && sensors[4] > sensorLimits[4]) {
    //      enablePID = false;
    //      //Serial.println("PID centre Left Leftmost");
    //      if (Tjunction == 2) {
    //        Tjunction = 3;
    //
    //      }
    //    }
    else if (sensors[0] > sensorLimits[0]  && sensors[1] < sensorLimits[1]
             && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
             && sensors[4] > sensorLimits[4]) {
      enablePID = true;
      //Serial.println("PID Left & Center");
      error = -1; //Left & Center
    }
    else if (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
             && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
             && sensors[4] > sensorLimits[4]) {
      enablePID = true;
      //Serial.println("PID Center");
      error = 0;  //Center
    }
    else if (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
             && sensors[2] < sensorLimits[2] && sensors[3] < sensorLimits[3]
             && sensors[4] > sensorLimits[4]) {
      enablePID = true;
      //Serial.println("PID Center & Right");
      error = 1;  //Center & Right
    }
    else if (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
             && sensors[2] > sensorLimits[2] && sensors[3] < sensorLimits[3]
             && sensors[4] > sensorLimits[4]) {
      enablePID = true;
      //Serial.println("PID Right");
      error = 2;  //Right
    }
    //    else if (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
    //             && sensors[2] < sensorLimits[2] && sensors[3] < sensorLimits[3]
    //             && sensors[4] < sensorLimits[4]) {
    //      enablePID = false;
    //      if (Tjunction == 2) {
    //        Tjunction = 3;
    //      }
    //    }
    else if (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
             && sensors[2] > sensorLimits[2] && sensors[3] < sensorLimits[3]
             && sensors[4] < sensorLimits[4]) {
      enablePID = true;
      //Serial.println("PID Right & Right most");
      error = 3;  //Right & Right most
    }
    else if (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
             && sensors[2] > sensorLimits[2] && sensors[3] > sensorLimits[3]
             && sensors[4] < sensorLimits[4]) {
      enablePID = true;
      //Serial.println("PID Right most");
      error = 4;  //Right most
    }

    else if ( (sensors[1] < sensorLimits[1] && sensors[2] < sensorLimits[2]
               && sensors[3] < sensorLimits[3])) {
      enablePID = false;
      if (Tjunction == 0) {
        Tjunction = 1;
      }
      else if (Tjunction == 1) {
        Tjunction = 2;
      }

      else if (Tjunction == 3) {
        Tjunction = 0;
      }

    }
    else if ((sensors[2] < sensorLimits[2] && sensors[3] < sensorLimits[3]&& sensors[4] < sensorLimits[4])
              || (sensors[1] < sensorLimits[1] && sensors[2] < sensorLimits[2])
              || (sensors[2] < sensorLimits[2] && sensors[3] < sensorLimits[3])) {
                if(Tjunction == 2){
                  Tjunction = 3;
                  enablePID = false;
                }
              }


      else {
        if (error > 0) {
          enablePID = true;
          error = 4;
        }
        else if (error < 0) {
          enablePID = true;
          error = -4;
        }
      }
      if (enablePID) {
        accError = accError + error;

        correction = (Kp * error) + (Ki * accError) + (Kd * (error - prevError));
        //  Serial.print(error);
        //  Serial.print(",");
        //  Serial.println(correction);

        if (baseMotorSpeed + correction < 0) {
          digitalWrite(12, HIGH);
          analogWrite(5, abs(baseMotorSpeed + correction));
          //Serial.println("//Left motor");
        }
        else {
          digitalWrite(12, LOW);  //Left motor
          analogWrite(5, baseMotorSpeed + correction);
          //Serial.println("/Left motor");
        }

        if (baseMotorSpeed - correction < 0) {
          digitalWrite(7, HIGH);   //Right motor
          analogWrite(6, abs(baseMotorSpeed - correction));
          //Serial.println("//Right motor");
        }
        else {
          digitalWrite(7, LOW);   //Right motor
          analogWrite(6, baseMotorSpeed - correction);
          //Serial.println("/Right motor");
        }
        prevError = error;
      }
      else {
        //      Serial.println("T junction");
        if (Tjunction == 1) {
          if (destinationSink == 'a') {
            //Serial.println(" T A");
            digitalWrite(12, HIGH);  //Left motor
            analogWrite(5, 100);
            digitalWrite(7, LOW);   //Right motor
            analogWrite(6, 100);
            delay(100);

            while (!((sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
                      && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
                      && sensors[4] > sensorLimits[4])
                     || (sensors[0] > sensorLimits[0]  && sensors[1] < sensorLimits[1]
                         && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
                         && sensors[4] > sensorLimits[4])
                     || (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
                         && sensors[2] < sensorLimits[2] && sensors[3] < sensorLimits[3]
                         && sensors[4] > sensorLimits[4]))) {
              for (int i = 0; i < 5; i++) {
                sensors[i] = analogRead(i);
              }
              digitalWrite(12, HIGH);  //Left motor
              analogWrite(5, 60);
              digitalWrite(7, LOW);   //Right motor
              analogWrite(6, 60);
            }
            error = 0;
            accError = 0;
            prevError = 0;
            enablePID = true;
          }
          else if (destinationSink == 'b') {
            //Serial.println("T B");
            digitalWrite(12, LOW);  //Left motor
            analogWrite(5, 60);
            digitalWrite(7, HIGH);   //Right motor
            analogWrite(6, 60);
            delay(50);

            while (!((sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
                      && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
                      && sensors[4] > sensorLimits[4])
                     || (sensors[0] > sensorLimits[0]  && sensors[1] < sensorLimits[1]
                         && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
                         && sensors[4] > sensorLimits[4])
                     || (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
                         && sensors[2] < sensorLimits[2] && sensors[3] < sensorLimits[3]
                         && sensors[4] > sensorLimits[4]))) {
              for (int i = 0; i < 5; i++) {
                sensors[i] = analogRead(i);
              }

              digitalWrite(12, LOW); //Left motor
              analogWrite(5, 60);
              digitalWrite(7, HIGH);   //Right motor
              analogWrite(6, 60);
            }

            error = 0;
            accError = 0;
            prevError = 0;
            enablePID = true;
          }
        }
        else if (Tjunction == 2) {
          digitalWrite(12, LOW);  //Left motor
          analogWrite(5, 100);
          digitalWrite(7, HIGH);   //Right motor
          analogWrite(6, 100);
          delay(500);
          //        error = -4;
          while (!((sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
                    && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
                    && sensors[4] > sensorLimits[4])
                   || (sensors[0] > sensorLimits[0]  && sensors[1] < sensorLimits[1]
                       && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
                       && sensors[4] > sensorLimits[4])
                   || (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
                       && sensors[2] < sensorLimits[2] && sensors[3] < sensorLimits[3]
                       && sensors[4] > sensorLimits[4]))) {
            for (int i = 0; i < 5; i++) {
              sensors[i] = analogRead(i);
            }
            digitalWrite(12, LOW);  //Left motor
            analogWrite(5, 60);
            digitalWrite(7, HIGH);   //Right motor
            analogWrite(6, 60);
          }
          digitalWrite(12, LOW);  //Left motor
          analogWrite(5, 0);
          digitalWrite(7, HIGH);   //Right motor
          analogWrite(6, 0);
          delay(5000);

          error = 0;
          accError = 0;
          prevError = 0;
          enablePID = true;
        }
        else if (Tjunction == 3) {
          if (destinationSink == 'a') {
            //Serial.println(" T A");
            digitalWrite(12, LOW);  //Left motor
            analogWrite(5, 60);
            digitalWrite(7, LOW);   //Right motor
            analogWrite(6, 60);
            delay(200);

            //          while (!((sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
            //                    && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
            //                    && sensors[4] > sensorLimits[4])
            //                   || (sensors[0] > sensorLimits[0]  && sensors[1] < sensorLimits[1]
            //                       && sensors[2] > sensorLimits[2] && sensors[3] > sensorLimits[3]
            //                       && sensors[4] > sensorLimits[4])
            //                   || (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
            //                       && sensors[2] > sensorLimits[2] && sensors[3] < sensorLimits[3]
            //                       && sensors[4] > sensorLimits[4]))) {
            //            for (int i = 0; i < 5; i++) {
            //              sensors[i] = analogRead(i);
            //            }
            //
            //            digitalWrite(12, LOW);  //Left motor
            //            analogWrite(5, 100);
            //            digitalWrite(7, HIGH);   //Right motor
            //            analogWrite(6, 100);
            //          }
            error = 0;
            accError = 0;
            prevError = 0;
            enablePID = true;
          }


          else if (destinationSink == 'b') {
            //          Serial.println("T B");
            digitalWrite(12, LOW);  //Left motor
            analogWrite(5, 60);
            digitalWrite(7, LOW);   //Right motor
            analogWrite(6, 60);
            delay(200);
            //          while (!((sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
            //                    && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
            //                    && sensors[4] > sensorLimits[4])
            //                   || (sensors[0] > sensorLimits[0]  && sensors[1] < sensorLimits[1]
            //                       && sensors[2] > sensorLimits[2] && sensors[3] > sensorLimits[3]
            //                       && sensors[4] > sensorLimits[4])
            //                   || (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
            //                       && sensors[2] > sensorLimits[2] && sensors[3] < sensorLimits[3]
            //                       && sensors[4] > sensorLimits[4]))) {
            //            for (int i = 0; i < 5; i++) {
            //              sensors[i] = analogRead(i);
            //            }
            //
            //            digitalWrite(12, HIGH);  //Left motor
            //            analogWrite(5, 100);
            //            digitalWrite(7, LOW);   //Right motor
            //            analogWrite(6, 100);
            //          }

            error = 0;
            accError = 0;
            prevError = 0;
            enablePID = true;
          }
        }
        else if (Tjunction == 0) {
             digitalWrite(12, LOW);  //Left motor
          analogWrite(5, 100);
          digitalWrite(7, HIGH);   //Right motor
          analogWrite(6, 100);
          delay(500);
          //        error = -4;
          while (!((sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
                    && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
                    && sensors[4] > sensorLimits[4])
                   || (sensors[0] > sensorLimits[0]  && sensors[1] < sensorLimits[1]
                       && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
                       && sensors[4] > sensorLimits[4])
                   || (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
                       && sensors[2] < sensorLimits[2] && sensors[3] < sensorLimits[3]
                       && sensors[4] > sensorLimits[4]))) {
            for (int i = 0; i < 5; i++) {
              sensors[i] = analogRead(i);
            }
            digitalWrite(12, LOW);  //Left motor
            analogWrite(5, 60);
            digitalWrite(7, HIGH);   //Right motor
            analogWrite(6, 60);
          }
          
          digitalWrite(12, LOW);  //Left motor
          analogWrite(5, 0);
          digitalWrite(7, HIGH);   //Right motor
          analogWrite(6, 0);

        error = 0;
        accError = 0;
        prevError = 0;
        enablePID = false;
        destinationSink = '0';
          irrecv.resume(); // Receive the next value
        }
      }
    }
  }
