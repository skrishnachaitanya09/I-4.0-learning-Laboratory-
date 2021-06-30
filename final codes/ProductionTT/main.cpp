#include <string.h>
#include "SPI.h"
#include "MFRC522.h"
#define SS_PIN 53
#define RST_PIN 49
#include "thread.h"
#include "PLiFi.hpp"
#include <stdlib.h>
#include "periph/eeprom.h"
MFRC522 mfrc522(SS_PIN, RST_PIN); // Instance of the class
uint8_t acc[10];
static const uint32_t DEVICE_ID_POS = 0;
static int state = 0;
int state2 = 0;
int message_received_on = -1;
uint8_t device_id;
uint8_t control_info[] = {0x7e};
uint8_t request_data[] = {0x7d};
uint8_t pallet_types[] = {0xaa, 0xbb, 0xcc, 0xaf, 0xbf, 0xa0, 0xb0};
uint8_t sink1[] = {0xd6, 0xd7, 0xd8};
uint8_t sink2[] = {0xd0, 0xd1, 0xd2};
uint8_t sink3[] = {0xd3, 0xd4, 0xd5};
uint8_t conveyor[] = {0xa6, 0xa7, 0xa8, 0xa9, 0xb1, 0xb2};
uint8_t hiBay_data[] = {0xa1, 0xa2, 0xa3};
uint8_t control_data[255];
uint8_t msg2[2];
// char userRequest = '0';

static char tx_stack1[THREAD_STACKSIZE_DEFAULT];
static char rx_stack1[THREAD_STACKSIZE_DEFAULT];
static char tx_stack2[THREAD_STACKSIZE_DEFAULT];
static char rx_stack2[THREAD_STACKSIZE_DEFAULT];
static char tx_stack3[THREAD_STACKSIZE_DEFAULT];
static char rx_stack3[THREAD_STACKSIZE_DEFAULT];
static char tx_stack4[THREAD_STACKSIZE_DEFAULT];
static char rx_stack4[THREAD_STACKSIZE_DEFAULT];

static void on_rx(PLiFi *lifi, const uint8_t *msg, uint8_t len);
static void control_message(const uint8_t *msg, uint8_t len);
static void request_message(const uint8_t *msg, uint8_t len);
// static void on_message_for_me(const uint8_t *msg, uint8_t len);

PLiFi lifi1(28, 3, on_rx, NULL); //A
PLiFi lifi2(24, 1, on_rx, NULL); //B
PLiFi lifi3(22, 0, on_rx, NULL); //C
PLiFi lifi4(26, 2, on_rx, NULL); //D


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
    if (len >= 2)
    {
        if (msg[0] == device_id)
        {
            // on_message_for_me(msg + 2, len - 2);
        }
        else if (msg[0] == control_info[0])
        {
            control_message(msg + 1, len - 1);
        }
        else if (msg[0] == request_data[0])
        {
            request_message(msg + 1, len - 1);
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
        Serial.print("Got: 0x");
        for (uint8_t i = 0; i < len - 1; i++)
        {
            Serial.print(msg[i], HEX);
            Serial.print(", 0x");
        }
        Serial.println(msg[len - 1], HEX);
        control_data[0] = msg[len - 1];
        
        if (control_data[0] == sink1[0])
        {
            state = 1;
            state2 = 1;
            message_received_on = 1;
        }
        if (control_data[0] == sink2[0])
        {
            state = 2;
            state2 = 1;
            message_received_on = 2;
        }
        if (control_data[0] == sink3[0])
        {
            state = 3;
            state2 = 1;
            message_received_on = 3;
        }
        if(state2==9 && control_data[0] == conveyor[3]) {
            state2 = 10;
        }
        if(state2==10 && control_data[0] == conveyor[4]) {
            state2 = 0;
        }
    }
    else
    {
        Serial.println("Got: Empty message");
    }
}

