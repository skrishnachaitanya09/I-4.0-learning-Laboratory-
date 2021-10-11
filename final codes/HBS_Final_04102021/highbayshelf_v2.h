

bool end1;
bool storingCompleted = false;
int storageState = 0;

int sc2sens = 4; //Check and delete, unused pin
int sc3sens = 10; //Sensor on the First Conveyor in Storage
int srbsens = 44; //Sensor on the Storage-Retrieval Belt
int storage = 5;
int dsens = 28;
int slt_sw = 27; 

int udsrrlt_sw[3] = {29,31,33}; //Up and down Belt Right Side Switches, starting from bottom
int rlsrlt_sw[3] = {2,35,37}; //Storage-Retrieval Belt Switches from Right to Left
int hbslt_sw[4] = {41,43,45,47}; //High bay switches, from wall to source
int udsrllt_sw[3] = {38,48,40}; //Up and down Belt Right Side Switches, starting from bottom

void store(int row, int column)
{
     Serial1.write(0xa3);
    storingCompleted = false;
    while(!digitalRead(sc3sens)) {
      Serial.println("Second & Third belt forward");
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    }
  

  while (digitalRead(rlsrlt_sw[0]))
  {

    Serial.println("All belts stop. Bring SRB towards source");
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(30, LOW);
    digitalWrite(32, HIGH);
  }
  while(digitalRead(udsrrlt_sw[1]))
  {
    Serial.println("SRB stop. Third Belt forward");
    digitalWrite(30, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    while (digitalRead(48)) {
      digitalWrite(24, LOW);
      digitalWrite(26, HIGH);
    }
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);

  }
  
  while(digitalRead(rlsrlt_sw[1]))
  {
    Serial.println("SRB BACKWARD");
    digitalWrite(30, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
  }

  //Until here, common for storage of both A and B

  while(digitalRead(udsrrlt_sw[column]))
  {
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(24, LOW);
    Serial.println("MATERIAL IS INSIDE STOP ALL MOTORS & Move ASRS UP");
  }

  while(digitalRead(hbslt_sw[row])) 
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, LOW);
    Serial.println("STOP MOVING ASRS UP AND MOVE IT TOWARDS SHELF");
  }


  while(digitalRead(rlsrlt_sw[0]))
  {
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, LOW);
    Serial.println("STOP AT SHELF AND MOVE THE SRB TOWARDS SHELF");
  }

  while(digitalRead(udsrllt_sw[column]))
  {
    digitalWrite(26, LOW);
    digitalWrite(24, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(30, LOW);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    Serial.println("SRB AT CORNER AND MOVE THE BELT DOWNWARDS ");
  }

  while(digitalRead(rlsrlt_sw[1]))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(30, HIGH);
    Serial.println("MOVE BACK  S & R BELT AFTER STORING MATERIAL "); //Recent changes here
  }

  while(digitalRead(udsrrlt_sw[0]))
  {
    digitalWrite(26, LOW);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    Serial.println("STOP S & R BELT AFTER STORING MATERIAL AND MOVE BELT DOWNWARDS ");
  }

  while(digitalRead(hbslt_sw[0]))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, LOW);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    Serial.println("BRING BACK SRB TO INITIAL POSITION ");
    storageState = 1;
  }

  if (storageState == 1)
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    storageState = 0;
    storingCompleted = true;
    Serial.println("INITIAL POSITION");
  }
}


