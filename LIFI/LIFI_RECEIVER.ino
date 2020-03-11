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
  int data[8];
  int startbyte[8];
  int delimiter[8];
 // int delimiterkey[] = {0,1,1,1,1,1,1,0};
  int startkey[] = {1,0,1,0,1,0,1,0};
 
  int p = 0;
  int q = 0;
  int r = 0;
 // Serial.println(reading);
// Listening for the start bit
 if (reading > ambientReading + THRESHOLD) {
 
  for (int j = 0; j < 8; j++){
    if (analogRead(SOLARPIN) > ambientReading + THRESHOLD) {
        
        startbyte[j] = 1;
      }
      else {
        startbyte[j] = 0;
        
      }
      delay(200);
    }

    for(int j=0; j<8; j++)
    {
      Serial.print(startbyte[j]);
    }
       Serial.println("");
  // compare startbyte with key

  for (int k = 0; k < 8; k++){
     
       if(startbyte[k] == startkey[k]) 
       p = 1;
       else
       {
       p=0;
       Serial.println("Not matched");
       break;
       }
     }
     if(p == 1){Serial.println("Start Byte Detected");}
     }
// Listening for delimiter
  if(p == 1) {
    
  for (int j = 0; j < 8; j++){
    if (analogRead(SOLARPIN) > ambientReading + THRESHOLD) {
        
        delimiter[j] = 1;
      }
      else {
        delimiter[j] = 0;
      }
      delay(100);
    }
  // compare delimiter with key

  for (int k = 0; k < 8; k++){
     
       if(delimiter[k] == delimiterkey[k])
       {
        q = 1;
       }
       else {
       q = 0;
       break;
       }
     }
     if(q == 1){Serial.println("Delimiter Byte Detected");};
  }
// Listening for data
     if (p*q == 1){
    
    for (int i = 0; i<8 ; i++) {
      if (analogRead(SOLARPIN) > ambientReading + THRESHOLD) {
        
        data[i] = 1;
      }
      else {
        data[i] = 0;
      }
      delay(100);
    } 

    for (int k = 0; k < 8; k++){
     
       if(data[k] == delimiterkey[k])
       r = 1;
       
       else
       {
        r = 0;
        break;
       }
     }
    switch(r)
    {
    case 1: Serial.println("Delimiter Byte Detected");
    break;
    
    case 0:   {
      for (int i = 0; i < 8; i++) {
    
       Serial.print(data[i]);
    }
    Serial.println("");
    break;
    }
    }
    }   
  }
