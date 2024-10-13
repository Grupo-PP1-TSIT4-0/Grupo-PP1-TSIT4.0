import unittest
from unittest.mock import MagicMock, patch
from mq2 import on_connect, on_message, topico

import paho.mqtt.client as mqtt

class TestMQTT(unittest.TestCase):

    @patch('mq2.Conexion')
    def test_on_connect_success(self, MockConexion):
        client = MagicMock()
        userdata = None
        flags = None
        rc = 0  # Simulate successful connection

        on_connect(client, userdata, flags, rc)

        client.subscribe.assert_called_with(topico)
        client.subscribe.assert_called_once()
        print("Test on_connect_success passed")

    @patch('mq2.Conexion')
    def test_on_connect_failure(self, MockConexion):
        client = MagicMock()
        userdata = None
        flags = None
        rc = 1  # Simulate failed connection

        on_connect(client, userdata, flags, rc)

        client.subscribe.assert_not_called()
        print("Test on_connect_failure passed")

    @patch('mq2.Sensor')
    @patch('mq2.Conexion')
    def test_on_message(self, MockConexion, MockSensor):
        client = MagicMock()
        userdata = None
        mensaje = MagicMock()
        mensaje.payload.decode.return_value = '{"temperature": 22.5}'

        on_message(client, userdata, mensaje)

        MockSensor.assert_called_with(0, 1, "humedad", mensaje)
        MockConexion().insertar_datos.assert_called_once()
        print("Test on_message passed")

if __name__ == '__main__':
    unittest.main()