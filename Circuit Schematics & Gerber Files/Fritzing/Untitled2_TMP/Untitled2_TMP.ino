void setup()
{
pinMode(8,OUTPUT);
pinMode(9,OUTPUT);
Serial.begin(9600);
}
void loop()
{
digitalWrite(8,HIGH);
digitalWrite(9,LOW);
Serial.println("ON");
delay(1000);
digitalWrite(8,LOW);
digitalWrite(9,LOW);
Serial.println("OFF");
delay(1000);
}