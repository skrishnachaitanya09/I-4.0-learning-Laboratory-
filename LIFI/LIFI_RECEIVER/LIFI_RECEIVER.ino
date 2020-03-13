#define SOLARPIN A0
#define THRESHOLD 100

int ambientReading = 0;

void setup() {
  pinMode(SOLARPIN, INPUT);
  Serial.begin(9600);

  ambientReading = analogRead(SOLARPIN);
}

void loop() 
{
// Serial.println(ambientReading);
  int reading = analogRead(SOLARPIN);
   //Serial.println(reading);
  int bits[8];
  int startbit[8];
  int key[]={1,0,1,1,1,0,1,0};
  int p = 0;

//  // Listening for the start bit
  int j=0;
  while(j<8) 
  {
    if (analogRead(SOLARPIN) > ambientReading + THRESHOLD) 
     {
      startbit[j] = 1;
     }
     else 
     {
       startbit[j] = 0;
     }
     if(startbit[j]==key[j]) 
     {
      j++;
     }
     else 
     {
      j=0;
     }
     delay(100);
  }
 if(j==8) 
 {
 Serial.println("Key matched");
 Serial.println("Key is ");
 for(int i =0;i<8;i++) 
 {
  Serial.print(startbit[i]);
 }
 Serial.println("Data is ");
 for(int i =0;i<8;i++) 
 {
      if (analogRead(SOLARPIN) > ambientReading + THRESHOLD) 
      {
        
        bits[i] = 1;
      }
      else 
      {
        bits[i] = 0;
      }
      delay(100);
    
  Serial.print(bits[i]);
 }
 }
 }

//  for (int j = 0; j < 8; j++){
//    if (analogRead(SOLARPIN) > ambientReading + THRESHOLD) {
//        
//        startbit[j] = 1;
//      }
//      else {
//        startbit[j] = 0;
//      }
//      delay(100);
//    }}
  // compare startbit with key

//  for (int k = 0; k < 8; k++)
//    {
//     
//       if(startbit[k] == key[k])
//       
//       {
//        p = 1;
//       }
//       else
//       {
//        p=0;
//        break;
//       }
//              
//     
//     }

//     if (reading > ambientReading + THRESHOLD && p ==1){
//    //delay(500);
//    for (int i = 0; i<8 ; i++) {
//      if (analogRead(SOLARPIN) > ambientReading + THRESHOLD) {
//        
//        bits[i] = 1;
//      }
//      else {
//        bits[i] = 0;
//      }
//      delay(100);
//    } 
//      for (int i = 0; i < 8; i++) {
//       Serial.print(bits[i]);
//    }
//    Serial.println("");
//    
//    }

  
  