static void request_message(const uint8_t *msg, uint8_t len)
{
    if (len > 0)
    {
        Serial.print("Got: 0x");
        for (uint8_t i = 0; i < len - 1; i++)
        {
            Serial.print(msg[i], HEX);
            Serial.print(", 0x");
        }
        Serial.println(msg[len - 1], HEX);
        control_data[0] = msg[len - 1];
        
        if (control_data[0] == pallet_types[0])
        {
            // userRequest = 'a';
            msg2[0] = request_data[0];
            msg2[1] = pallet_types[0];
            if (lifi1.send_data(msg2, sizeof(msg2))) {
                delay(10);
            }
            if (lifi2.send_data(msg2, sizeof(msg2))) {
                delay(10);
            }
            if (lifi3.send_data(msg2, sizeof(msg2))) {
                delay(10);
            }
        }
        else if (control_data[0] == pallet_types[1])
        {
            // userRequest = 'b';
            msg2[0] = request_data[0];
            msg2[1] = pallet_types[1];
            if (lifi1.send_data(msg2, sizeof(msg2))) {
                delay(10);
            }
            if (lifi2.send_data(msg2, sizeof(msg2))) {
                delay(10);
            }
            if (lifi3.send_data(msg2, sizeof(msg2))) {
                delay(10);
            }
        }
        else if (control_data[0] == pallet_types[2])
        {
            // userRequest = 'c';
            msg2[0] = request_data[0];
            msg2[1] = pallet_types[2];
            if (lifi1.send_data(msg2, sizeof(msg2))) {
                delay(10);
            }
            if (lifi2.send_data(msg2, sizeof(msg2))) {
                delay(10);
            }
            if (lifi3.send_data(msg2, sizeof(msg2))) {
                delay(10);
            }
        }
        else if (control_data[0] == pallet_types[3])
        {
            // userRequest = '1';
            msg2[0] = request_data[0];
            msg2[1] = pallet_types[3];
            if (lifi1.send_data(msg2, sizeof(msg2))) {
                delay(10);
            }
        }
        else if (control_data[0] == pallet_types[4])
        {
            // userRequest = '2';
            msg2[0] = request_data[0];
            msg2[1] = pallet_types[4];
            if (lifi2.send_data(msg2, sizeof(msg2))) {
                delay(10);
            }
        }
        else if (control_data[0] == pallet_types[5]) {
            msg2[0] = request_data[0];
            msg2[1] = pallet_types[5];
            if (lifi1.send_data(msg2, sizeof(msg2)))
            {
                delay(10);
            }
        }
        else if (control_data[0] == pallet_types[6]) {
            msg2[0] = request_data[0];
            msg2[1] = pallet_types[6];
            if (lifi2.send_data(msg2, sizeof(msg2)))
            {
                delay(10);
            }
        }
        else if(control_data[0] == hiBay_data[2]) {
            msg2[0] = request_data[0];
            msg2[1] = hiBay_data[2];
            if (lifi1.send_data(msg2, sizeof(msg2)))
            {
                delay(10);
            }
            if (lifi2.send_data(msg2, sizeof(msg2)))
            {
                delay(10);
            }
            if (lifi3.send_data(msg2, sizeof(msg2)))
            {
                delay(10);
            }
        }
        // userRequest = '0';
    }
    else
    {
        Serial.println("Got: Empty message");
    }
}

// static void on_message_for_me(const uint8_t *msg, uint8_t len)
// {
//     if (len > 0)
//     {
//         Serial.print("Got: 0x");
//         for (uint8_t i = 0; i < len - 1; i++)
//         {
//             Serial.print(msg[i], HEX);
//             Serial.print(", 0x");
//         }
//         Serial.println(msg[len - 1], HEX);
//     }
//     else
//     {
//         Serial.println("Got: Empty message");
//     }
// }
// static const uint8_t sink1_1[] = {0x3E, 0xF1, 0xBB, 0xDF};
// static const uint8_t sink1_2[] = {0xC5, 0x1D, 0xF7, 0x58};
// static const uint8_t sink2_1[] = {0x74, 0x31, 0xDC, 0xE9};
// static const uint8_t sink2_2[] = {0x95, 0xFB, 0xF8, 0x58};
// static const uint8_t sink3_1[] = {0x74, 0x8E, 0xE1, 0xE9};
// static const uint8_t sink3_2[] = {0x54, 0xE6, 0xB6, 0xEB};

