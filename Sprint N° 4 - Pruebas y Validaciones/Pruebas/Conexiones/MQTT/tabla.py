from datetime import *

class Sensor:
    """
    Clase que representa un sensor.
    """
    def __init__(self, id, tipo_sensor, nombre, descripcion, fecha=None):
        """
        Inicializa un nuevo sensor.

        Args:
            id: El ID del sensor.
            tipo_sensor: El tipo de sensor.
            nombre: El nombre del sensor.
            descripcion: La descripción del sensor.
            fecha: La fecha de creación del sensor.
        """
        self.id = id
        self.tipo_sensor = tipo_sensor
        self.nombre = nombre
        self.descripcion = descripcion
        self.fecha = fecha or datetime.today()

    def obtener_id(self):
        return self.id

    def obtener_tipo_sensor(self):
        return self.tipo_sensor

    def obtener_nombre(self):
        return self.nombre

    def obtener_descripcion(self):
        return self.descripcion

    def obtener_fecha(self):
        return self.fecha

    def establecer_id(self, id):
        self.id = id

    def establecer_tipo_sensor(self, tipo_sensor):
        self.tipo_sensor = tipo_sensor

    def establecer_nombre(self, nombre):
        self.nombre = nombre

    def establecer_descripcion(self, descripcion):
        self.descripcion = descripcion

    def establecer_fecha(self, fecha):
        self.fecha = fecha