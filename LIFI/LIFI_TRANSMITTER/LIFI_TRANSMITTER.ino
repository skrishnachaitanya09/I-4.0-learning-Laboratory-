#define LASERPIN 2

void setup() {
  // put your setup code here, to run once:
  pinMode(LASERPIN, OUTPUT);

}

void loop() {
  // 10011010
  int bits[] = {1,0,0,1,1,0,1,0};
  
  //start bit
 digitalWrite(LASERPIN, HIGH);
 delay(100);
 digitalWrite(LASERPIN, LOW);
 delay(100);
 digitalWrite(LASERPIN, HIGH);
 delay(100);
 digitalWrite(LASERPIN, LOW);


  for (int i = 0; i < 8; i++) {
    digitalWrite(LASERPIN, bits[i]);
    delay(200);
  }

  digitalWrite(LASERPIN, LOW);

  delay(500);
}
