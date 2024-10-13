#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "wifi.h"

// Mocking functions for testing
void mockWiFiBegin(const char* ssid, const char* password) {
    Serial.println("Mock WiFi.begin called");
}

int mockWiFiStatus() {
    static int status = WL_DISCONNECTED;
    status = (status == WL_DISCONNECTED) ? WL_CONNECTED : WL_DISCONNECTED;
    return status;
}

String mockWiFiLocalIP() {
    return "192.168.1.100";
}

void mockHTTPClientBegin(HTTPClient* http, const char* url) {
    Serial.println("Mock HTTPClient.begin called with URL: " + String(url));
}

void mockHTTPClientAddHeader(HTTPClient* http, const char* name, const char* value) {
    Serial.println("Mock HTTPClient.addHeader called with name: " + String(name) + ", value: " + String(value));
}

int mockHTTPClientPOST(HTTPClient* http, const String& payload) {
    Serial.println("Mock HTTPClient.POST called with payload: " + payload);
    return HTTP_CODE_OK;
}

String mockHTTPClientGetString(HTTPClient* http) {
    return "Mock server response";
}

void setup() {
    Serial.begin(115200);

    // Replace actual functions with mocks
    WiFi.begin = mockWiFiBegin;
    WiFi.status = mockWiFiStatus;
    WiFi.localIP = mockWiFiLocalIP;
    HTTPClient::begin = mockHTTPClientBegin;
    HTTPClient::addHeader = mockHTTPClientAddHeader;
    HTTPClient::POST = mockHTTPClientPOST;
    HTTPClient::getString = mockHTTPClientGetString;

    // Test iniciarWiFi function
    Serial.println("Testing iniciarWiFi...");
    iniciarWiFi();

    // Test manejarWiFi function
    Serial.println("Testing manejarWiFi...");
    manejarWiFi();
}

void loop() {
    // Empty loop for testing purposes
}
#include <Arduino.h>
#include <WiFi.h>
#include <HTTPClient.h>
#include "wifi.h"

// Mocking functions for testing
void mockWiFiBegin(const char* ssid, const char* password) {
    Serial.println("Mock WiFi.begin called");
}

int mockWiFiStatus() {
    static int status = WL_DISCONNECTED;
    status = (status == WL_DISCONNECTED) ? WL_CONNECTED : WL_DISCONNECTED;
    return status;
}

String mockWiFiLocalIP() {
    return "192.168.1.100";
}

void mockHTTPClientBegin(HTTPClient* http, const char* url) {
    Serial.println("Mock HTTPClient.begin called with URL: " + String(url));
}

void mockHTTPClientAddHeader(HTTPClient* http, const char* name, const char* value) {
    Serial.println("Mock HTTPClient.addHeader called with name: " + String(name) + ", value: " + String(value));
}

int mockHTTPClientPOST(HTTPClient* http, const String& payload) {
    Serial.println("Mock HTTPClient.POST called with payload: " + payload);
    return HTTP_CODE_OK;
}

String mockHTTPClientGetString(HTTPClient* http) {
    return "Mock server response";
}

void setup() {
    Serial.begin(115200);

    // Replace actual functions with mocks
    WiFi.begin = mockWiFiBegin;
    WiFi.status = mockWiFiStatus;
    WiFi.localIP = mockWiFiLocalIP;
    HTTPClient::begin = mockHTTPClientBegin;
    HTTPClient::addHeader = mockHTTPClientAddHeader;
    HTTPClient::POST = mockHTTPClientPOST;
    HTTPClient::getString = mockHTTPClientGetString;

    // Test iniciarWiFi function
    Serial.println("Testing iniciarWiFi...");
    iniciarWiFi();

    // Test manejarWiFi function
    Serial.println("Testing manejarWiFi...");
    manejarWiFi();
}

void loop() {
    // Empty loop for testing purposes
}
