#include <EEPROM.h>
#include "highbayshelf.h"

uint8_t source;
char incomingBluetoothMessage;
int state;
int ack;
bool bluetoothRequest;
int addrA = 0;
int addrB = addrA + 1;
byte countA;
byte countB;

void setup() {


  pinMode(3, INPUT);
  pinMode(4, INPUT);
  pinMode(10, INPUT);
  pinMode(46, INPUT);
  pinMode(28, INPUT);
  pinMode(5, INPUT);


  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT); // HIGH forward - first conveyor from Production
  pinMode(9, OUTPUT);

  pinMode(11, OUTPUT); //HIGH forward - second conveyor from Production
  pinMode(12, OUTPUT);

  pinMode(22, OUTPUT);
  pinMode(23, OUTPUT); // HIGH forward - second conveyor from Dispatch

  pinMode(30, OUTPUT); // HIGH forward - center conveyor
  pinMode(32, OUTPUT);

  pinMode(42, OUTPUT); // HIGH turntable towards Dispatch
  pinMode(25, OUTPUT);

  pinMode(34, OUTPUT);
  pinMode(36, OUTPUT); // High towards storage columns
  pinMode(24, OUTPUT);
  pinMode(26, OUTPUT);

  // dispatch turntable
  pinMode(16, OUTPUT); //ground for switch
  pinMode(17, OUTPUT); //ground for switch
  pinMode(3, OUTPUT); //motor high towards dispatch
  pinMode(13, OUTPUT); //motor
  pinMode(20, INPUT_PULLUP); //near dispatch
  pinMode(21, INPUT_PULLUP); //near storage

  digitalWrite(16, LOW);
  digitalWrite(17, LOW);

  Serial.begin(9600);
  Serial1.begin(9600);
  Serial2.begin(9600);
  Serial3.begin(9600);

  pinMode(27, INPUT_PULLUP);
  pinMode(29, INPUT_PULLUP);
  pinMode(31, INPUT_PULLUP);
  pinMode(33, INPUT_PULLUP);
  pinMode(2, INPUT_PULLUP);
  pinMode(35, INPUT_PULLUP);
  pinMode(37, INPUT_PULLUP);
  pinMode(41, INPUT_PULLUP);
  pinMode(43, INPUT_PULLUP);
  pinMode(45, INPUT_PULLUP);
  pinMode(47, INPUT_PULLUP);
  pinMode(38, INPUT_PULLUP);
  pinMode(48, INPUT_PULLUP);
  pinMode(40, INPUT_PULLUP);
  pinMode(39, INPUT_PULLUP);


  state = 0;
  countA = EEPROM.read(addrA);
  countB = EEPROM.read(addrB);


  //      while (digitalRead(21)) {
  //        digitalWrite(42, HIGH);
  //        digitalWrite(25, LOW);
  //      }
  //      digitalWrite(42, HIGH);
  //      digitalWrite(25,HIGH);


  while (digitalRead(35)) {
    digitalWrite(30, LOW);
    digitalWrite(32, HIGH);
  }
  digitalWrite(32, HIGH);
  digitalWrite(30, HIGH);

  while (digitalRead(38)) {
    digitalWrite(26, LOW);
    digitalWrite(24, HIGH);
  }
  digitalWrite(26, HIGH);
  digitalWrite(24, HIGH);

  while (digitalRead(27)) {
    digitalWrite(34, HIGH);
    digitalWrite(36, LOW);
  }
  digitalWrite(36, HIGH);
  digitalWrite(34, HIGH);

  while (digitalRead(21)) {
    digitalWrite(42, HIGH);
    digitalWrite(25, LOW);
  }
  digitalWrite(42, HIGH);
  digitalWrite(25, HIGH);

  Serial.print("Number of A type in storage: ");
  Serial.println(countA);
  Serial.print("Number of B type in storage: ");
  Serial.println(countB);
}

