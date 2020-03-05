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
  pinMode(3,INPUT_PULLUP); //upper limit switch
  pinMode(4,INPUT_PULLUP); //lower limit switch
  pinMode(8,OUTPUT); //conveyor positive
  pinMode(9,OUTPUT); //conveyor negative
  pinMode(10,OUTPUT); //slider forward
  pinMode(11,OUTPUT); //slider backward
  Serial.begin(9600);
  digitalWrite(8,HIGH); //conveyor forward
  digitalWrite(9,HIGH); //conveyor reverse
  digitalWrite(10,HIGH); //slider initial
  digitalWrite(11,HIGH); //slider final
}

void loop() 
{
  int sens=digitalRead(2);
  int lt_sw1=digitalRead(3);
  int lt_sw2=digitalRead(4);
  Serial.println(sens);

  if(sens && !lt_sw2)
  {
    digitalWrite(10,HIGH);
    digitalWrite(11,LOW);
  }
  if(sens && !lt_sw1) 
  {
    pushPalette();
  }
  if(!sens && !lt_sw1) {
    digitalWrite(8,LOW);
    digitalWrite(9,LOW);
    digitalWrite(10,LOW);
    digitalWrite(11,HIGH);
    
  }
  if(!sens && !lt_sw2) {
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
  }

//  if(lt_sw1==0)
//  {
//    digitalWrite(10,LOW);
//    digitalWrite(11,HIGH);
//  }
//  if(lt_sw2==0)
//  {
//    digitalWrite(10,HIGH);
//    digitalWrite(11,LOW);
//  }

} 

 void pushPalette() {
    digitalWrite(10,LOW);
    digitalWrite(11,LOW);
    digitalWrite(8,HIGH);
    digitalWrite(9,LOW);
    delay(2000);
 }
