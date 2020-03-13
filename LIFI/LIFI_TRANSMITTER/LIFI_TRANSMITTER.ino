#define LASERPIN 2
#define activpin 3
void setup() {
  // put your setup code here, to run once:
  pinMode(LASERPIN, OUTPUT);
  pinMode(activpin, INPUT);

}

void loop() {
  // 10011010
  int key[]={1,0,1,1,1,0,1,0};
  int bits[] = {1,0,0,1,1,0,1,0};
  
  
  //start bit
// digitalWrite(LASERPIN, HIGH);
// delay(100);
// digitalWrite(LASERPIN, LOW);
// delay(100);
// digitalWrite(LASERPIN, HIGH);
// delay(100);
// digitalWrite(LASERPIN, LOW);
if(digitalRead(activpin)== HIGH)
{
 for (int i = 0; i < 8; i++) 
  {
    digitalWrite(LASERPIN, key[i]);
    delay(100);
  }

  for (int j = 0; j< 8; j++) 
  {
    digitalWrite(LASERPIN, bits[j]);
    delay(100);
  }
}
//  digitalWrite(LASERPIN, LOW);
//
//  delay(500);
}
