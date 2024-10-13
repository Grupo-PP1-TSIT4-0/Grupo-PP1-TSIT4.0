#include <Arduino.h>
#include <unity.h>
#include "BluetoothSerial.h"
#include "ble.h"

extern BluetoothSerial SerialBT;
extern int ledPin;

void setUp(void) {
    // Set up code here, to run before each test
    iniciarBle();
}

void tearDown(void) {
    // Clean up code here, to run after each test
}

void test_bluetooth_initialization(void) {
    // Test if Bluetooth is initialized correctly
    TEST_ASSERT_TRUE(SerialBT.hasClient());
}

void test_led_initialization(void) {
    // Test if LED pin is set to OUTPUT
    TEST_ASSERT_EQUAL(OUTPUT, getPinMode(ledPin));
}

void test_led_on(void) {
    // Simulate receiving '1' via Bluetooth
    SerialBT.write('1');
    manejarBle();
    TEST_ASSERT_EQUAL(HIGH, digitalRead(ledPin));
}

void test_led_off(void) {
    // Simulate receiving '0' via Bluetooth
    SerialBT.write('0');
    manejarBle();
    TEST_ASSERT_EQUAL(LOW, digitalRead(ledPin));
}

void setup() {
    // NOTE!!! Wait for >2 secs if board doesn't support software reset via Serial.DTR/RTS
    delay(2000);

    UNITY_BEGIN();    // Start unit testing framework

    RUN_TEST(test_bluetooth_initialization);
    RUN_TEST(test_led_initialization);
    RUN_TEST(test_led_on);
    RUN_TEST(test_led_off);

    UNITY_END(); // Stop unit testing framework
}

void loop() {
    // Empty loop
}