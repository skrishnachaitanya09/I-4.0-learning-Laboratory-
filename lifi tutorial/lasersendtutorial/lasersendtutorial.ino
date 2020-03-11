#define LASERPIN 2

void setup() {
  // put your setup code here, to run once:
  pinMode(LASERPIN, OUTPUT);

}

void loop() {
  // 01011010
  int bits[] = {LOW, HIGH, LOW, HIGH, HIGH, LOW, HIGH, LOW};
  
 // start bit
  digitalWrite(LASERPIN, HIGH);
  delay(500);
  digitalWrite(LASERPIN, LOW);


  for (int i = 0; i < 8; i++) {
    digitalWrite(LASERPIN, bits[i]);
    delay(200);
  }

  digitalWrite(LASERPIN, LOW);

  delay(5000);
}
