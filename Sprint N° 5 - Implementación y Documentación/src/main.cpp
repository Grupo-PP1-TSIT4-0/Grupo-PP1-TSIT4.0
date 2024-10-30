#include <Arduino.h>
#include <WiFi.h>
#include <PubSubClient.h>
#include <DHT.h> 

#define pinDHT 14
#define tipDHT DHT11 
DHT sensordht11(pinDHT, DHT11); 

const char* ssid = "Wokwi-GUEST";
const char* password = "";

const char* mqtt_server = "test.mosquitto.org";
const int mqtt_port = 8883;
const char* mqtt_user = "";
const char* mqtt_password = "";

const char* client_id = "PowerRangers";

const char* temperatura_topic = "deposito/temperatura";
const char* humedad_topic = "deposito/humedad";
const char* luz_topic = "deposito/luz";
const char* mov_topic = "deposito/movimiento";
const char* pir_topic = "deposito/pir";
const char* aviso_humedad_topic = "deposito/aviso_humedad";

const int pirPin = 25;
const int controlHumedadPin = 14;
const int luzPin = 32;

float temperatura; 
float humedadambiente; 
const float GAMMA = 0.7;
const float RL10 = 50;
float lux;

WiFiClient espClient;
PubSubClient client(espClient);

void callback(char* topic, byte* payload, unsigned int length) {
    Serial.print("Mensaje recibido: ");
    Serial.println(topic);

    String msg = "";
    for (unsigned int i = 0; i < length; i++) {
        msg += (char)payload[i];
    }
}

void setup_wifi() {
    delay(10);
    Serial.println("Conectando a WiFi...");
    WiFi.begin(ssid, password);
    while (WiFi.status() != WL_CONNECTED) {
        delay(500);
        Serial.print(".");
    }
    Serial.println("\nConectado al WiFi");
}

void reconnect() {
    while (!client.connected()) {
        Serial.println("Intentando la conexión a MQTT...");
        if (client.connect(client_id, mqtt_user, mqtt_password)) {
            Serial.println("Conectado al servidor de MQTT");
            client.subscribe(mov_topic);
        } else {
            Serial.print("Error de conexión, rc=");
            Serial.print(client.state());
            Serial.println(" Intentando nuevamente en 5 segundos");
            delay(5000);
        }
    }
}

void setup() {
    Serial.begin(115200);
    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);

    pinMode(controlHumedadPin, OUTPUT);
    pinMode(luzPin, INPUT);
    pinMode(pirPin, INPUT);

    sensordht11.begin();
}

void leerSensores() {
    int analogValue = analogRead(luzPin);
    float voltage = analogValue * (5.0 / 4095.0);
    float resistance = (RL10 * (5.0 - voltage)) / voltage;
    lux = pow(RL10 * 1000 * pow(10, GAMMA) / resistance, (1 / GAMMA));
    lux = constrain(lux, 0, 100000);

    temperatura = sensordht11.readTemperature();
    humedadambiente = sensordht11.readHumidity();
    if (isnan(temperatura) || isnan(humedadambiente)) {
        Serial.println("Error en la lectura del DHT!");
    }
}

void publicarDatos() {
    char luxStr[8], humStr[8], tempStr[8];
    dtostrf(lux, 1, 2, luxStr);
    dtostrf(humedadambiente, 1, 2, humStr);
    dtostrf(temperatura, 1, 2, tempStr);

    client.publish(luz_topic, luxStr);
    client.publish(humedad_topic, humStr);
    client.publish(temperatura_topic, tempStr);

    int movimientoDetectado = digitalRead(pirPin);
    client.publish(mov_topic, movimientoDetectado ? "1" : "0");

    if (humedadambiente >= 40 || temperatura >= 28) {
        client.publish(aviso_humedad_topic, "Humedad alta detectada");
    }

    Serial.print("Temperatura: ");
    Serial.println(temperatura);
    Serial.print("Humedad: ");
    Serial.println(humedadambiente);
    Serial.print("Luminosidad: ");
    Serial.println(lux);
    Serial.print("Movimiento detectado: ");
    Serial.println(movimientoDetectado ? "Sí" : "No");
}

void loop() {
    if (!client.connected()) {
        reconnect();
    }
    client.loop();

    leerSensores();
    publicarDatos();
    delay(2000);
}
