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
  int reading = analogRead(LDRPIN);
  boolean sensor1 = digitalRead(SENSOR1);
  boolean sensor2 = digitalRead(SENSOR2);
  digitalWrite(state,HIGH);
  
  switch(state)
  {
    case r: if(reading > ambientReading + THRESHOLD)
    {
      state = o;
    }
    break;

    case o: if(sensor1 == HIGH)
    {
      state = g;
      digitalWrite(motorpos,HIGH);
      digitalWrite(motorneg,LOW);
    }
    break;

    case g:
    if(sensor2 == HIGH)
      {
        digitalWrite(LEDPIN,HIGH); 
      }
    if(sensor2 == LOW && reading > ambientReading+THRESHOLD)
    {
      digitalWrite(motorpos,LOW);
      digitalWrite(LEDPIN,LOW);
      state = r;
    }
    break;
    
    default:
    //conveyor stop
    state = r //error blink;
  }
}
