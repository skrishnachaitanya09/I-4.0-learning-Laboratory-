#include <string.h>
#include "SPI.h"
#include "MFRC522.h"
#define SS_PIN 53
#define RST_PIN 5
#include "thread.h"
#include "PLiFi.hpp"
#include <stdlib.h>
#include "periph/eeprom.h"
MFRC522 mfrc522(SS_PIN, RST_PIN); // Instance of the class
uint8_t acc[10];
static const uint32_t DEVICE_ID_POS = 0;
static int state = 0;
int state2 = 0;
int palletType = -1;    //A->1  B->2    C->3
uint8_t device_id;
uint8_t control_info[] = {0x7e};
uint8_t request_data[] = {0x7d};
uint8_t pallet_types[] = {0xaa, 0xbb, 0xcc, 0xaf, 0xbf, 0xa0, 0xb0};
uint8_t sink1[] = {0xd6, 0xd7, 0xd8};
uint8_t sink2[] = {0xd0, 0xd1, 0xd2};
uint8_t sink3[] = {0xd3, 0xd4, 0xd5};
uint8_t conveyor[] = {0xa6, 0xa7, 0xa8, 0xa9, 0xb1, 0xb2};
uint8_t control_data[255];
uint8_t hiBay_data[] = {0xa1, 0xa2, 0xa3};

static char tx_stack1[THREAD_STACKSIZE_MAIN];
static char rx_stack1[THREAD_STACKSIZE_MAIN];

static void on_rx(PLiFi *lifi, const uint8_t *msg, uint8_t len);
static void control_message(const uint8_t *msg, uint8_t len);
static void on_message_for_me(const uint8_t *msg, uint8_t len);

PLiFi lifi1(22, 0, on_rx, NULL);

void *tx_loop(void *arg)
{
    PLiFi *lifi = (PLiFi *)arg;

    lifi->tx_loop();
    return NULL;
}

void *rx_loop(void *arg)
{
    PLiFi *lifi = (PLiFi *)arg;
    lifi->rx_loop();
    return NULL;
}

static void on_rx(PLiFi *lifi, const uint8_t *msg, uint8_t len)
{
    for (uint8_t i = 0; i < len - 1; i++)
    {
        Serial.print(msg[i], HEX);
        Serial.print(", 0x");
    }
    if (len >= 2)
    {
        if (msg[0] == device_id)
        {
            on_message_for_me(msg + 2, len - 2);
        }
        else if (msg[0] == control_info[0])
        {
            control_message(msg + 1, len - 1);
        }
        else
        {
            if (lifi != &lifi1)
            {
                lifi1.send_data(msg, len);
            }
        }
    }
}

static void control_message(const uint8_t *msg, uint8_t len)
{
    if (len > 0)
    {
        // Serial.print("Got: 0x");
        // for (uint8_t i = 0; i < len - 1; i++)
        // {
            // Serial.print(msg[i], HEX);
            // Serial.print(", 0x");
        // }
        // Serial.println(msg[len - 1], HEX);
        control_data[0] = msg[len - 1];
        if (control_data[0] == conveyor[0])
        {
            palletType = 1;
            state2 = 1;
        }
        if (control_data[0] == conveyor[1])
        {
            palletType = 2;
            state2 = 1;
        }
        if (control_data[0] == conveyor[2])
        {
            palletType = 3;
            state2 = 1;
        }
    }
    else
    {
        // Serial.println("Got: Empty message");
    }
}

static void on_message_for_me(const uint8_t *msg, uint8_t len)
{
    if (len > 0)
    {
        // Serial.print("Got: 0x");
        for (uint8_t i = 0; i < len - 1; i++)
        {
            // Serial.print(msg[i], HEX);
            // Serial.print(", 0x");
        }
        // Serial.println(msg[len - 1], HEX);
        //set state
        acc[0] = msg[len - 1];
        if (acc[0] == 0xf1)
            state = 1;
        if (acc[0] == 0xf2)
            state = 2;
        if (acc[0] == 0xf3)
            state = 3;
    }
    else
    {
        // Serial.println("Got: Empty message");
    }
}
// static const uint8_t defective1[] = {0x44, 0xA5, 0xE0, 0xE9};
// static const uint8_t defective2[] = {0xC5, 0x1D, 0xF7, 0x58};
// static const uint8_t defective3[] = {0x74, 0x31, 0xDC, 0xE9};

