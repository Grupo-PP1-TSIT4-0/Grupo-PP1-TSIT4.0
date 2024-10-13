import mysql.connector


class ConectorDB:
    def __init__(self):
        self.conexion = mysql.connector.connect(
            host="localhost",
            user="root",
            password="PowerRangers",
            database="powerrangers"
        )

        if self.conexion.is_connected:
            print("Conexión exitosa")

    def obtener_datos(self):
        cursor = self.conexion.cursor()
        cursor.execute("SELECT * FROM sensores")
        datos = cursor.fetchall()

        if not datos:
            print("No se encontraron resultados")
        else:
            for fila in datos:
                print(fila)
        self.conexion.close()

    def insertar_datos(self, sensor):
        cursor = self.conexion.cursor()
        sql = "INSERT INTO sensores VALUES (%s, %s, %s, %s, %s)"
        valores = (
            sensor.getid(),
            sensor.getsensor(),
            sensor.getnombre(),
            sensor.getdescripcion(),
            sensor.getfecha()
        )
        cursor.execute(sql, valores)
        self.conexion.commit()
        print("Registro insertado")