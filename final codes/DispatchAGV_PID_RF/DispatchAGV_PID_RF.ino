int sensors[5] = {0, 0, 0, 0, 0};
float error = 0, accError = 0, prevError = 0, correction = 0;
int sensorLimits[5] = {800, 550, 979, 700, 750};

float Kp = 60, Ki = 0, Kd = 60;
float baseMotorSpeed = 60;

bool enablePID = false;
char destinationSink = 'a';

void setup() {
  // put your setup code here, to run once:
  pinMode(5, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);

  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);

  Serial.begin(9600);
}

void loop() {
  for (int i = 0; i < 5; i++) {
    sensors[i] = analogRead(i);
  }

  if (sensors[0] < sensorLimits[0]  && sensors[1] > sensorLimits[1]
      && sensors[2] > sensorLimits[2] && sensors[3] > sensorLimits[3]
      && sensors[4] > sensorLimits[4]) {
    enablePID = true;
    error = -4; //Left most
  }
  else if (sensors[0] < sensorLimits[0]  && sensors[1] < sensorLimits[1]
           && sensors[2] > sensorLimits[2] && sensors[3] > sensorLimits[3]
           && sensors[4] > sensorLimits[4]) {
    enablePID = true;
    error = -3; //Left most & Left
  }
  else if (sensors[0] > sensorLimits[0]  && sensors[1] < sensorLimits[1]
           && sensors[2] > sensorLimits[2] && sensors[3] > sensorLimits[3]
           && sensors[4] > sensorLimits[4]) {
    enablePID = true;
    error = -2; //Left
  }
  else if (sensors[0] > sensorLimits[0]  && sensors[1] < sensorLimits[1]
           && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
           && sensors[4] > sensorLimits[4]) {
    enablePID = true;
    error = -1; //Left & Center
  }
  else if (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
           && sensors[2] < sensorLimits[2] && sensors[3] > sensorLimits[3]
           && sensors[4] > sensorLimits[4]) {
    enablePID = true;
    error = 0;  //Center
  }
  else if (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
           && sensors[2] < sensorLimits[2] && sensors[3] < sensorLimits[3]
           && sensors[4] > sensorLimits[4]) {
    enablePID = true;
    error = 1;  //Center & Right
  }
  else if (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
           && sensors[2] > sensorLimits[2] && sensors[3] < sensorLimits[3]
           && sensors[4] > sensorLimits[4]) {
    enablePID = true;
    error = 2;  //Right
  }
  else if (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
           && sensors[2] > sensorLimits[2] && sensors[3] < sensorLimits[3]
           && sensors[4] < sensorLimits[4]) {
    enablePID = true;
    error = 3;  //Right & Right most
  }
  else if (sensors[0] > sensorLimits[0]  && sensors[1] > sensorLimits[1]
           && sensors[2] > sensorLimits[2] && sensors[3] > sensorLimits[3]
           && sensors[4] < sensorLimits[4]) {
    enablePID = true;
    error = 4;  //Right most
  }
  else if (sensors[0] < sensorLimits[0]  && sensors[1] < sensorLimits[1]
           && sensors[2] < sensorLimits[2] && sensors[3] < sensorLimits[3]
           && sensors[4] < sensorLimits[4]) {
    enablePID = false;
    //T junction
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
      digitalWrite(12, HIGH);  //Left motor
      analogWrite(5, abs(baseMotorSpeed + correction));
    }
    else {
      digitalWrite(12, LOW);  //Left motor
      analogWrite(5, baseMotorSpeed + correction);
    }

    if (baseMotorSpeed - correction < 0) {
      digitalWrite(7, HIGH);   //Right motor
      analogWrite(6, abs(baseMotorSpeed - correction));
    }
    else {
      digitalWrite(7, LOW);   //Right motor
      analogWrite(6, baseMotorSpeed - correction);
    }
    prevError = error;
  }
  else {
    Serial.println("T junction");
    if(destinationSink == 'a') {
      Serial.println("a sink");
      
//      digitalWrite(12, LOW);  //Left motor
//      analogWrite(5, 0);
//      digitalWrite(7, LOW);   //Right motor
//      analogWrite(6, 0);
//      delay(1000);
      
      digitalWrite(12, HIGH);  //Left motor
      analogWrite(5, 100);
      digitalWrite(7, LOW);   //Right motor
      analogWrite(6, 100);
      delay(200);
      error = 0;
      accError=0;
      prevError=0;
    }
  }

  //6, 9
  //10, 11
  //2, 3
  //22, 24 limit switch
  

  //  delay(500);
}
