
//SENSORS

int sc1sens1; //pin2
int sc1sens2; //pin3
int sc2sens; //pin4
int sc3sens; //pin10
int srbsens; //pin47
// LIMIT SWITCHES
int slt_sw; //27
int udsrrlt_sw1; //29 up down belt right side down switch
int udsrrlt_sw2; //31 up down belt right side middle switch
int udsrrlt_sw3; //33 up down belt right side up switch
int rlsrlt_sw1; //39 right
int rlsrlt_sw2; //35 middle 
int rlsrlt_sw3; //37 left
int hbslt_sw1; //41 towards wall
int hbslt_sw2; //43 
int hbslt_sw3; //45
int hbslt_sw4; //47 towards source and destination
int udsrllt_sw1; //38 up down belt left side down switch
int udsrllt_sw2; //48 up down belt left side middle switch
int udsrllt_sw3; //40 up down belt left side top switch


// MOTORS

int sc1mp=6;
int sc1mn=7;
int sc2mp=8;
int sc2mn=9;
int sc3mp=11;
int sc3mn=12;
int srrlmp=30;
int srrlmn=32;
int srudmp=24;
int srudmn=26;
int srtfmp=34;
int srtfmn=36;


void setup() {
  // put your setup code here, to run once:
pinMode(2,INPUT);  
pinMode(3,INPUT);
pinMode(4,INPUT); 
pinMode(10,INPUT );
pinMode(47,INPUT); 

pinMode(27,INPUT_PULLUP);
pinMode(29,INPUT_PULLUP);
pinMode(31,INPUT_PULLUP);
pinMode(33,INPUT_PULLUP);
pinMode(39,INPUT_PULLUP);
pinMode(35,INPUT_PULLUP); 
pinMode(37,INPUT_PULLUP);
pinMode(41,INPUT_PULLUP);
pinMode(43,INPUT_PULLUP);
pinMode(45,INPUT_PULLUP);
pinMode(47,INPUT_PULLUP);
pinMode(38,INPUT_PULLUP);
pinMode(48,INPUT_PULLUP);
pinMode(40,INPUT_PULLUP);

pinMode(6,OUTPUT); 
pinMode(7,OUTPUT); 
pinMode(8,OUTPUT); 
pinMode(9,OUTPUT); 
pinMode(11,OUTPUT); 
pinMode(12,OUTPUT); 
pinMode(30,OUTPUT); 
pinMode(32,OUTPUT); 
pinMode(24,OUTPUT); 
pinMode(26,OUTPUT); 
pinMode(34,OUTPUT); 
pinMode(36,OUTPUT); 

Serial.begin(9600);

digitalWrite(6,HIGH);
digitalWrite(7,HIGH);
digitalWrite(8,HIGH);
digitalWrite(9,HIGH);
digitalWrite(11,HIGH);
digitalWrite(12,HIGH);
digitalWrite(24,HIGH);
digitalWrite(26,HIGH);
digitalWrite(30,HIGH);
digitalWrite(32,HIGH);
digitalWrite(34,HIGH);
digitalWrite(36,HIGH);
}

void loop() {
  // put your main code here, to run repeatedly:
int sc1sens1=digitalRead(2); //pin2
int sc1sens2=digitalRead(3); //pin3
int sc2sens=digitalRead(4); //pin4
int sc3sens=digitalRead(10); //pin10
int srbsens=digitalRead(44); //pin46

int slt_sw=digitalRead(27); //27
int udsrrlt_sw1=digitalRead(29); //29 up down belt right side down switch
int udsrrlt_sw2=digitalRead(31); //31 up down belt right side middle switch
int udsrrlt_sw3=digitalRead(33); //33 up down belt right side up switch
int rlsrlt_sw1=digitalRead(39); //39 right
int rlsrlt_sw2=digitalRead(35); //35 middle 
int rlsrlt_sw3=digitalRead(37); //37 left
int hbslt_sw1=digitalRead(41); //41 towards wall
int hbslt_sw2=digitalRead(43); //43 
int hbslt_sw3=digitalRead(45); //45
int hbslt_sw4=digitalRead(47); //47 towards source and destination
int udsrllt_sw1=digitalRead(38); //38 up down belt left side down switch
int udsrllt_sw2=digitalRead(48); //48 up down belt left side middle switch
int udsrllt_sw3=digitalRead(40); //40 up down belt left side top switch 

if((sc1sens1==1) && (sc1sens2==0) && (sc2sens==0) && (sc3sens==1) &&(srbsens==1) )
{
  Serial.println("First belt forward");
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW); 
}
if((sc1sens1==0) && (sc1sens2==1) && (sc2sens==0) && (sc3sens==1) &&(srbsens==1))
{
  Serial.println("First & Second belt forward");
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW); 
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW); 
}
if((sc1sens1==0) && (sc1sens2==0) && (sc2sens==1) && (sc3sens==1) &&(srbsens==1))
{
  Serial.println("Second & Third belt forward");
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH); 
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  
}

