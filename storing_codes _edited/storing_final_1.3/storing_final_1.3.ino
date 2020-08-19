//SENSORS

int sc2sens;         //source conveyor2 sensor
int sc3sens;         //source conveyor3 sensor
int srbsens;         // storage and retrieval belt sensor
int dsens;           // destination sensor
int storage;

// LIMIT SWITCHES
int slt_sw;          // source side limit switch
int udsrrlt_sw1;     // ASRS belt right side bottom switch
int udsrrlt_sw2;     //ASRS belt right side middle switch
int udsrrlt_sw3;     //ASRS belt right side upper switch
int rlsrlt_sw1;      // storage and retrieval belt right side limit switch
int rlsrlt_sw2;      //storage and retrieval belt middle limit switch
int rlsrlt_sw3;      //storage and retrieval belt left side limit switch
int hbslt_sw1;       //41 high bay shelf first limit switch
int hbslt_sw2;       //43 high bay shelf second limit switch
int hbslt_sw3;       //45 high bay shelf third limit switch
int hbslt_sw4;       //47 high bay shelf fourth limit switch(towards source and destination)
int udsrllt_sw1;     //38 ASRS belt left side bottom switch
int udsrllt_sw2;     //48 ASRS belt left side middle switch
int udsrllt_sw3;     //40 ASRS belt left side top switch


// MOTORS

int sc2mp = 8;       // source conveyor2: motor +
int sc2mn = 9;       // source conveyor2: motor -
int sc3mp = 11;      // source conveyor3: motor +
int sc3mn = 12;      // source conveyor3: motor -
int srrlmp = 30;     // storage and retrieval belt: motor +
int srrlmn = 32;     // storage and retrieval belt: motor -
int srudmp = 24;     // ASRS up and down motor +
int srudmn = 26;     // ASRS up and down motor -
int srtfmp = 34;     // ASRS forward and backward motor +
int srtfmn = 36;     // ASRS forward and backward motor -
int dm1p = 22;       // destination conveyor1: motor +
int dm1n = 23;       // destination conveyor1: motor -
int dm2p = 42;       // destination conveyor2: motor +
int dm2n = 25;       // destination conveyor2: motor -

void setup()
{
  Serial.begin(9600);


  pinMode(2, INPUT_PULLUP);
  pinMode(3, INPUT_PULLUP);
  pinMode(4, INPUT);
  pinMode(10, INPUT);
  pinMode(46, INPUT);
  pinMode(28, INPUT);
  pinMode(5, INPUT);

  pinMode(27, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(41, INPUT_PULLUP);
  pinMode(43, INPUT_PULLUP);
  pinMode(45, INPUT_PULLUP);
  pinMode(47, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  pinMode(48, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);

  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(11, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(30, OUTPUT);
  pinMode(32, OUTPUT);
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);
  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT);
  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT);
  pinMode(42, OUTPUT);
  pinMode(25, OUTPUT);



  digitalWrite(6, HIGH);
  digitalWrite(7, HIGH);
  digitalWrite(8, HIGH);
  digitalWrite(9, HIGH);
  digitalWrite(11, HIGH);
  digitalWrite(12, HIGH);
  digitalWrite(24, HIGH);
  digitalWrite(26, HIGH);
  digitalWrite(30, HIGH);
  digitalWrite(32, HIGH);
  digitalWrite(34, HIGH);
  digitalWrite(36, HIGH);
  digitalWrite(22, HIGH);
  digitalWrite(23, HIGH);
  digitalWrite(42, HIGH);
  digitalWrite(25, HIGH);
}
void loop()
{



  int sc2sens = digitalRead(4); //pin4
  int sc3sens = digitalRead(10); //pin10
  int srbsens = digitalRead(44); //pin44
  int storage = digitalRead(5);
  int dsens = digitalRead(28);
  int slt_sw = digitalRead(27); //27
  int udsrrlt_sw1 = digitalRead(29); //29 up down belt right side down switch
  int udsrrlt_sw2 = digitalRead(31); //31 up down belt right side middle switch
  int udsrrlt_sw3 = digitalRead(33); //33 up down belt right side up switch
  int rlsrlt_sw1 = digitalRead(2); //39 right
  int rlsrlt_sw2 = digitalRead(35); //35 middle
  int rlsrlt_sw3 = digitalRead(37); //37 left
  int hbslt_sw1 = digitalRead(41); //41 towards wall
  int hbslt_sw2 = digitalRead(43); //43
  int hbslt_sw3 = digitalRead(45); //45
  int hbslt_sw4 = digitalRead(47); //47 towards source and destination
  int udsrllt_sw1 = digitalRead(38); //38 up down belt left side down switch
  int udsrllt_sw2 = digitalRead(48); //48 up down belt left side middle switch
  int udsrllt_sw3 = digitalRead(40); //40 up down belt left side top switch

if( (sc2sens==0) && (sc3sens==1) &&(srbsens==1) )
{
  Serial.println("First belt forward");
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW); 
}
if( (sc2sens==0) && (sc3sens==1) &&(srbsens==1))
{
  Serial.println("First & Second belt forward");
  digitalWrite(6,HIGH);
  digitalWrite(7,LOW); 
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW); 
}
if((sc2sens==1) && (sc3sens==1) &&(srbsens==1))
{
  Serial.println("Second & Third belt forward");
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH); 
  digitalWrite(8,HIGH);
  digitalWrite(9,LOW);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);
  
}

