#include <nRF24L01.h>
#include <RF24.h>
#include <RF24_config.h>
#include <SPI.h>
#include <DigitalIO.h>
RF24 radio(7, 8);

const byte txAddr[6] = "11800";
const byte rxAddr[6] = "11801";
char text[] = "Hi";
char rxText[] = "";

/*
 * NRF Connections with Arduino Mega:
 * CE - 7
 * CSN - 8
 * M1/MISO - 50
 * M0/MOSI - 51
 * SCK - 52
 */


void setup(){
  pinMode(2,INPUT);
  radio.begin();
  Serial.begin(9600);
  radio.setRetries(15, 15);
  radio.setPALevel(RF24_PA_MIN);
  radio.openReadingPipe(1, txAddr);
  radio.openWritingPipe(rxAddr);
  radio.stopListening();
}  
void loop(){  
     bool sent = false;
    if(digitalRead(2)) {
      sent = radio.write(&text,sizeof(text));
      if(sent) {
        //motor start
        Serial.println("Motor Start");
        radio.startListening();
        while(!radio.available());
        //motor stop
        radio.read(&rxText, sizeof(rxText));
        radio.stopListening();
        if(strcmp(rxText, "AA"))
        Serial.println("Motor A Stop");
        else if(strcmp(rxText, "BB"))
        Serial.println("Motor B Stop");
        else if(strcmp(rxText, "CC"))        
        Serial.println("Motor C Stop");
        
      }
    }

//    if(radio.available()) {
//      radio.stopListening();
//      Serial.println("Transmitted");
//    }
}