void setup()
{
    Serial.begin(9600);
    Serial.begin(9600);
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522
    // Serial.println("RFID reading UID");
    device_id = eeprom_read_byte(DEVICE_ID_POS);
    // Serial.print("Device ID: 0x");
    // Serial.println(device_id, HEX);

    thread_create(tx_stack1, sizeof(tx_stack1), THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST, tx_loop, &lifi1, "tx1");
    thread_create(rx_stack1, sizeof(rx_stack1), THREAD_PRIORITY_MAIN - 2,
                  THREAD_CREATE_STACKTEST, rx_loop, &lifi1, "rx1");
    delay(1);

    pinMode(2, INPUT);
    pinMode(3, INPUT);
    pinMode(23, INPUT);
    pinMode(30, INPUT_PULLUP);
    pinMode(32, INPUT_PULLUP);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, HIGH);

    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);

    digitalWrite(6, LOW); //HIGH for forward
    digitalWrite(9, LOW);

    digitalWrite(10, LOW); //HIGH for push
    digitalWrite(11, LOW);

    while (digitalRead(32))
    {
        digitalWrite(10, LOW);
        digitalWrite(11, HIGH);
    }
    digitalWrite(10, LOW); //HIGH for push
    digitalWrite(11, LOW);

    // Serial.println("setup() done");
}

boolean startSensor = false;
boolean endSensor = false;
boolean pusherSensor = false;
boolean messageSent = false;
boolean correctMessage = false;
boolean defective = false;
boolean startPusherSensor = true;
boolean endPusherSensor = true;
boolean userRequest = false;

int incomingByte = 0; // for incoming serial data
int txMessage = 0;
int rxMessage = 0;
int requestMessage = 0;

