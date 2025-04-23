from flask import Flask, jsonify
import serial
import threading
from flask_cors import CORS

app = Flask(__name__)
CORS(app, origins=["http://192.168.1.116:8080"])

# Configuración del puerto serial
SERIAL_PORT = '/dev/ttyUSB0'
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