void storeL(int row, int column)
{
  
     Serial1.write(0xa3);
    storingCompleted = false;
    while(!digitalRead(sc3sens)) {
      Serial.println("Second & Third belt forward");
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, LOW);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    }
  

  while (digitalRead(rlsrlt_sw[0]))
  {

    Serial.println("All belts stop. Bring SRB towards source");
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(30, LOW);
    digitalWrite(32, HIGH);
  }
  while(digitalRead(udsrrlt_sw[1]))
  {
    Serial.println("SRB stop. Third Belt forward");
    digitalWrite(30, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, LOW);
    while (digitalRead(48)) {
      digitalWrite(24, LOW);
      digitalWrite(26, HIGH);
    }
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);

  }
  
  while(digitalRead(rlsrlt_sw[1]))
  {
    Serial.println("SRB BACKWARD");
    digitalWrite(30, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(6, HIGH);
    digitalWrite(7, HIGH);
    digitalWrite(8, HIGH);
    digitalWrite(9, HIGH);
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
  }

  //Until here, common for storage of both A and B

  while(digitalRead(udsrrlt_sw[column]))
  {
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(24, LOW);
    Serial.println("MATERIAL IS INSIDE STOP ALL MOTORS & Move ASRS UP");
  }

  while(digitalRead(hbslt_sw[row])) 
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, LOW);
    Serial.println("STOP MOVING ASRS UP AND MOVE IT TOWARDS SHELF");
  }


  while(digitalRead(rlsrlt_sw[2]))
  {
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, LOW);
    Serial.println("STOP AT SHELF AND MOVE THE SRB TOWARDS SHELF");
  }

  while(digitalRead(udsrllt_sw[column]))
  {
    digitalWrite(26, LOW);
    digitalWrite(24, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(30, LOW);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    Serial.println("SRB AT CORNER AND MOVE THE BELT DOWNWARDS ");
  }

  while(digitalRead(rlsrlt_sw[1]))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(30, HIGH);
    Serial.println("MOVE BACK  S & R BELT AFTER STORING MATERIAL "); //Recent changes here
  }

  while(digitalRead(udsrrlt_sw[0]))
  {
    digitalWrite(26, LOW);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    Serial.println("STOP S & R BELT AFTER STORING MATERIAL AND MOVE BELT DOWNWARDS ");
  }

  while(digitalRead(hbslt_sw[0]))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, LOW);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    Serial.println("BRING BACK SRB TO INITIAL POSITION ");
    storageState = 1;
  }

  if (storageState == 1)
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    storageState = 0;
    storingCompleted = true;
    Serial.println("INITIAL POSITION");
  }
}

/*Retrieving codes..........................
 * .........................................
 */

void retrieve(int row, int column)
{
  int sc2sens = digitalRead(4); //pin4
  int sc3sens = digitalRead(10); //pin10
  int srbsens = digitalRead(44); //pin44
  int storage = digitalRead(5);
  int dsens = digitalRead(28);
  int slt_sw = digitalRead(27); //27

  while (hbslt_sw[row] == 1)
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, LOW);
    Serial.println("MOVE ASRS TOWARDS SHELF");
  }

  while(udsrllt_sw[column] == 1)
  {
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(24, LOW);
    Serial.println("MATERIAL IS NOT INSIDE STOP ALL MOTORS & Move ASRS UP");
  }

  while(rlsrlt_sw[0] == 1)
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, LOW);
    Serial.println("stop the system at column and move the belt outside");
  }

  while(udsrrlt_sw[column] == 1)
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, LOW);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    Serial.println("lift the belt up");
  }

  while(rlsrlt_sw[1] == 1)
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(30, HIGH);
    Serial.println("material picked and going inside");
  }

  while(udsrrlt_sw[0] == 1)
  {
    digitalWrite(26, LOW);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    Serial.println("MATERIAL INSIDE!! STOP");
  }

  while(hbslt_sw[0] == 1)
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, LOW);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    Serial.println("system coming towards destination");
  }

  while(rlsrlt_sw[2] == 0)
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(30, HIGH);
    Serial.println("moving towards destination");
  }

  if ((udsrrlt_sw[1] == 0) && (srbsens == 1) && (slt_sw == 0) && (rlsrlt_sw[2] == 0) && (dsens == 0))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    digitalWrite(22, HIGH);
    digitalWrite(23, LOW);
    digitalWrite(42, HIGH);
    digitalWrite(46, LOW);
    Serial.println("sending material outside");
    while (digitalRead(38)) {
      digitalWrite(26, LOW);
      digitalWrite(24, HIGH);
    }
    digitalWrite(24, HIGH);
    digitalWrite(26, HIGH);

  }
  
}



