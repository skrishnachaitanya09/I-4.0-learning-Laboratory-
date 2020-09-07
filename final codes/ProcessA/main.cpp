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
uint8_t device_id;
uint8_t control_info[] = {0x7e};
uint8_t sink1[] = {0xd6, 0xd7, 0xd8};
uint8_t sink2[] = {0xd0, 0xd1, 0xd2};
uint8_t sink3[] = {0xd3, 0xd4, 0xd5};
uint8_t control_data[255];

static char tx_stack1[THREAD_STACKSIZE_MAIN];
static char rx_stack1[THREAD_STACKSIZE_MAIN];

static void on_rx(PLiFi *lifi, const uint8_t *msg, uint8_t len);
static void control_message(const uint8_t *msg, uint8_t len);
static void on_message_for_me(const uint8_t *msg, uint8_t len);

PLiFi lifi1(2, 0, on_rx, NULL);

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
        }
        if (control_data[0] == sink1[1])
        {
            state = 2;
            state2 = 3;
        }
        if (control_data[0] == sink1[2])
        {
            state = 3;
            state2 = 0;
        }
    }
    else
    {
        Serial.println("Got: Empty message");
    }
}

static void on_message_for_me(const uint8_t *msg, uint8_t len)
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
        Serial.println("Got: Empty message");
    }
}
static const uint8_t sink1_1[] = {0x3E, 0xF1, 0xBB, 0xDF};
static const uint8_t sink1_2[] = {0xC5, 0x1D, 0xF7, 0x58};
static const uint8_t sink2_1[] = {0x74, 0x31, 0xDC, 0xE9};
static const uint8_t sink2_2[] = {0x95, 0xFB, 0xF8, 0x58};
static const uint8_t sink3_1[] = {0x74, 0x8E, 0xE1, 0xE9};
static const uint8_t sink3_2[] = {0x54, 0xE6, 0xB6, 0xEB};

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

    pinMode(4, INPUT);
    pinMode(5, INPUT);
    pinMode(8, OUTPUT);
    pinMode(9, OUTPUT);

    digitalWrite(8, LOW);
    digitalWrite(9, LOW); //HIGH for forward
    Serial.println("setup() done");
}

boolean startSensor = false;
boolean endSensor = false;
boolean messageSent = false;

void loop()
{
    uint8_t msg[2];

    startSensor = digitalRead(4);
    endSensor = digitalRead(5);

    // if(endSensor!=digitalRead(5)) {
    //     messageSent = false;
    // }

    if (startSensor)
    {
        state2 = 1;
    }
    else if (endSensor && state2 == 1)
    {
        state2 = 2;
    }

    switch (state2)
    {
    case 0:
        digitalWrite(8, LOW);
        digitalWrite(9, LOW); //HIGH for forward
        break;
    case 1:
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH); //HIGH for forward
        break;
    case 2:
        digitalWrite(8, LOW);
        digitalWrite(9, LOW); //HIGH for forward

        msg[0] = control_info[0];
        msg[1] = sink1[0];
        if (lifi1.send_data(msg, sizeof(msg)))
        {
            delay(10);
        }
        messageSent = true;
        Serial.println("Message 0x7e sent");
        state2 = 0;
        break;
    case 3:
        digitalWrite(8, LOW);
        digitalWrite(9, HIGH); //HIGH for forward
        break;
    }
}
