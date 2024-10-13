#include <Arduino.h>
#include <SPI.h>
#include <LoRa.h>
#include <unity.h>

const int ss = 18;    // Pin de NSS
const int rst = 14;   // Pin de RST
const int dio0 = 26;  // Pin de DIO0

void test_lora_initialization() {
    LoRa.setPins(ss, rst, dio0);
    bool initialized = LoRa.begin(433E6);
    TEST_ASSERT_TRUE_MESSAGE(initialized, "LoRa initialization failed");
}

void test_lora_send_message() {
    LoRa.beginPacket();
    LoRa.print("Test message");
    int result = LoRa.endPacket();
    TEST_ASSERT_EQUAL_MESSAGE(1, result, "LoRa packet sending failed");
}

void test_lora_receive_message() {
    // Simulate sending a message
    LoRa.beginPacket();
    LoRa.print("Test message");
    LoRa.endPacket();

    // Simulate receiving the message
    int packetSize = LoRa.parsePacket();
    TEST_ASSERT_TRUE_MESSAGE(packetSize > 0, "No packet received");

    if (packetSize) {
        String received = LoRa.readString();
        TEST_ASSERT_EQUAL_STRING_MESSAGE("Test message", received.c_str(), "Received message does not match");
    }
}

void setup() {
    delay(2000); // service delay
    UNITY_BEGIN(); // start unit testing

    RUN_TEST(test_lora_initialization);
    RUN_TEST(test_lora_send_message);
    RUN_TEST(test_lora_receive_message);

    UNITY_END(); // end unit testing
}

void loop() {
    // Empty loop
}