void loop()
{
    uint8_t msg[2];

    correctMessage = false;

    startSensor = digitalRead(3);
    endSensor = digitalRead(2);
    pusherSensor = digitalRead(23);

    startPusherSensor = digitalRead(30);
    endPusherSensor = digitalRead(32);

    // state2 = -1;
    // digitalWrite(8, HIGH); //HIGH for forward
    // digitalWrite(9, LOW);

    // Serial.write(0x1a);
    // while(Serial.available() < 0) { }
    // // read the incoming byte:
    // incomingByte = Serial.1read();

    // // say what you got:
    // Serial.print("I received: ");
    // Serial.println(incomingByte, DEC);

    // if (startSensor && state2 == 2)
    if (startSensor && state2 == 2)
    {
        state2 = 3;
    }
    if (endSensor && state2 == 4)
    {
        state2 = 5;
    }
    if (!startPusherSensor && state2 == 7)
    {
        state2 = 8;
    }
    if (!endPusherSensor && state2 == 8)
    {
        state2 = 0;
    }
    // Serial.print("State2: ");
    // Serial.println(state2);
    switch (state2)
    {
    case 0:
        // Serial.println("In state2 0");
        digitalWrite(6, LOW); //HIGH for forward
        digitalWrite(9, LOW);
        digitalWrite(10, LOW); //HIGH for push
        digitalWrite(11, LOW);
        while (!Serial.available())
        {
            if (state2 != 0)
            {
                userRequest = false;
                break;
            }
            else {
                userRequest = true;
            }
        }
        if (userRequest)
        {
            requestMessage = Serial.read();
            if (requestMessage == pallet_types[0])
            {
                msg[0] = request_data[0];
                msg[1] = pallet_types[0];
            }
            else if (requestMessage == pallet_types[1])
            {
                msg[0] = request_data[0];
                msg[1] = pallet_types[1];
            }
            else if (requestMessage == pallet_types[2])
            {
                msg[0] = request_data[0];
                msg[1] = pallet_types[2];
            }
            else if (requestMessage == pallet_types[3]) {
                msg[0] = request_data[0];
                msg[1] = pallet_types[3];
            }
            else if (requestMessage == pallet_types[4]) {
                msg[0] = request_data[0];
                msg[1] = pallet_types[4];
            }
            else if (requestMessage == pallet_types[5]) {
                msg[0] = request_data[0];
                msg[1] = pallet_types[5];
            }
            else if (requestMessage == pallet_types[6]) {
                msg[0] = request_data[0];
                msg[1] = pallet_types[6];
            }
            if (lifi1.send_data(msg, sizeof(msg)))
            {
                delay(10);
            }
        }
        break;
    case 1:
        // Serial.println("In state2 1");
        msg[0] = control_info[0];
        msg[1] = conveyor[3];
        if (lifi1.send_data(msg, sizeof(msg)))
        {
            delay(10);
        }
        defective = true;
        state2 = 2;
        break;
    case 2:
        // Serial.println("In state2 2");
        digitalWrite(6, HIGH); //HIGH for forward
        digitalWrite(9, LOW);
        if (mfrc522.PICC_IsNewCardPresent())
        {
            if (mfrc522.PICC_ReadCardSerial())
            {
                Serial.print("Tag UID:");
                // for (uint8_t i = 0; i < mfrc522.uid.size; i++) {
                //     Serial.print(mfrc522.uid.uidByte[i] < 0x10 ? " 0" : " ");
                //     Serial.print(mfrc522.uid.uidByte[i], HEX);
                // }
                Serial.println(mfrc522.uid.uidByte[0], HEX);
                Serial.println(mfrc522.uid.uidByte[1], HEX);
                Serial.println(mfrc522.uid.uidByte[2], HEX);
                Serial.println(mfrc522.uid.uidByte[3], HEX);
                // Serial.println(sizeof(mfrc522.uid.uidByte));
                // Serial.println(sizeof(sink1_1));
                // if (
                //     (mfrc522.uid.size == sizeof(defective1) &&
                //     mfrc522.uid.uidByte[0] == defective1[0] && mfrc522.uid.uidByte[1] == defective1[1] &&
                //     mfrc522.uid.uidByte[2] == defective1[2] && mfrc522.uid.uidByte[3] == defective1[3]) ||
                //     (mfrc522.uid.size == sizeof(defective2) &&
                //     mfrc522.uid.uidByte[0] == defective2[0] && mfrc522.uid.uidByte[1] == defective2[1] &&
                //     mfrc522.uid.uidByte[2] == defective2[2] && mfrc522.uid.uidByte[3] == defective2[3]) ||
                //     (mfrc522.uid.size == sizeof(defective3) &&
                //     mfrc522.uid.uidByte[0] == defective3[0] && mfrc522.uid.uidByte[1] == defective3[1] &&
                //     mfrc522.uid.uidByte[2] == defective3[2] && mfrc522.uid.uidByte[3] == defective3[3])
                //     )
                // {
                //     // Serial.println("Defective piece");
                //     defective = true;
                // }
                defective = false;
            }
        }
        break;
    case 3:
        // Serial.println("In state2 3");
        msg[0] = control_info[0];
        msg[1] = conveyor[4];
        if (lifi1.send_data(msg, sizeof(msg)))
        {
            delay(10);
        }
        state2 = 4;
        if (defective)
        {
            state2 = 7;
            msg[0] = request_data[0];
            if(palletType==1) {
                msg[1] = pallet_types[0];
            }
            else if(palletType==2) {
                msg[1] = pallet_types[1];
            }
            else if(palletType==3) {
                msg[1] = pallet_types[2];
            }
            
            if (lifi1.send_data(msg, sizeof(msg))) {
                delay(10);
            }
        }
        break;
    case 4:
        // Serial.println("In state2 4");
        digitalWrite(6, HIGH); //HIGH for forward
        digitalWrite(9, LOW);

        break;
    case 5:
        // Serial.println("In state2 5");
        digitalWrite(6, LOW); //HIGH for forward
        digitalWrite(9, LOW);
        if(palletType==1) {
            Serial.println("Sending 0xa1");
            Serial.write(hiBay_data[0]);
        }
        if(palletType==2) {
            Serial.println("Sending 0xb1");
            Serial.write(0xb1);
        }
        if(palletType==3) {
            Serial.println("Sending 0xc1");
            Serial.write(0xc1);
        }
        // Serial.println("Done writing 0xA1. Waiting for 0xA2 message...");
        while (!Serial.available())
        {
        }
        txMessage = Serial.read();
        // Serial.println(txMessage, HEX);
        while (!correctMessage)
        {
            if (txMessage == hiBay_data[1])
            {
                correctMessage = true;
                state2 = 6;
            }
        }
        break;
    case 6:
        // Serial.println("In state2 6");
        digitalWrite(6, HIGH); //HIGH for forward
        digitalWrite(9, LOW);
        while (!Serial.available())
        {
        }
        correctMessage = false;
        while (!correctMessage)
        {
            rxMessage = Serial.read();
            if (rxMessage == hiBay_data[2])
            {
                msg[0] = request_data[0];
                msg[1] = hiBay_data[2];
                if (lifi1.send_data(msg, sizeof(msg))) {
                    delay(10);
                }
                
                state2 = 0;
                correctMessage = true;
            }
        }
        break;
    case 7:
        // Serial.println("In state2 7");
        if (pusherSensor)
        {
            digitalWrite(6, LOW); //HIGH for forward
            digitalWrite(9, LOW);
            digitalWrite(10, HIGH); //HIGH for push
            digitalWrite(11, LOW);
        }
        break;
    case 8:
        digitalWrite(10, LOW); //HIGH for push
        digitalWrite(11, HIGH);
        break;
    }
}