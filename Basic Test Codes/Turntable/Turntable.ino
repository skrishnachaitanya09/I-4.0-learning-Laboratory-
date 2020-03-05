int sens;   // 2 pin on arduino
int lt_sw1;  //3 pin on arduino
int lt_sw2;  // 4 pin on arduino
int lin_mtr_n=10;
int lin_mtr_p=11;
int rot_mtr_p=8;
int rot_mtr_n=9;

void setup() 
{
  pinMode(2,INPUT);  //sensor
  pinMode(3,INPUT_PULLUP); // sw1
  pinMode(4,INPUT_PULLUP); //sw2
  pinMode(8,OUTPUT); //r
  pinMode(9,OUTPUT); //r
  pinMode(10,OUTPUT); //l
  pinMode(11,OUTPUT); //l
  Serial.begin(9600);
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(10,HIGH);
  digitalWrite(11,HIGH);
}

void loop() 
{
int sens=digitalRead(2);
int lt_sw1=digitalRead(3);
int lt_sw2=digitalRead(4);
Serial.println(lt_sw1);
//if(lt_sw2==0)
//{
//digitalWrite(8,LOW);
//digitalWrite(9,HIGH);
//}
//if(lt_sw1==0)
//{
//digitalWrite(8,HIGH);
//digitalWrite(9,HIGH);
//
//}
//digitalWrite(9,LOW);
//digitalWrite(8,HIGH);
if(sens==0 && lt_sw1==0)
{
digitalWrite(10,HIGH);
digitalWrite(11,LOW);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);

}
if(sens==1 && lt_sw1==0)
{
digitalWrite(10,HIGH);
digitalWrite(11,HIGH);  
digitalWrite(8,LOW);
digitalWrite(9,HIGH); 
}
if(lt_sw2==0 && sens==1)
{
  {
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);
digitalWrite(10,LOW);
digitalWrite(11,HIGH);
  }
delay(2000);
}
if(lt_sw2==0 && sens==0)
{
digitalWrite(8,HIGH);
digitalWrite(9,LOW);
digitalWrite(10,HIGH);
digitalWrite(11,HIGH);
}
}
