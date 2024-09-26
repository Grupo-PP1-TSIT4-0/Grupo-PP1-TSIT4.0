import paho.mqtt.client as mqtt
import json
from conexion import Conexion
from sensor import Sensor

topico = "deposito/temperatura"

def on_connect(client, userdata, flags, rc):
    if rc == 0:        
        print("La Conexión al broker MQTT se realizo de forma exitosa")
        client.subscribe(topico)
        print(f"Suscrito a : {topico}")
    else:        
        print(f"Ha ocurrido un error al intentar conectar al broker MQTT. El código de error es: {rc}")

conectar = Conexion()

def on_message(client, userdata, mensaje):
    print(f"Mensaje recibido: {mensaje.payload.decode()}: {topico}")
    sensor = Sensor(0, 1, "humedad", mensaje)  
    conectar.insertar_datos(sensor)       

cliente = mqtt.Client()

cliente.on_connect = on_connect
cliente.on_message = on_message

cliente.connect("test.mosquitto.org", 8883, 60) 

cliente.loop_forever()