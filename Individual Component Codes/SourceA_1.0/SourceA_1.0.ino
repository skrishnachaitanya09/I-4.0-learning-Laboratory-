/*States :
 Green : Under Process
 Red : Waiting for Order
 Orange : Waiting for Product to be placed*/

#define r 10 //red LED
#define g 11 //green LED
#define o 12 //orange LED
#define SENSOR1 4
#define SENSOR2 5
#define LDRPIN 6
#define LEDPIN 7
#define motorpos 8
#define motorneg 9
#define THRESHOLD 90
char state = r;
ambientReading = analogRead(LDRPIN);

void setup() {
  pinMode(SENSOR1,INPUT);
  pinMode(SENSOR2,INPUT);
  pinMode(LDRPIN,INPUT);
  pinMode(LEDPIN,OUTPUT);
  pinMode(motorpos,OUTPUT);
  pinMode(motorneg,OUTPUT);
  Serial.begin(9600);
}

void loop() {
  reading = analogRead(LDRPIN);
  sensor1 = digitalRead(SENSOR1);
  sensor2 = digitalRead(SENSOR2);
  digitalWrite(state,HIGH);
  
  if(reading>ambientReading + THRESHOLD && state = r)
  {
    state = o;
  }
  if(sensor1 == HIGH && state == o)
  {
    state = g;
    digitalWrite(motorpos,HIGH);
    digitalWrite(motorneg,LOW);
  }
  if(sensor2 == HIGH && state == g)
  {
    digitalWrite(LEDPIN,HIGH);
  }
  if(sensor2 == LOW && state == g && reading>ambientReading + THRESHOLD)
  {
    digitalWrite(motorpos,LOW);
  } 
  if(reading>ambientReading + THRESHOLD && state == g)
  {
    state = r;
  }
}
