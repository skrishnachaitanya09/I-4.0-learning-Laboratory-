#define SIGNALPIN 2
#define SENSORPIN 3
#define LEDA 4
#define LEDB 5
#define LEDC 6
#define LDRA 7
#define LDRB 8
#define LDRC 9
#define conmotpos 10
#define conmotneg 11
void setup() {
  pinMode(SIGNALPIN,INPUT);
  pinMode(SENSORPIN,INPUT);
  pinMode(LDRA,INPUT);
  pinMode(LDRB,INPUT);
  pinMode(LDRC,INPUT);
  pinMode(LEDA,OUTPUT);
  pinMode(LEDB,OUTPUT);
  pinMode(LEDC,OUTPUT);
  pinMode(conmotpos,OUTPUT);
  pinMode(conmotneg,OUTPUT);
  int ambientReadingA = analogRead(LDRA);
}

void loop() {
  boolean signalValue = digitalRead(SIGNALPIN); //testing
  boolean sensorValue = digitalRead(SENSORPIN);
  if(signalValue = 1 && reading<ambientReadingA+THRESHOLD) //Product requested when TT in default position
  {
    //turn towards A
    digitalWrite(LEDA,HIGH);
  }
  if(signalValue = 1 && reading>ambientReadingA+THRESHOLD) //Product reached end of source conveyor
  {
    digitalWrite(conmotpos,HIGH); //TT Conveyor start
    digitalWrite(conmotneg,LOW);  //TT Conveyor start
    if(sensorValue == HIGH)
    {
      digitalWrite(conmotpos,LOW); //TT Conveyor stop
      //turn towards default
      digitalWrite(conmotpos,HIGH); //TT Conveyor start
      digitalWrite(conmotneg,LOW); //TT Conveyor start
      digitalWrite(LEDA,LOW); //LED A OFF
      if(sensorValue == LOW) //Product reached output conveyor
      digitalWrite(conmotpos,LOW); //TT Conveyor stops
    }
  }
}
