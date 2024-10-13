import unittest
from datetime import datetime
from tabla import Sensor

class TestSensor(unittest.TestCase):

    def setUp(self):
        self.sensor = Sensor(id=1, tipo_sensor="Temperatura", nombre="Sensor 1", descripcion="Sensor de temperatura")

    def test_obtener_id(self):
        self.assertEqual(self.sensor.obtener_id(), 1)

    def test_obtener_tipo_sensor(self):
        self.assertEqual(self.sensor.obtener_tipo_sensor(), "Temperatura")

    def test_obtener_nombre(self):
        self.assertEqual(self.sensor.obtener_nombre(), "Sensor 1")

    def test_obtener_descripcion(self):
        self.assertEqual(self.sensor.obtener_descripcion(), "Sensor de temperatura")

    def test_obtener_fecha(self):
        self.assertIsInstance(self.sensor.obtener_fecha(), datetime)

    def test_establecer_id(self):
        self.sensor.establecer_id(2)
        self.assertEqual(self.sensor.obtener_id(), 2)

    def test_establecer_tipo_sensor(self):
        self.sensor.establecer_tipo_sensor("Humedad")
        self.assertEqual(self.sensor.obtener_tipo_sensor(), "Humedad")

    def test_establecer_nombre(self):
        self.sensor.establecer_nombre("Sensor 2")
        self.assertEqual(self.sensor.obtener_nombre(), "Sensor 2")

    def test_establecer_descripcion(self):
        self.sensor.establecer_descripcion("Sensor de humedad")
        self.assertEqual(self.sensor.obtener_descripcion(), "Sensor de humedad")

    def test_establecer_fecha(self):
        nueva_fecha = datetime(2022, 1, 1)
        self.sensor.establecer_fecha(nueva_fecha)
        self.assertEqual(self.sensor.obtener_fecha(), nueva_fecha)

if __name__ == '__main__':
    unittest.main()