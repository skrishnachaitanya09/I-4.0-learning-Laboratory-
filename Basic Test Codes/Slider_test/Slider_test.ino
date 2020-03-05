void setup() {
  pinMode(2,INPUT);
  pinMode(3,INPUT_PULLUP);
  pinMode(4,INPUT_PULLUP);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
  pinMode(10,OUTPUT);
  pinMode(11,OUTPUT);
  Serial.begin(9600);

}

void loop() {
  // put your main code here, to run repeatedly:
//  Serial.println(digitalRead(2));
//  Serial.println(digitalRead(3));
//  Serial.println(digitalRead(4));
//    digitalWrite(8,HIGH);
//    digitalWrite(9,LOW);

    digitalWrite(10,HIGH);
    digitalWrite(11 ,LOW);
//    
 
  Serial.println("");
  
}
