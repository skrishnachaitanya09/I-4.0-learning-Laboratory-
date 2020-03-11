#define SOLARPIN A0
#define THRESHOLD 100

int ambientReading = 0;

void setup() {
  pinMode(SOLARPIN, INPUT);
  Serial.begin(9600);

  ambientReading = analogRead(SOLARPIN);
}

void loop() {

  int reading = analogRead(SOLARPIN);
  int bits[8];

//   Listening for the start bit
  if (reading > ambientReading + THRESHOLD) {
    for (int i = 0; i < 8; i++) {
      if (analogRead(SOLARPIN) > ambientReading + THRESHOLD) {
        bits[i] = 1;
      }
      else {
        bits[i] = 0;
      }
      delay(200);
    }

    for (int i = 0; i < 8; i++) {
      Serial.print(bits[i]);
    }
    Serial.println("");
    
  }
}
