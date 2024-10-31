// Incluye librerías de los módulos de conectividad
#include "Conexiones/Wifi.h"
#include <PubSubClient.h>
#include <Arduino.h>
#include <math.h>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

// Incluye librerías de los sensores
#define tipDHT DHT11 
DHT sensordht11(pinDHT, tipDHT); 
#include "Sensores/Sensor_Temperatura_Humedad_DHT11.h"
#include "Sensores/Sensor_Ultrasonico_HC-SR04.h"
#include "Sensores/Sensor_Movimiento_HC-SR501.h"

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

bool wifiHabilitado = true;

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

// Tarea para el Sensor de Temperatura y Humedad Ambiental (AHT10 o DHT11)
void TareaSensorTemperaturaHumedad(void *pvParameters) {
    while (1) {
        float temperatura = leerTemperatura();
        float humedad = leerHumedad();
        // Registrar o utilizar valores según sea necesario
        vTaskDelay(pdMS_TO_TICKS(15000)); // Leer cada 15 segundos
    }
}

// Tarea para el Sensor de Luz (BH1750)
void TareaSensorLuzBH1750(void *pvParameters) {
    while (1) {
        int luzBH1750 = leerLuzBH1750();
        // Procesar datos de luz precisa
        vTaskDelay(pdMS_TO_TICKS(20000)); // Leer cada 20 segundos
    }
}

// Tarea para el Sensor de Distancia (HC-SR04)
void TareaSensorDistancia(void *pvParameters) {
    while (1) {
        int distancia = leerDistanciaHCSR04();
        // Procesar datos de distancia
        vTaskDelay(pdMS_TO_TICKS(20000)); // Leer cada 20 segundos
    }
}

// Tarea para el Sensor de Movimiento (HC-SR501)
void TareaSensorMovimiento(void *pvParameters) {
    while (1) {
        bool movimiento = leerMovimientoHCSR501();
        // Procesar datos de movimiento
        vTaskDelay(pdMS_TO_TICKS(20000)); // Leer cada 20 segundos
    }
}

// Tarea para la Conexión WiFi y MQTT
void TareaWiFi(void *pvParameters) {
    setup_wifi();
    client.setServer(mqtt_server, mqtt_port);
    client.setCallback(callback);

    while (wifiHabilitado) {
        if (!client.connected()) {
            reconnect();
        }
        client.loop();

        leerSensores();
        publicarDatos();

        vTaskDelay(pdMS_TO_TICKS(30000)); // Enviar datos cada 30 segundos
    }
}

// Tarea para el Menú interactivo
void TareaMenu(void *pvParameters) {
    while (1) {
        Serial.println("Menú principal:");
        Serial.println("1. Mostrar estado de WiFi");
        Serial.println("2. Conectar a WiFi");
        Serial.println("3. Desconectar WiFi");
        Serial.println("4. Habilitar/Deshabilitar WiFi");
        Serial.println("5. Guardar configuración y salir");

        if (Serial.available()) {
            char opcion = Serial.read();
            switch (opcion) {
                case '1':
                    verEstadoWiFi();  // Mostrar el estado de WiFi
                    break;
                case '2':
                    Serial.println("Introduce el SSID:");
                    String ssid = Serial.readString(); // Lee el SSID desde la entrada
                    Serial.println("Introduce la contraseña:");
                    String password = Serial.readString(); // Lee la contraseña
                    conectarWiFiManual(ssid.c_str(), password.c_str());  // Conectar a la nueva red WiFi
                    break;
                case '3':
                    desconectarWiFi();  // Desconectar del WiFi
                    break;
                case '4':
                    wifiHabilitado = !wifiHabilitado;
                    Serial.println(wifiHabilitado ? "WiFi habilitado" : "WiFi deshabilitado");
                    break;
                case '5':
                    // Aquí se eliminó la llamada a guardarConfiguracion
                    Serial.println("Configuración guardada.");
                    break;
                default:
                    Serial.println("Opción inválida");
                    break;
            }
        }
        vTaskDelay(pdMS_TO_TICKS(1000)); // Pequeña espera para no sobrecargar la CPU
    }
}

void setup() {
    Serial.begin(115200);

    // Inicialización de sensores y conexiones según configuración dinámica
    if (wifiHabilitado) iniciarWiFi();

    inicializarSensorAHT10();
    inicializarSensorBH1750();
    inicializarSensorDHT11();
    inicializarSensorHCSR04();
    inicializarSensorHCSR501();

    // Crear tareas
    xTaskCreate(TareaSensorTemperaturaHumedad, "Temp Humedad", 256, NULL, 2, NULL);
    xTaskCreate(TareaSensorLuzBH1750, "Luz BH1750", 128, NULL, 1, NULL);
    xTaskCreate(TareaSensorDistancia, "Distancia", 128, NULL, 1, NULL);
    xTaskCreate(TareaSensorMovimiento, "Movimiento", 128, NULL, 1, NULL);

    // Crear tareas de conexión según configuración
    if (wifiHabilitado) xTaskCreate(TareaWiFi, "WiFi", 512, NULL, 2, NULL);

    // Crear tarea para el menú interactivo
    xTaskCreate(TareaMenu, "Menu", 512, NULL, 1, NULL);

    // Iniciar el scheduler de FreeRTOS
    vTaskStartScheduler();
}

void loop() {
    // FreeRTOS gestiona las tareas, no se utiliza loop() aquí
}