import random
import json
from datetime import datetime, timedelta

def generar_datos_sensores(num_muestras):
    """Genera datos simulados de sensores para un número determinado de muestras.

    Args:
        num_muestras (int): Número de muestras de datos a generar.

    Returns:
        list: Lista de diccionarios, donde cada diccionario representa una muestra de datos de sensor.
    """
    datos_sensores = []
    tiempo_base = datetime.now()

        for i in range(num_muestras):
        id_sensor = f"sensor_{i}"
        humedad = random.uniform(30.0, 60.0)
        temperatura = random.uniform(20.0, 35.0)
        nivel_luz = random.uniform(10, 100)
        movimiento = random.choice([0, 1])
        
               
        led = 1 if nivel_luz < 50 else 0  
        
        aviso_humedad = "Humedad alta detectada" if humedad >= 40 else ""

        marca_tiempo = (tiempo_base - timedelta(minutes=i)).strftime('%Y-%m-%d %H:%M:%S')

        datos_sensores.append({
            "id": id_sensor,
            "timestamp": marca_tiempo,
            "humedad": round(humedad, 2),
            "temperatura": round(temperatura, 2),
            "luz": round(nivel_luz, 2),
            "movimiento": movimiento,
            "aviso_humedad": aviso_humedad,
            "topics": {
                "humedad_topic": f"{id_sensor}/sala/humedad",
                "temperatura_topic": f"{id_sensor}/sala/temperatura",
                "luz_topic": f"{id_sensor}/sala/luz",
                "mov_topic": f"{id_sensor}/sala/movimiento",
                "pir_topic": f"{id_sensor}/sala/pir",
                "aviso_humedad_topic": f"{id_sensor}/sala/aviso_humedad"
            }
        })

    return datos_sensores

def guardar_datos_json(datos_sensores, nombre_archivo="datos_sensores.json"):
    """Guarda los datos de los sensores en un archivo JSON.

    Args:
        datos_sensores (list): Lista de diccionarios con los datos de los sensores.
        nombre_archivo (str, optional): Nombre del archivo JSON. Por defecto, "datos_sensores.json".
    """
    with open(nombre_archivo, "w") as f:
        json.dump(datos_sensores, f, indent=4)
    print(f"Datos guardados en {nombre_archivo}")

if __name__ == "__main__":
    num_muestras = 100
    datos_sensores = generar_datos_sensores(num_muestras)
    guardar_datos_json(datos_sensores)