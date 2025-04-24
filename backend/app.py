from flask import Flask, jsonify
import serial
import threading
from flask_cors import CORS
import glob
import os

app = Flask(__name__)
CORS(app, origins=["http://192.168.1.116:8080"])

def encontrar_puerto_ch340():
    # Buscar puertos seriales disponibles
    for puerto in glob.glob('/dev/ttyUSB*'):
        # Construir la ruta al directorio del dispositivo en /sys
        sys_path = f"/sys/class/tty/{puerto.split('/')[-1]}/device"
        driver_path = f"{sys_path}/driver"

        # Verificar si el dispositivo usa el controlador ch341-uart
        if os.path.exists(driver_path):
            # Leer el nombre del controlador
            driver_name = os.readlink(driver_path).split('/')[-1]
            if driver_name == "ch341-uart":  # Ajustado para "ch341-uart"
                return puerto  # Retornar el puerto encontrado

    return None  # Si no se encuentra ningún CH340

# Ejecutar la función
puerto_arduino = encontrar_puerto_ch340()

if puerto_arduino:
    print(f"Puerto seleccionado: {puerto_arduino}")
else:
    print("No se encontró el dispositivo CH340.")

SERIAL_PORT = puerto_arduino 
BAUD_RATE = 9600

# Variable global para almacenar el último dato recibido
last_data = None

def read_serial():
    global last_data
    try:
        ser = serial.Serial(SERIAL_PORT, BAUD_RATE, timeout=1)
        while True:
            line = ser.readline().decode('utf-8').strip()
            if line:
                last_data = line
    except Exception as e:
        print(f"Error al leer el puerto serial: {e}")

# Iniciar el hilo para leer el puerto serial
thread = threading.Thread(target=read_serial, daemon=True)
thread.start()

@app.route('/data', methods=['GET'])
def get_data():
    global last_data
    return jsonify({'data': last_data})

if __name__ == '__main__':
    app.run(host='0.0.0.0', port=5000)