void setup()
{
    SPI.begin();        // Init SPI bus
    mfrc522.PCD_Init(); // Init MFRC522
    Serial.println("RFID reading UID");
    device_id = eeprom_read_byte(DEVICE_ID_POS);
    Serial.print("Device ID: 0x");
    Serial.println(device_id, HEX);

    thread_create(tx_stack1, sizeof(tx_stack1), THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST, tx_loop, &lifi1, "tx1");
    thread_create(rx_stack1, sizeof(rx_stack1), THREAD_PRIORITY_MAIN - 2,
                  THREAD_CREATE_STACKTEST, rx_loop, &lifi1, "rx1");
    delay(1);

    thread_create(tx_stack2, sizeof(tx_stack2), THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST, tx_loop, &lifi2, "tx2");
    thread_create(rx_stack2, sizeof(rx_stack2), THREAD_PRIORITY_MAIN - 2,
                  THREAD_CREATE_STACKTEST, rx_loop, &lifi2, "rx2");
    delay(1);

    thread_create(tx_stack3, sizeof(tx_stack3), THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST, tx_loop, &lifi3, "tx3");
    thread_create(rx_stack3, sizeof(rx_stack3), THREAD_PRIORITY_MAIN - 2,
                  THREAD_CREATE_STACKTEST, rx_loop, &lifi3, "rx3");
    delay(1);

    thread_create(tx_stack4, sizeof(tx_stack4), THREAD_PRIORITY_MAIN - 1,
                  THREAD_CREATE_STACKTEST, tx_loop, &lifi4, "tx4");
    thread_create(rx_stack4, sizeof(rx_stack4), THREAD_PRIORITY_MAIN - 2,
                  THREAD_CREATE_STACKTEST, rx_loop, &lifi4, "rx4");
    delay(1);

    pinMode(30, INPUT_PULLUP); //parallel
    pinMode(32, INPUT_PULLUP); //perpendicular
    pinMode(3, INPUT);
    pinMode(6, OUTPUT);
    pinMode(9, OUTPUT);
    pinMode(4, OUTPUT);
    digitalWrite(4, HIGH);
    pinMode(10, OUTPUT);
    pinMode(11, OUTPUT);
    pinMode(5, OUTPUT);
    digitalWrite(5, HIGH);

    digitalWrite(6, LOW);
    digitalWrite(9, LOW); //HIGH for forward
    
    digitalWrite(10, LOW); //HIGH for clockwise
    digitalWrite(11, LOW);

    Serial.println("setup() done");
}

boolean startSensor = false;
boolean endSensor = false;
boolean messageSent = false;


