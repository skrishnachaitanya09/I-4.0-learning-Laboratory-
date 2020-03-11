#define SOLARPIN A0
#define THRESHOLD 100

int ambientReading = 0;

void setup() {
  pinMode(SOLARPIN, INPUT);
  Serial.begin(9600);

  ambientReading = analogRead(SOLARPIN);
}

void loop() {
// Serial.println(ambientReading);
  int reading = analogRead(SOLARPIN);
  int bits[8];
  int startbit[4];
  int key[] = {1,0,1,0};
  int p = 0;

//  // Listening for the start bit
 if (reading > ambientReading + THRESHOLD) {
 
  for (int j = 0; j < 4; j++){
    if (analogRead(SOLARPIN) > ambientReading + THRESHOLD) {
        
        startbit[j] = 1;
      }
      else {
        startbit[j] = 0;
      }
      delay(100);
    }}
  // compare startbit with key

  for (int k = 0; k < 8; k++){
     
       if(startbit[k] == key[k])
       p = 1;
       break;       
     
     }

     if (reading > ambientReading + THRESHOLD && p ==1){
    //delay(500);
    for (int i = 0; i<8 ; i++) {
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
  