#define SENSOR1 4
#define SENSOR2 5
#define motorpos 8
#define motorneg 9
bool object=false;
char state ='X';
void setup() 
{
  pinMode(SENSOR1,INPUT);
  pinMode(SENSOR2,INPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);

  pinMode(motorpos,OUTPUT);
  pinMode(motorneg,OUTPUT);
  Serial.begin(9600);
  Serial1.begin(38400);

}

void loop() 
{
 bool sensor1 = digitalRead(SENSOR1);
 bool sensor2 = digitalRead(SENSOR2);
Serial.println(sensor2);
 if(Serial1.available())
 {
  state = Serial1.read();
  Serial.println(state);
 }
  if(state == 'A' || state == 'B' || state == 'C')
  {
    digitalWrite(motorpos,LOW);
    digitalWrite(motorneg,HIGH);
  }
  if(sensor1 == 1 && state == 'A')
  {
    Serial1.write('S');
    digitalWrite(motorpos,LOW);
    digitalWrite(motorneg,HIGH);
    digitalWrite(31,HIGH);
    digitalWrite(30,LOW);
  }
    if(sensor1 == 1 && state == 'B')
  {
    Serial1.write('S');
    digitalWrite(motorpos,LOW);
    digitalWrite(motorneg,HIGH);
    digitalWrite(33,HIGH);
    digitalWrite(32,LOW);
  }
    if(sensor1 == 1 && state == 'C')
  {
    Serial1.write('S');
    digitalWrite(motorpos,LOW);
    digitalWrite(motorneg,HIGH);
    digitalWrite(35,HIGH);
    digitalWrite(34,LOW);
  }

  if(sensor2 == 1 && (state == 'C' || state == 'A' || state == 'B'))
  {
    digitalWrite(motorpos,HIGH);
    digitalWrite(motorneg,HIGH);
  }
 
}
