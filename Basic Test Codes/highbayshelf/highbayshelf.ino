#include "highbayshelf.h"

//SENSORS
int sc1sens1;        // source conveyor1: sensor1
int sc1sens2;        //source conveyor1: sensor2
int sc2sens;         //source conveyor2 sensor
int sc3sens;         //source conveyor3 sensor
int srbsens;         // storage and retrieval belt sensor
int dsens;           // destination sensor
int storage;

// LIMIT SWITCHES
int slt_sw;          // source side limit switch 
int udsrrlt_sw1;     // ASRS belt right side bottom switch 
int udsrrlt_sw2;     //ASRS belt right side middle switch 
int udsrrlt_sw3;     //ASRS belt right side upper switch 
int rlsrlt_sw1;      // storage and retrieval belt right side limit switch
int rlsrlt_sw2;      //storage and retrieval belt middle limit switch
int rlsrlt_sw3;      //storage and retrieval belt left side limit switch
int hbslt_sw1;       //41 high bay shelf first limit switch
int hbslt_sw2;       //43 high bay shelf second limit switch
int hbslt_sw3;       //45 high bay shelf third limit switch
int hbslt_sw4;       //47 high bay shelf fourth limit switch(towards source and destination)
int udsrllt_sw1;     //38 ASRS belt left side bottom switch 
int udsrllt_sw2;     //48 ASRS belt left side middle switch 
int udsrllt_sw3;     //40 ASRS belt left side top switch 


// MOTORS
int sc1mp=6;         // source conveyor1: motor +
int sc1mn=7;         // source conveyor1: motor -
int sc2mp=8;         // source conveyor2: motor +
int sc2mn=9;         // source conveyor2: motor -
int sc3mp=11;        // source conveyor3: motor +
int sc3mn=12;        // source conveyor3: motor -
int srrlmp=30;       // storage and retrieval belt: motor +
int srrlmn=32;       // storage and retrieval belt: motor -
int srudmp=24;       // ASRS up and down motor +
int srudmn=26;       // ASRS up and down motor -
int srtfmp=34;       // ASRS forward and backward motor +
int srtfmn=36;       // ASRS forward and backward motor -
int dm1p=22;         // destination conveyor1: motor +
int dm1n=23;         // destination conveyor1: motor -
int dm2p=42;         // destination conveyor2: motor +
int dm2n=25;         // destination conveyor2: motor -

int a;
char b;
int state;
void setup() 
{
Serial.begin(9600);
Serial1.begin(9600);
Serial2.begin(9600);

pinMode(2,INPUT);  
pinMode(3,INPUT);
pinMode(4,INPUT); 
pinMode(10,INPUT);
pinMode(46,INPUT);
pinMode(28,INPUT);
pinMode(5,INPUT);  

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
pinMode(22,OUTPUT); 
pinMode(23,OUTPUT); 
pinMode(42,OUTPUT); 
pinMode(25,OUTPUT); 



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
digitalWrite(22,HIGH);
digitalWrite(23,HIGH);
digitalWrite(42,HIGH);
digitalWrite(25,HIGH);
}

void loop() 
{
if(Serial1.available() > 0)
 {
  a=Serial1.read();
 }
if(Serial.available() > 0)
 {
  b = Serial.read();
 }
int storage=digitalRead(52);
while((a==11) && (storage==1))
{
store11();
state=111;
Serial2.write(state);
}
while((a==13) && (storage==1))
{
store13();
state=131;
Serial2.write(state);
}
while((a==32) && (storage==1))
{
store32();
state=321;
Serial2.write(state);
}
while((a==33) && (storage==1))
{
store33();
state=331;
Serial2.write(state);
}
while((a==42) && (storage==1))
{
store42();
state=421;
Serial2.write(state);
}
while((a==43) && (storage==1))
{
store43();
state=431;
Serial2.write(state);
}
while((b=='c') && (storage==0))
{
retrieve11();
state=110;
Serial2.write(state);
}
while((b=='a') && (storage==0))
{
retrieve13();
state=130;
Serial2.write(state);
}
while((b=='h') && (storage==0))
{
retrieve32();
state=320;
Serial2.write(state);
}
while((b=='g') && (storage==0))
{
retrieve33();
state=330;
Serial2.write(state);
}
while((b=='k') && (storage==0))
{
retrieve42();
state=420;
Serial2.write(state);
}
while((b=='j') && (storage==0))
{
retrieve43();
state=430;
Serial2.write(state);
}
}

