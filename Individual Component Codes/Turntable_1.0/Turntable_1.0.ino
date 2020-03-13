//#define SIGNALPIN 2
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
void setup() 
{
//  pinMode(SIGNALPIN,INPUT);
  pinMode(SENSORPIN,INPUT);
  pinMode(LDRA,INPUT);
  pinMode(LDRB,INPUT);
  pinMode(LDRC,INPUT);
  pinMode(lt_sw1,INPUT_PULLUP);
  pinMode(lt_sw2,INPUT_PULLUP);
  pinMode(LEDA,OUTPUT);
  pinMode(LEDB,OUTPUT);
  pinMode(LEDC,OUTPUT);
 Serial.begin(9600);
//  pinMode(conmotpos,OUTPUT);
//  pinMode(conmotneg,OUTPUT);
  pinMode(8,OUTPUT); //r
  pinMode(9,OUTPUT); //r
  pinMode(10,OUTPUT); //l
  pinMode(11,OUTPUT); //l
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
  
  int ambientReadingA = analogRead(LDRA);
}

void loop() 
{
  //boolean signalValue = digitalRead(SIGNALPIN); //testing
  boolean sensorValue = digitalRead(SENSORPIN);
  int a=analogRead(LDRA);
  int b=analogRead(LDRB);
  int c=analogRead(LDRC);
  int limitsw1=digitalRead(lt_sw1);
  int limitsw2=digitalRead(lt_sw2);
//Serial.println(a);
  if((sensorValue==0) && (a>ambientReadingA+THRESHOLD) && (limitsw1==0)&& (limitsw2==1))
  {
    //turn table towards A
    digitalWrite(8,LOW);
    digitalWrite(9,HIGH);
    digitalWrite(10,HIGH);
    digitalWrite(11,HIGH);
    digitalWrite(LEDA,LOW);
    Serial.println("Turning towards A"); 
  }
  
  if((sensorValue==0) && (a>ambientReadingA+THRESHOLD) && (limitsw2==0)&& (limitsw1==1))
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
    Serial.println("Turned towards storage");
  }
 if((sensorValue==1) && (limitsw2==1)&& (limitsw1==0))
 {
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(LEDA,LOW);
 }
  

}