void loop()
{
    uint8_t msg[2];

    switch(state2) {
        case 0:
            Serial.println("In state2 0");
            digitalWrite(6, LOW);
            digitalWrite(9, LOW); //HIGH for forward
            
            digitalWrite(10, LOW); //HIGH for clockwise
            digitalWrite(11, LOW);            
            break;

        case 1:
            Serial.println("In state2 1");
            if(message_received_on == 1) {
                if(digitalRead(30)!=LOW) {
                    digitalWrite(10, HIGH); //HIGH for clockwise
                    digitalWrite(11, LOW);
                }
                else {
                    state2 = 4;
                    digitalWrite(10, LOW); //HIGH for clockwise
                    digitalWrite(11, LOW);
                }
            }
            else if(message_received_on == 2) {
                if(digitalRead(32)!=LOW) {
                    digitalWrite(10, LOW); //HIGH for clockwise
                    digitalWrite(11, HIGH);
                }
                else {
                    state2 = 4;
                    digitalWrite(10, LOW); //HIGH for clockwise
                    digitalWrite(11, LOW);
                }
            }
            else if(message_received_on == 3) {
                if(digitalRead(32)!=LOW) {
                    digitalWrite(10, LOW); //HIGH for clockwise
                    digitalWrite(11, HIGH);
                }
                else {
                    state2 = 4;
                    digitalWrite(10, LOW); //HIGH for clockwise
                    digitalWrite(11, LOW);
                }
            }
            break;
        case 4:
            Serial.println("In state2 4");
            msg[0] = control_info[0];
            if(message_received_on == 1) {
                msg[1] = sink1[1];
                if (lifi1.send_data(msg, sizeof(msg)))
                {
                    delay(10);
                }
            }
            else if(message_received_on == 2) {
                msg[1] = sink2[1];
                if (lifi2.send_data(msg, sizeof(msg)))
                {
                    delay(10);
                }
            }
            else if(message_received_on == 3) {
                msg[1] = sink3[1];
                if (lifi3.send_data(msg, sizeof(msg)))
                {
                    delay(10);
                }
            }
            
            state2 = 5;
            break;

        case 5:
            Serial.println("In state2 5");
            if(message_received_on == 1) {
                digitalWrite(6, LOW);
                digitalWrite(9, HIGH); //HIGH for forward
            }
            else if(message_received_on == 2) {
                digitalWrite(6, LOW);
                digitalWrite(9, HIGH); //HIGH for forward
            }
            else if(message_received_on == 3) {
                digitalWrite(6, HIGH); 
                digitalWrite(9, LOW); //HIGH for forward
            }

            if(digitalRead(3)==HIGH) {
                state2 = 6;
            }
            break;

        case 6:
            Serial.println("In state2 6");
            digitalWrite(6, LOW); 
            digitalWrite(9, LOW); //HIGH for forward

            digitalWrite(10, LOW); //HIGH for clockwise
            digitalWrite(11, LOW);

            msg[0] = control_info[0];
            msg[1] = sink1[2];

            if(message_received_on == 1) {
                msg[1] = sink1[2];
                if (lifi1.send_data(msg, sizeof(msg)))
                {
                    delay(10);
                }
            }
            else if(message_received_on == 2) {
                msg[1] = sink2[2];
                if (lifi2.send_data(msg, sizeof(msg)))
                {
                    delay(10);
                }
            }
            else if(message_received_on == 3) {
                msg[1] = sink3[2];
                if (lifi3.send_data(msg, sizeof(msg)))
                {
                    delay(10);
                }
            }

            state2 = 7;
            break;
        
        case 7:
            Serial.println("In state2 7");
            if(digitalRead(30)!=LOW) {
                digitalWrite(10, HIGH); //HIGH for clockwise
                digitalWrite(11, LOW);
            }
            else {
                state2 = 8;
                digitalWrite(10, LOW); //HIGH for clockwise
                digitalWrite(11, LOW);
            }
            break;

        case 8:
            Serial.println("In state2 8");
            msg[0] = control_info[0];
            if(message_received_on == 1) {
                msg[1] = conveyor[0];
            }
            else if(message_received_on == 2) {
                msg[1] = conveyor[1];
            }
            else if(message_received_on == 3) {
                msg[1] = conveyor[2];
            }
            if (lifi4.send_data(msg, sizeof(msg)))
            {
                delay(10);
            }
            state2 = 9;
            break;
        
        case 9:
            Serial.println("In state2 9");
            break;

        case 10:
            Serial.println("In state2 10");
            digitalWrite(6, LOW);
            digitalWrite(9, HIGH); //HIGH for forward
            break;
        
    }

}
