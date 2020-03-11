#define LASERPIN 2

  int startbit[] = {1,0,1,0,1,0,1,0};
  int delimiter[] = {0,1,1,1,1,1,1,0};

  int data[] = {1,0,0,1,1,0,1,0};

void setup() {
 
  pinMode(LASERPIN, OUTPUT);

}

void loop() {

  for (int i = 0; i < 8; i++) {
    digitalWrite(LASERPIN, startbit[i]);    // transmission of startbits
    delay(100);
  }
  digitalWrite(LASERPIN, LOW);
  delay(300);
  
 
  for (int i = 0; i < 8; i++) {
    digitalWrite(LASERPIN, delimiter[i]);  // transmission of delimiter at the start of data transmission
    delay(100);
  }
  digitalWrite(LASERPIN, LOW);
  delay(300);


   for (int i = 0; i < 8; i++) {
    digitalWrite(LASERPIN, data[i]);    // transmission of data
    delay(100);
  }
  digitalWrite(LASERPIN, LOW);
  delay(500);


   for (int i = 0; i < 8; i++) {
    digitalWrite(LASERPIN, delimiter[i]);    // transmission of delimiter at the end of data transmission
    delay(100);
  }
  digitalWrite(LASERPIN, LOW);
  delay(3000);
}