if((sc1sens1==0) && (sc1sens2==0) && (sc2sens==0) && (sc3sens==0) && (srbsens==1)&& (rlsrlt_sw1==1))
{
//  Serial.println("All belts stop");
  Serial.println("All belts stop. Bring SRB towards source");
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH); 
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(30,LOW);
  digitalWrite(32,HIGH);
  Serial.println(rlsrlt_sw1);
}
if((sc1sens1==0) && (sc1sens2==0) && (sc2sens==0) && (sc3sens==0) && (srbsens==1) && (rlsrlt_sw1==0))
{
  Serial.println("SRB stop. Third Belt forward");
  digitalWrite(30,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH); 
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);

 
}
if((sc1sens1==0) && (sc1sens2==0) && (sc2sens==0) && (sc3sens==1) && (srbsens==1) && (rlsrlt_sw1==0) && (rlsrlt_sw2==1) && (hbslt_sw3==1))
{
  Serial.println("SRB BACKWARD");
  digitalWrite(30,HIGH);
  digitalWrite(32,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH); 
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);

 

}

if((rlsrlt_sw2==0) && (srbsens==0)  && (hbslt_sw3==1) && (udsrrlt_sw1==1))
{
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH); 
  digitalWrite(32,HIGH);
  digitalWrite(30,HIGH);
  digitalWrite(26,HIGH);
  digitalWrite(24,LOW);
  Serial.println("MATERIAL IS INSIDE STOP ALL MOTORS & Move ASRS UP");
}

if((udsrrlt_sw1==0) && (srbsens==0) && (hbslt_sw3==1) &&(udsrllt_sw1==1))
{
  digitalWrite(26,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(36,HIGH);
  digitalWrite(34,LOW);
  Serial.println("STOP MOVING ASRS UP AND MOVE IT TOWARDS SHELF");
}

if((hbslt_sw3==0)&& (srbsens==0) && (udsrrlt_sw1==0))
{
  digitalWrite(36,HIGH);
  digitalWrite(34,HIGH);
  digitalWrite(26,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(30,LOW);
  Serial.println("STOP AT SHELF AND MOVE THE SRB TOWARDS SHELF");
  
}

//if((hbslt_sw2==0) && (srbsens==1) && (rlsrlt_sw1==0) && (udsrrlt_sw1==0))
//{
//  digitalWrite(26,HIGH);
//  digitalWrite(24,HIGH);
//  digitalWrite(36,HIGH);
//  digitalWrite(34,HIGH);
//  digitalWrite(32,HIGH);
//  digitalWrite(30,HIGH);
//  Serial.println("STOP SRB WHEN CORNER SWITCH IS DETECTED AT SHELF ");
//}
if((hbslt_sw3==0) && (rlsrlt_sw1==0) && (udsrrlt_sw1==0) && (srbsens==1))
{
  digitalWrite(26,LOW);
  digitalWrite(24,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(30,HIGH);
  digitalWrite(36,HIGH);
  digitalWrite(34,HIGH);
  Serial.println("SRB AT CORNER AND MOVE THE BELT DOWNWARDS ");
}
if((hbslt_sw3==0) && (rlsrlt_sw1==0) && (udsrllt_sw1==0) && (udsrrlt_sw1==1))
{
  digitalWrite(26,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(36,HIGH);
  digitalWrite(34,HIGH);
  digitalWrite(32,LOW);
  digitalWrite(30,HIGH);
  Serial.println("MOVE BACK  S & R BELT AFTER STORING MATERIAL ");
}
if((hbslt_sw3==0) && (rlsrlt_sw2==0) && (udsrllt_sw1==0) && (srbsens==1))
{
  digitalWrite(26,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(36,LOW);
  digitalWrite(34,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(30,HIGH);
  Serial.println("STOP S & R BELT AFTER STORING MATERIAL AND MOVE BELT BACKWARDS ");
}

if((udsrllt_sw1==0) && (srbsens==1) && (slt_sw==0) &&(rlsrlt_sw2==0) && (sc3sens==1))
{
  digitalWrite(26,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(36,HIGH);
  digitalWrite(34,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(30,HIGH);
  Serial.println("INITIAL POSITION");
}
}
