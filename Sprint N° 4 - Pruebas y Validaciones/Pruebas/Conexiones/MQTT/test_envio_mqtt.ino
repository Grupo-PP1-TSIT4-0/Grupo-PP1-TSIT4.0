#include <WiFi.h>
#include <PubSubClient.h>
#include <unity.h>

const char* ssid = "Power_Rangers";
const char* password = "PowerRangersForceInnovation";
const char* mqtt_server = "test.mosquitto.org";

const char* topico = "powerrangers/mq2";

WiFiClient espClient;
PubSubClient client(espClient);

#define MQ2PIN 34 

void setup_wifi() {
    delay(10);
    Serial.print("Usted se a contectado a ");
    Serial.println(ssid);

    WiFi.begin(ssid, password);

    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }

    Serial.println("El WiFi se ha conectado exitosamente");
    Serial.println("Dirección IP: ");
    Serial.println(WiFi.localIP());
}

void reconnect() {
    while (!client.connected()) {
        Serial.print("Aguarde unos segundos, intentando conectar a MQTT...");
        if (client.connect("ESP32Client_001")) {
            Serial.println("Exitosamente Conectado");
        } else {
            Serial.print("Conexion Fallida, rc=");
            Serial.print(client.state());
            Serial.println("Volviendo a intentar conectar, aguarde unos segundos");
            delay(5000);
        }
    }
}

void test_wifi_connection() {
    setup_wifi();
    TEST_ASSERT_EQUAL(WL_CONNECTED, WiFi.status());
}

void test_mqtt_connection() {
    reconnect();
    TEST_ASSERT_TRUE(client.connected());
}

void test_mq2_reading() {
    int mq = analogRead(MQ2PIN);
    TEST_ASSERT_GREATER_OR_EQUAL(0, mq);
    TEST_ASSERT_LESS_OR_EQUAL(4095, mq);
}

void setup() {
    Serial.begin(115200);
    delay(2000);
    UNITY_BEGIN();

    RUN_TEST(test_wifi_connection);
    RUN_TEST(test_mqtt_connection);
    RUN_TEST(test_mq2_reading);

    UNITY_END();
}

void loop() {
    // Empty loop since tests are run in setup
}