if((sc2sens==0) && (sc3sens==0) && (srbsens==1)&& (rlsrlt_sw1==1))
{
//  Serial.println("All belts stop");
  Serial.println("All belts stop. Bring SRB towards source");
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH); 
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);
  digitalWrite(30,LOW);
  digitalWrite(32,HIGH);
  Serial.println(rlsrlt_sw1);
}
if( (sc2sens==0) && (sc3sens==0) && (srbsens==1) && (rlsrlt_sw1==0))
{
  Serial.println("SRB stop. Third Belt forward");
  digitalWrite(30,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH); 
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,LOW);

 
}
if((sc2sens==0) && (sc3sens==1) && (srbsens==1) && (rlsrlt_sw1==0) && (rlsrlt_sw2==1) && (hbslt_sw1==1))
{
  Serial.println("SRB BACKWARD");
  digitalWrite(30,HIGH);
  digitalWrite(32,LOW);
  digitalWrite(6,HIGH);
  digitalWrite(7,HIGH); 
  digitalWrite(8,HIGH);
  digitalWrite(9,HIGH);
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH);

 

}

if((rlsrlt_sw2==0) && (srbsens==0)  && (hbslt_sw1==1) && (udsrrlt_sw3==1))
{
  digitalWrite(11,HIGH);
  digitalWrite(12,HIGH); 
  digitalWrite(32,HIGH);
  digitalWrite(30,HIGH);
  digitalWrite(26,HIGH);
  digitalWrite(24,LOW);
  Serial.println("MATERIAL IS INSIDE STOP ALL MOTORS & Move ASRS UP");
}

if((udsrrlt_sw3==0) && (srbsens==0) && (hbslt_sw1==1) &&(udsrllt_sw1==1))
{
  digitalWrite(26,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(36,HIGH);
  digitalWrite(34,LOW);
  Serial.println("STOP MOVING ASRS UP AND MOVE IT TOWARDS SHELF");
}

if((hbslt_sw1==0)&& (srbsens==0) && (udsrrlt_sw3==0))
{
  digitalWrite(36,HIGH);
  digitalWrite(34,HIGH);
  digitalWrite(26,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(30,LOW);
  Serial.println("STOP AT SHELF AND MOVE THE SRB TOWARDS SHELF");
  
}

if((hbslt_sw1==0) && (rlsrlt_sw1==0) && (udsrrlt_sw3==0) && (srbsens==1))
{
  digitalWrite(26,LOW);
  digitalWrite(24,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(30,HIGH);
  digitalWrite(36,HIGH);
  digitalWrite(34,HIGH);
  Serial.println("SRB AT CORNER AND MOVE THE BELT DOWNWARDS ");
}
if((hbslt_sw1==0) && (rlsrlt_sw1==0) && (udsrllt_sw3==0) && (udsrrlt_sw3==1))
{
  digitalWrite(26,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(36,HIGH);
  digitalWrite(34,HIGH);
  digitalWrite(32,LOW);
  digitalWrite(30,HIGH);
  Serial.println("MOVE BACK  S & R BELT AFTER STORING MATERIAL ");
}
if((hbslt_sw1==0) && (rlsrlt_sw2==0) && (udsrllt_sw3==0) && (srbsens==1))
{
  digitalWrite(26,LOW);
  digitalWrite(24,HIGH);
  digitalWrite(36,HIGH);
  digitalWrite(34,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(30,HIGH);
  Serial.println("STOP S & R BELT AFTER STORING MATERIAL AND MOVE BELT DOWNWARDS ");
}
if((hbslt_sw1==0) && (rlsrlt_sw2==0) && (udsrllt_sw1==0) && (srbsens==1))
{
  digitalWrite(26,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(36,LOW);
  digitalWrite(34,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(30,HIGH);
  Serial.println("BRING BACK SRB TO INITIAL POSITION ");
}
if((udsrllt_sw1==0) && (srbsens==1) && (slt_sw==0) &&(rlsrlt_sw2==0) && (sc3sens==1))
{
  digitalWrite(26,HIGH);
  digitalWrite(24,HIGH);
  digitalWrite(36,HIGH);
  digitalWrite(34,HIGH);
  digitalWrite(32,HIGH);
  digitalWrite(30,HIGH);
  Serial.println("INITIAL POSITION");
}
}
