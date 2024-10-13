import unittest
from unittest.mock import patch, MagicMock
from conexion import ConectorDB

class TestConectorDB(unittest.TestCase):

    @patch('mysql.connector.connect')
    def test_conexion_exitosa(self, mock_connect):
        mock_connect.return_value.is_connected.return_value = True
        conector = ConectorDB()
        self.assertTrue(conector.conexion.is_connected())
        mock_connect.assert_called_once()

    @patch('mysql.connector.connect')
    def test_obtener_datos(self, mock_connect):
        mock_conexion = MagicMock()
        mock_cursor = MagicMock()
        mock_conexion.cursor.return_value = mock_cursor
        mock_cursor.fetchall.return_value = [(1, 'sensor1', 'nombre1', 'descripcion1', 'fecha1')]
        mock_connect.return_value = mock_conexion

        conector = ConectorDB()
        conector.obtener_datos()

        mock_cursor.execute.assert_called_once_with("SELECT * FROM sensores")
        mock_cursor.fetchall.assert_called_once()
        mock_conexion.close.assert_called_once()

    @patch('mysql.connector.connect')
    def test_insertar_datos(self, mock_connect):
        mock_conexion = MagicMock()
        mock_cursor = MagicMock()
        mock_conexion.cursor.return_value = mock_cursor
        mock_connect.return_value = mock_conexion

        class MockSensor:
            def getid(self):
                return 1
            def getsensor(self):
                return 'sensor1'
            def getnombre(self):
                return 'nombre1'
            def getdescripcion(self):
                return 'descripcion1'
            def getfecha(self):
                return 'fecha1'

        sensor = MockSensor()
        conector = ConectorDB()
        conector.insertar_datos(sensor)

        sql = "INSERT INTO sensores VALUES (%s, %s, %s, %s, %s)"
        valores = (1, 'sensor1', 'nombre1', 'descripcion1', 'fecha1')
        mock_cursor.execute.assert_called_once_with(sql, valores)
        mock_conexion.commit.assert_called_once()
        mock_conexion.close.assert_called_once()

if __name__ == '__main__':
    unittest.main()