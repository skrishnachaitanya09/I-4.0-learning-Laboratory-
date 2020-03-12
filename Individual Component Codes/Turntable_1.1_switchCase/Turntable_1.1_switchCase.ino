#define SIGNALPIN 2
#define SENSORPIN 3
#define LEDA 4
#define LEDB 5
#define LEDC 6
#define LDRA 7
#define LDRB 8
#define LDRC 9
#define conmotpos 10
#define conmotneg 11

void setup() {
  pinMode(SIGNALPIN,INPUT);
  pinMode(SENSORPIN,INPUT);
  pinMode(LDRA,INPUT);
  pinMode(LDRB,INPUT);
  pinMode(LDRC,INPUT);
  pinMode(LEDA,OUTPUT);
  pinMode(LEDB,OUTPUT);
  pinMode(LEDC,OUTPUT);
  pinMode(conmotpos,OUTPUT);
  pinMode(conmotneg,OUTPUT);
  int ambientReadingA = analogRead(LDRA);
}

void loop() {
  boolean signalValue = digitalRead(SIGNALPIN);
  boolean sensor = digitalRead(SENSORPIN); //testing

   switch(signalValue)
   {
    case 1: 
      if(reading<ambientReadingA+THRESHOLD) //Product requested when TT in default position
      {
        //turn towards A
        digitalWrite(LEDA,HIGH);
      }
      if(reading>ambientReadingA+THRESHOLD) //Product reached end of source conveyor
      {
        digitalWrite(conmotpos,HIGH);
        digitalWrite(conmotneg,LOW);
        if(sensor == HIGH)
        {
          digitalWrite(conmotpos,LOW);
          //turn towards default
          digitalWrite(conmotpos,HIGH);
          digitalWrite(conmotneg,LOW);
        }
      }
      break;
//
//     case B:
//        if(signalValue = B && reading<ambientReadingB+THRESHOLD)
//        {
//          //turn towards B
//          digitalWrite(LEDB,HIGH);
//        }
//        if(signalValue = B && reading>ambientReadingB+THRESHOLD)
//        {
//          digitalWrite(conmotpos,HIGH);
//          digitalWrite(conmotneg,LOW);
//          if(sensor == HIGH)
//          {
//            digitalWrite(conmotpos,LOW);
//            //turn towards default
//            digitalWrite(conmotpos,HIGH);
//            digitalWrite(conmotneg,LOW);
//          }
//        }
//        break;
//        
//     case C:
//        if(signalValue = C && reading<ambientReadingC+THRESHOLD)
//        {
//          //turn towards C
//          digitalWrite(LEDB,HIGH);
//        }
//        if(signalValue = C && reading>ambientReadingC+THRESHOLD)
//        {
//          digitalWrite(conmotpos,HIGH);
//          digitalWrite(conmotneg,LOW);
//          if(sensor == HIGH)
//          {
//            digitalWrite(conmotpos,LOW);
//            //turn towards default
//            digitalWrite(conmotpos,HIGH);
//            digitalWrite(conmotneg,LOW);
//          }
//        }
//        break;
//          
   }

}
