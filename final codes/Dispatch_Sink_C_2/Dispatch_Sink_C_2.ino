int state;
uint8_t incomingMessage;
void setup() {
  Serial.begin(9600);
  Serial1.begin(9600);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT); 
  pinMode(9, OUTPUT); //high forward

  pinMode(2, INPUT); //ending sensor
  pinMode(3, INPUT); //starting sensor

  digitalWrite(4, HIGH);
  digitalWrite(5, HIGH);
  state = -1;

}

void loop() {
  bool firstSensor = digitalRead(3);
  bool secondSensor = digitalRead(2);
  Serial.println(firstSensor);
  Serial.println(secondSensor);
  Serial.println("---------------------");
  if(state == 0) {
    while(!Serial1.available());
    incomingMessage = Serial1.read();
    if(incomingMessage == 0xcf) {
      moveConveyor('f');
      state = 1;
    }
  }

  else if(state == 1 && firstSensor) {
    Serial1.write(0xff);
    state = 2;
  }

  else if(state == 2 && secondSensor) {
    delay(3000);
    stopConveyor();
    state = 0;
  }
}

void moveConveyor(char direction) {
  if (direction == 'f') {
    digitalWrite(9, HIGH);
    digitalWrite(6, LOW);
  }
  if (direction == 'b') {
    digitalWrite(9, LOW);
    digitalWrite(6, HIGH);
  }
}

void stopConveyor() {
  digitalWrite(9, LOW);
  digitalWrite(6, LOW);
}