void retrieveL13()
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
  int rlsrlt_sw1 = digitalRead(2); //2 right
  int rlsrlt_sw2 = digitalRead(35); //35 middle
  int rlsrlt_sw3 = digitalRead(37); //37 left
  int hbslt_sw1 = digitalRead(41); //41 towards wall
  int hbslt_sw2 = digitalRead(43); //43
  int hbslt_sw3 = digitalRead(45); //45
  int hbslt_sw4 = digitalRead(47); //47 towards source and destination
  int udsrllt_sw1 = digitalRead(38); //38 up down belt left side down switch
  int udsrllt_sw2 = digitalRead(48); //48 up down belt left side middle switch
  int udsrllt_sw3 = digitalRead(40); //40 up down belt left side top switch
  if ((rlsrlt_sw2 == 0) && (srbsens == 1)  && (hbslt_sw1 == 1) && (udsrllt_sw3 == 1))
  {
    digitalWrite(11, HIGH);
    digitalWrite(12, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    digitalWrite(26, HIGH);
    digitalWrite(24, LOW);
    Serial.println("MATERIAL IS NOT INSIDE STOP ALL MOTORS & Move ASRS UP");
  }

  if ((udsrllt_sw3 == 0) && (srbsens == 1) && (hbslt_sw1 == 1) && (rlsrlt_sw2 == 0))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, LOW);
    Serial.println("STOP MOVING ASRS UP AND MOVE IT TOWARDS SHELF");
  }

  if ((udsrllt_sw3 == 0) && (srbsens == 1) && (hbslt_sw1 == 0) && (rlsrlt_sw2 == 0))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(30, HIGH);
    Serial.println("stop the system at 3 column and move the belt outside");
  }
  if ((udsrllt_sw3 == 0) && (srbsens == 1) && (hbslt_sw1 == 0) && (rlsrlt_sw3 == 0))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, LOW);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    Serial.println("lift the belt up");
  }
  if ((udsrrlt_sw3 == 0) && (srbsens == 1) && (hbslt_sw1 == 0) && (rlsrlt_sw3 == 0))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, LOW);
    Serial.println("material picked and going inside");
  }
  if ((udsrrlt_sw3 == 0) && (srbsens == 0) && (hbslt_sw1 == 0) && (rlsrlt_sw2 == 0))
  {
    digitalWrite(26, LOW);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    Serial.println("material inside!! stop");
  }
  if ((udsrrlt_sw3 == 0) && (hbslt_sw1 == 0) && (rlsrlt_sw1 == 0))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(30, HIGH);
    Serial.println("Too far, coming back");
  }
  if ((udsrrlt_sw2 == 0) && (srbsens == 0) && (hbslt_sw1 == 0) && (rlsrlt_sw2 == 0))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, LOW);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    Serial.println("system coming towards destination");
  }
  if ((udsrrlt_sw2 == 0) && (srbsens == 0) && (slt_sw == 0) && (rlsrlt_sw2 == 0))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, LOW);
    digitalWrite(30, HIGH);
    Serial.println("moving towards destination");
  }
  if ((udsrrlt_sw2 == 0) && (srbsens == 1) && (slt_sw == 0) && (rlsrlt_sw3 == 0) && (dsens == 0))
  {
    digitalWrite(26, HIGH);
    digitalWrite(24, HIGH);
    digitalWrite(36, HIGH);
    digitalWrite(34, HIGH);
    digitalWrite(32, HIGH);
    digitalWrite(30, HIGH);
    digitalWrite(22, HIGH);
    digitalWrite(23, LOW);
    digitalWrite(42, HIGH);
    digitalWrite(46, LOW);
    Serial.println("sending material outside");
    while (digitalRead(38)) {
      digitalWrite(26, LOW);
      digitalWrite(24, HIGH);
    }
    digitalWrite(24, HIGH);
    digitalWrite(26, HIGH);
    
  }
}
