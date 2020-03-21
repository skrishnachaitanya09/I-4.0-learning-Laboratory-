
#define SENSORPIN 5

#define lt_sw1 6  //6 pin on arduino
#define lt_sw2 7  // 7 pin on arduino
#define LEDA 2
#define LEDB 3
#define LEDC 4
#define LDRA A0
#define LDRB A1
#define LDRC A2
#define lin_mtr_n 10
#define lin_mtr_p 11
#define rot_mtr_p 8
#define rot_mtr_n 9
#define THRESHOLD 90
int ambientReadingA;
int ambientReadingB;
int ambientReadingC;
bool aa=false;
bool bb=false;
bool cc=false;
void setup() 
{

  pinMode(SENSORPIN,INPUT);
  pinMode(LDRA,INPUT);
  pinMode(LDRB,INPUT);
  pinMode(LDRC,INPUT);
  pinMode(lt_sw1,INPUT_PULLUP);
  pinMode(lt_sw2,INPUT_PULLUP);
  pinMode(LEDA,OUTPUT);
  pinMode(LEDB,OUTPUT);
  pinMode(LEDC,OUTPUT);
 Serial1.begin(38400);
 Serial.begin(9600);

  pinMode(8,OUTPUT); //r
  pinMode(9,OUTPUT); //r
  pinMode(10,OUTPUT); //l
  pinMode(11,OUTPUT); //l
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  
  int ambientReadingA = analogRead(LDRA);
  int ambientReadingB = analogRead(LDRB);
  int ambientReadingC = analogRead(LDRC);
}

void loop() 
{
  
  boolean sensorValue = digitalRead(SENSORPIN);
  int a=analogRead(LDRA);
  int b=analogRead(LDRB);
  int c=analogRead(LDRC);
  int limitsw1=digitalRead(lt_sw1);
  int limitsw2=digitalRead(lt_sw2);
// Serial.println(sensorValue);
//
//    digitalWrite(9,LOW);
//    digitalWrite(8,HIGH);
//    if(limitsw1==0)
//    {
//          digitalWrite(9,HIGH);
//    digitalWrite(8,HIGH);
//    }
 /* for source A*/
  if((sensorValue==0) && (a>ambientReadingA+THRESHOLD) && (limitsw1==0)&& (limitsw2==1))
  {
    aa=true;
    bb=false;
    cc=false;
    //turn table towards A
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(LEDA,LOW);
    Serial.println("Turning towards A"); 
  }
 if((sensorValue==0) && (a>ambientReadingA+THRESHOLD) && (limitsw2==0)&& (limitsw1==1) )
  {
    //turn table rotation stop
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
    digitalWrite(LEDA,HIGH);
    Serial.println("Turned towards A");
  }
    if((sensorValue==1) && (limitsw2==0)&& (limitsw1==1))
  {
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(8,HIGH);
    digitalWrite(LEDA,LOW);
    Serial.println("Turned towards storage from A");
  }


   if((sensorValue==1) && (limitsw2==1)&& (limitsw1==0) && aa)
 {
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(LEDA,LOW);
  digitalWrite(LEDB,LOW);
  digitalWrite(LEDC,LOW);
  Serial1.write('A');
 }

 /* for source B*/
  if((sensorValue==0) && (b>ambientReadingB+THRESHOLD) && (limitsw1==0)&& (limitsw2==1))
  {
    aa=false;
    bb=true;
    cc=false;
    //turn table towards B
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(LEDB,LOW);
    Serial.println("Turning towards B"); 
  }


  
 
 if((sensorValue==0) && (b>ambientReadingB+THRESHOLD) && (limitsw2==0)&& (limitsw1==1))
  {
    //turn table rotation stop
    digitalWrite(8,HIGH);
    digitalWrite(9,HIGH);
    digitalWrite(11,LOW);
    digitalWrite(10,HIGH);
    digitalWrite(LEDB,HIGH);
    Serial.println("Turned towards B");
  }


 if((sensorValue==1) && (limitsw2==0)&& (limitsw1==1) && bb)
  {
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(9,LOW);
    digitalWrite(8,HIGH);
    digitalWrite(LEDB,LOW);
    Serial.println("Turned towards storage from B");
  }
 

 if((sensorValue==1) && (limitsw2==1)&& (limitsw1==0) && bb)
 {
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(LEDB,LOW);
  digitalWrite(LEDA,LOW);
  digitalWrite(LEDC,LOW);
  Serial1.write('B');
 }

/* from source C  */

if((sensorValue==0) && (c>ambientReadingC+THRESHOLD) && (limitsw2==1)&& (limitsw1==0))
  {
      aa=false;
      cc=true;
      bb=false;
      digitalWrite(10,LOW);
      digitalWrite(11,HIGH);
      digitalWrite(LEDC,LOW);
      Serial.println("Turned towards C and to storage ");
      Serial1.write('C');
  }
  
if((sensorValue==1) && (limitsw2==1)&& (limitsw1==0) && cc)
 {
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(LEDC,HIGH);
  digitalWrite(LEDA,LOW);
  digitalWrite(LEDB,LOW);
  Serial1.write('C');
 }
 if(Serial1.available())
 {
  char state = Serial1.read();
  if(state == 'S')
  {
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    cc = false;
  }
 }
}
