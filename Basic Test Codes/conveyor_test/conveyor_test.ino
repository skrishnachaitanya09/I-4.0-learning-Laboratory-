void setup() {
  Serial.begin(9600);
  pinMode(2,INPUT);
  pinMode(3,INPUT);
  pinMode(8,OUTPUT);
  pinMode(9,OUTPUT);
}

void loop() 
{
  int sensor_1=digitalRead(2);
  int sensor_2=digitalRead(3);

  if(sensor_1==1)
  {
     digitalWrite(9,HIGH);
     digitalWrite(8,LOW);
  }
     if(sensor_2==1)
    {
     digitalWrite(8,LOW); 
     digitalWrite(9,LOW);
    }
    
//  
//  Serial.println(sensor_1);
//  Serial.println(sensor_2);
  }
  
