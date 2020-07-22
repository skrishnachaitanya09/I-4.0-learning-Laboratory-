/*States :
 Green : Under Process
 Red : Waiting for Order
 Orange : Waiting for Product to be placed*/

#define r 10 //red LED
#define g 11 //green LED
#define o 12 //orange LED
#define SENSOR1 4
#define SENSOR2 5
#define LDRPIN A0
#define LEDPIN 2
#define motorpos 8
#define motorneg 9
#define THRESHOLD 90
char state = r;
int ambientReading = analogRead(LDRPIN);
bool object=false;
void setup() 
{
  pinMode(SENSOR1,INPUT);
  pinMode(SENSOR2,INPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  pinMode(12,OUTPUT);
  pinMode(LDRPIN,INPUT);
  pinMode(LEDPIN,OUTPUT);
  pinMode(motorpos,OUTPUT);
  pinMode(motorneg,OUTPUT);
  Serial.begin(9600);
  digitalWrite(10,HIGH);
}

void loop() 
{
 int  reading = analogRead(LDRPIN);
  int sensor1 = digitalRead(SENSOR1);
 int sensor2 = digitalRead(SENSOR2);
//
//  Serial.print(sensor1);
//  Serial.print(" ");
  //Serial.println(reading);
   // RED LED IS HIGH
  
  if((reading>ambientReading + THRESHOLD) && state == r)
  {
    state = o;
    digitalWrite(10,LOW);
    digitalWrite(12,HIGH);
  }
  if(sensor1==1 && state==r)
  {
    state=g;
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
    digitalWrite(motorpos,LOW);
    digitalWrite(motorneg,HIGH);
  }
  if(sensor1 == 1 && state == o)
  {
    state = g;
    digitalWrite(10,LOW);
    digitalWrite(12,LOW);
    digitalWrite(11,HIGH);
    digitalWrite(motorpos,LOW);
    digitalWrite(motorneg,HIGH);
  }
  if(sensor2 == 1 && state == g && (reading<ambientReading + THRESHOLD))
  {
    
    digitalWrite(LEDPIN,HIGH);
    object = true;
    // digitalWrite(motorpos,HIGH);
   //  digitalWrite(motorneg,HIGH);//STOP CONVEYOR
  }
  if(sensor2==1 && state==g &&(reading>ambientReading + THRESHOLD))
  {
    object=true;
    digitalWrite(motorpos,LOW);
    digitalWrite(motorneg,HIGH);
    digitalWrite(LEDPIN,LOW);
  }

  if(sensor1 ==0 && sensor2==0 && (reading>ambientReading + THRESHOLD) && state==g && object)
  {
    
    digitalWrite(motorpos,HIGH);
    digitalWrite(motorneg,HIGH);//STOP CONVEYOR
    
    state=r;
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
    object=false;
  }
  

}
