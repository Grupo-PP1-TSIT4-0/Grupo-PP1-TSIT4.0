#include <WiFi.h>
#include <PubSubClient.h>


const char* ssid = "Power_Rangers";
const char* password = "PowerRangersForceInnovation";
const char* mqtt_server = "test.mosquitto.org";

const char* topico = "powerrangers/mq2";

WiFiClient espClient;
PubSubClient client(espClient);

#define MQ2PIN 34 
  

void setup() {
  Serial.begin(115200);
  
  setup_wifi();
  client.setServer(mqtt_server, 8883);
}

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

void loop() {
  delay(2000);
  
  int mq = analogRead(MQ2PIN);

  if (!client.connected()) {
    reconnect();
  }
  client.loop();

  String mensaje = "valor: " + String(mq);
  client.publish(topico, mensaje.c_str());
  Serial.println("Se enviaron los datos: " + String(mensaje));

  delay(3000);
}