void loop() {



  //  while (digitalRead(37)) {
  //    digitalWrite(32, LOW);
  //    digitalWrite(30, HIGH);
  //  }
  //  digitalWrite(30, HIGH);
  //  digitalWrite(32, HIGH);
  //
  //  while (digitalRead(2)) {
  //    digitalWrite(30, LOW);
  //    digitalWrite(32, HIGH);
  //  }
  //  digitalWrite(32, HIGH);
  //  digitalWrite(30, HIGH);

  bluetoothRequest = false;
  //  Serial.println(digitalRead(40));
  Serial.println(state);


  if (state == 0) {
    while (!Serial1.available()) {
      if (Serial2.available()) {
        bluetoothRequest = true;
        break;
      }
    }
    source = Serial1.read();

    if (bluetoothRequest == true) {
      incomingBluetoothMessage = Serial2.read();
      if (incomingBluetoothMessage == 'a') {
        if (countA == 0) {
          Serial1.write(0xaa);
          while (Serial1.available());
          Serial1.write(0xa2);
          digitalWrite(8, HIGH);
          digitalWrite(9, LOW);
          state = 1;
        }
        else if (countA == 1) {
          while (!digitalRead(28)) {

            retrieve13();
          }
          countA--;
          EEPROM.update(addrA, countA);
          state = 4;
        }

        else if (countA == 2) {
          while (!digitalRead(28)) {

            retrieve32();
          }
          countA--;
          EEPROM.update(addrA, countA);
          state = 4;
        }

        else if (countA == 3) {
          while (!digitalRead(28)) {
            Serial.println("Retrieving..........");
            retrieve33();
          }
          countA--;
          EEPROM.update(addrA, countA);
          state = 4;
        }
        bluetoothRequest = false;

      }
      else if (incomingBluetoothMessage == 'b') {
        if (countB == 0) {
          Serial1.write(0xbb);
          while (Serial1.available());
          Serial1.write(0xa2);
          digitalWrite(8, HIGH);
          digitalWrite(9, LOW);
          state = 1;
        }

        else if (countB == 1) {
          while (!digitalRead(28)) {
            Serial.println("Retrieving..........");
            //            retrieve13();
          }
          countB--;
          EEPROM.update(addrB, countB);
          state = 4;
        }

        else if (countB == 2) {
          while (!digitalRead(28)) {
            Serial.println("Retrieving..........");
            //            retrieve32();
          }
          countB--;
          EEPROM.update(addrB, countB);
          state = 4;
        }

        else if (countB == 3) {
          while (!digitalRead(28)) {
            Serial.println("Retrieving..........");
            //            retrieve33();
          }
          countB--;
          EEPROM.update(addrB, countB);
          state = 4;
        }

        bluetoothRequest = false;
      }

      else if (incomingBluetoothMessage == 'c') {
        Serial1.write(0xcc);
        bluetoothRequest = false;
      }
    }

    else if (source == 0xc1) {
      Serial.println(source, HEX);
      Serial1.write(0xa2);
      digitalWrite(8, HIGH);
      digitalWrite(9, LOW);
      state = 1;
    }

    else {
      Serial.println(source, HEX);
      if (source == 0xa1) {
        Serial1.write(0xa2);
        if (countA == 0) {
          storingCompleted = false;
          digitalWrite(8, HIGH);
          digitalWrite(9, LOW);
          while (!storingCompleted) {
            store13();
          }
        }
        if (countA == 1) {
          storingCompleted = false;
          digitalWrite(8, HIGH);
          digitalWrite(9, LOW);
          while (!storingCompleted) {
            store32();
          }

        }
        if (countA == 2) {
          storingCompleted = false;
          digitalWrite(8, HIGH);
          digitalWrite(9, LOW);
          while (!storingCompleted) {
            store33();
          }
        }
        countA++;
        EEPROM.update(addrA, countA);
        if (EEPROM.read(addrA) >= 3) {
          Serial1.write(0xaf);
        }
        state = 0;
      }

      if (source == 0xb1) {
        Serial1.write(0xa2);
        if (countB == 0) {
          storingCompleted = false;
          digitalWrite(8, HIGH);
          digitalWrite(9, LOW);
          while (!storingCompleted) {
            storeL13();
          }
        }
        if (countB == 1) {
          storingCompleted = false;
          digitalWrite(8, HIGH);
          digitalWrite(9, LOW);
          while (!storingCompleted) {
            storeL32();
          }
        }
        if (countB == 2) {
          storingCompleted = false;
          digitalWrite(8, HIGH);
          digitalWrite(9, LOW);
          while (!storingCompleted) {
            storeL33();
          }
        }
        countB++;
        EEPROM.update(addrB, countB);
        if (EEPROM.read(addrB) >= 3) {
          Serial1.write(0xbf);
        }
        state = 0;
      }
    }
  }

  else if (state == 1) {
    if (digitalRead(4)) {
      Serial1.write(0xa3);
      digitalWrite(11, HIGH);
      digitalWrite(12, LOW);
      state = 2;
    }
  }

  else if (state == 2) {
    if (!digitalRead(10)) {
      digitalWrite(8, LOW);
      digitalWrite(9, LOW);
      digitalWrite(11, LOW);
      digitalWrite(12, LOW);

      while (digitalRead(2)) {
        digitalWrite(30, LOW);
        digitalWrite(32, HIGH);
      }
      digitalWrite(32, LOW);
      digitalWrite(30, LOW);

      //      digitalWrite(11, HIGH);
      //      digitalWrite(12, LOW);

      while (digitalRead(48)) {
        digitalWrite(24, LOW);
        digitalWrite(26, HIGH);
      }
      digitalWrite(26, HIGH);
      digitalWrite(24, HIGH);

      digitalWrite(11, LOW);
      digitalWrite(12, LOW);

      state = 3;
    }
  }

  else if (state == 3) {

    digitalWrite(23, HIGH);
    digitalWrite(22, LOW);
    while (digitalRead(37)) {
      digitalWrite(30, HIGH);
      digitalWrite(32, LOW);
    }
    digitalWrite(30, HIGH);
    digitalWrite(32, HIGH);
    while (digitalRead(38)) {
      digitalWrite(26, LOW);
      digitalWrite(24, HIGH);
    }
    digitalWrite(24, HIGH);
    digitalWrite(26, HIGH);
    //      digitalWrite(11, LOW);
    digitalWrite(3, HIGH);
    digitalWrite(13, LOW);
    while (digitalRead(21)) {
      digitalWrite(42, HIGH);
      digitalWrite(25, LOW);
    }
    digitalWrite(42, HIGH);
    digitalWrite(25, HIGH);
    state = 4;

  }
  else if (state == 4) {
    if (digitalRead(28)) {
      digitalWrite(3, LOW);
      digitalWrite(23, LOW);
      while (digitalRead(35)) {
        digitalWrite(30, LOW);
        digitalWrite(32, HIGH);
      }
      digitalWrite(32, HIGH);
      digitalWrite(30, HIGH);

      state = 5;
    }
  }

  else if (state == 5) {
    while (digitalRead(20)) {
      digitalWrite(42, LOW);
      digitalWrite(25, HIGH);
    }
    digitalWrite(25, HIGH);
    digitalWrite(42, HIGH);

    digitalWrite(3, LOW);
    digitalWrite(13, HIGH);

    Serial3.write(source);
    while (!Serial3.available());
    ack = Serial3.read();
    if (ack == 0xff) {
      digitalWrite(13, LOW);
      while (digitalRead(21)) {
        digitalWrite(42, HIGH);
        digitalWrite(25, LOW);
      }
      digitalWrite(42, HIGH);
      digitalWrite(25, HIGH);
      state = 0;
    }
  }
}
