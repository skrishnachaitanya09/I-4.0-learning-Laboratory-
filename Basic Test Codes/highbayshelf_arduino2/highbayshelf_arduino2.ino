#include <SPI.h>
#include <MFRC522.h>
#define SS_PIN 53
#define RST_PIN 5
MFRC522 mfrc522(SS_PIN, RST_PIN);
int a=11;
int b=13;
int c=32;
int d=33;
int e=42;
int f=43;
int state;

String uidString1 = "84 87 179 235";
String uidString2 = "22 167 171 187";
String uidString3 = "180 230 219 233";
String uidString4 = "84 94 231 233";
String uidString5 = "68 165 224 233";
String uidString6 = "36 222 176 235";
String uidString;
String Product_Id;
String side;
String Storage_Location_row;
String Storage_Location_coloumn;

void setup() 
{
Serial.begin(9600);
Serial.println("Date & Time,Product_Id,side,Storage_Location_row,Storage_Location_coloumn");
Serial1.begin(9600);
Serial2.begin(9600); 
Serial3.begin(9600);   
SPI.begin();          
mfrc522.PCD_Init();
pinMode(22,OUTPUT); 
pinMode(23,OUTPUT); 
pinMode(24,OUTPUT); 
pinMode(25,OUTPUT); 
pinMode(26,OUTPUT); 
pinMode(27,OUTPUT); 
pinMode(28,OUTPUT); 
pinMode(29,OUTPUT); 
pinMode(30,OUTPUT);
pinMode(31,OUTPUT);
pinMode(32,OUTPUT); 
pinMode(33,OUTPUT);  

digitalWrite(22,LOW);
digitalWrite(23,LOW);
digitalWrite(24,LOW);
digitalWrite(25,LOW);
digitalWrite(26,LOW);
digitalWrite(27,LOW);
digitalWrite(28,LOW);
digitalWrite(29,LOW);
digitalWrite(30,LOW);
digitalWrite(31,LOW);
digitalWrite(32,LOW);
digitalWrite(33,LOW);


}

void loop() 
{

  if(Serial2.available()>0)
  {
    state= Serial2.read();
  }

  if ( ! mfrc522.PICC_IsNewCardPresent()) // Look for new cards
  {
    return;
  }
 
  if ( ! mfrc522.PICC_ReadCardSerial())  // Select one of the cards
  {
    return;
  }
  uidString = String(mfrc522.uid.uidByte[0]) + " " + String(mfrc522.uid.uidByte[1]) + " " + 
  String(mfrc522.uid.uidByte[2]) + " " + String(mfrc522.uid.uidByte[3]);

  //Serial.println(uidString);
  if (uidString == uidString1) 
  {
  Serial1.write(a);
  Serial3.write(a);
  Product_Id=".MUs.Part:1";
  side="Left";
  Storage_Location_row= "2";
  Storage_Location_coloumn="1";
  Serial.print(",");
  Serial.print(Product_Id);
  Serial.print(",");
  Serial.print(side);
  Serial.print(",");
  Serial.print(Storage_Location_row);
  Serial.print(",");
  Serial.println(Storage_Location_coloumn);
  }
  if (uidString == uidString2) 
  {
  Serial1.write(b);
  Serial3.write(b);
  Product_Id=".MUs.Part:2";
  side="Left";
  Storage_Location_row= "3";
  Storage_Location_coloumn="2";
  Serial.print(",");
  Serial.print(Product_Id);
  Serial.print(",");
  Serial.print(side);
  Serial.print(",");
  Serial.print(Storage_Location_row);
  Serial.print(",");
  Serial.println(Storage_Location_coloumn);
  }
   if (uidString == uidString3) 
  {
  Serial1.write(c);
  Serial3.write(c);
  Product_Id=".MUs.Container:1";
  side="Right";
  Storage_Location_row= "3";
  Storage_Location_coloumn="1";
  Serial.print(",");
  Serial.print(Product_Id);
  Serial.print(",");
  Serial.print(side);
  Serial.print(",");
  Serial.print(Storage_Location_row);
  Serial.print(",");
  Serial.println(Storage_Location_coloumn);
  }
  if (uidString == uidString4) 
  {
  Product_Id=".MUs.Container:1";
  side="Right";
  Storage_Location_row= "2";
  Storage_Location_coloumn="2";
  Serial.print(",");
  Serial.print(Product_Id);
  Serial.print(",");
  Serial.print(side);
  Serial.print(",");
  Serial.print(Storage_Location_row);
  Serial.print(",");
  Serial.println(Storage_Location_coloumn);
  }
  /*
   if (uidString == uidString5) 
  {
   
  Serial1.write(e);
  Serial3.write(e);
  Product_Id=uidString5;
  Storage_Location="column 4 middle rack";
  Status="Stored";
 Serial.print(",");
  Serial.print(Product_Id);
  Serial.print(",");
  Serial.print(side);
  Serial.print(",");
  Serial.print(Storage_Location_row);
  Serial.print(",");
  Serial.println(Storage_Location_coloumn);
  }
  if (uidString == uidString6) 
  {
  Serial1.write(f);
  Serial3.write(f);
  Product_Id=uidString6;
  Storage_Location="column 4 top rack";
  Status="Stored";
  Serial.print(",");
  Serial.print(Product_Id);
  Serial.print(",");
  Serial.print(side);
  Serial.print(",");
  Serial.print(Storage_Location_row);
  Serial.print(",");
  Serial.println(Storage_Location_coloumn);
  }
  */
  if(state==110)
  {
    digitalWrite(22,LOW);
  }
  if(state==111)
  {
    digitalWrite(22,HIGH);
  }
  if(state==130)
  {
    digitalWrite(23,LOW);
  }
  if(state==131)
  {
    digitalWrite(23,HIGH);
  }
  if(state==320)
  {
    digitalWrite(24,LOW);
  }
  if(state==321)
  {
    digitalWrite(24,HIGH);
  }
  if(state==330)
  {
    digitalWrite(25,LOW);
  }
  if(state==331)
  {
    digitalWrite(25,HIGH);
  }
  if(state==420)
  {
    digitalWrite(26,LOW);
  }
  if(state==421)
  {
    digitalWrite(26,HIGH);
  }
  if(state==430)
  {
    digitalWrite(27,LOW);
  }
  if(state==431)
  {
    digitalWrite(27,HIGH);
  }
  }
