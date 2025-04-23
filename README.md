# Monitor de Temperatura con Arduino, Raspberry Pi y Docker

Este proyecto permite monitorear datos enviados por un sensor DHT11 conectado a un Arduino a través de una Raspberry Pi. El sistema consta de un backend que lee los datos del puerto serial del Arduino y un frontend que muestra esos datos en una página web simple. Todo está orquestado con Docker Compose para facilitar la configuración y ejecución.

## Características

- **Backend:** Un servidor Flask liviano que lee datos del puerto serial (`/dev/ttyUSB0`) y los expone a través de una API REST.
- **Frontend:** Una página HTML simple servida por Nginx que consume los datos del backend y los muestra en tiempo real.
- **Docker Compose:** Configuración completa para levantar ambos servicios (frontend y backend) en contenedores Docker.
- **Proxy Inverso:** Nginx actúa como proxy inverso para redirigir las solicitudes del frontend al backend.

## Requisitos Previos

1. **Raspberry Pi:**
   - Conexión a internet.
   - Puerto USB disponible para conectar el Arduino.

2. **Arduino:**
   - Debe estar programado con el código proporcionado en este README.
   - Sensor DHT11 conectado al pin digital 2.

3. **Software:**
   - Docker y Docker Compose instalados en la Raspberry Pi.
     ```bash
     sudo apt update
     sudo apt install docker docker-compose
     ```

4. **Permisos de Puerto Serial:**
   - Asegúrate de que tu usuario tenga acceso al grupo `dialout` para leer el puerto serial.
     ```bash
     sudo usermod -a -G dialout $USER
     ```
## Estructura del Proyecto
    
    ```
    arduino-backend/
    ├── backend/
    │   ├── app.py                # Backend Flask
    │   ├── requirements.txt      # Dependencias de Python
    │   └── Dockerfile            # Configuración del contenedor del backend
    ├── frontend/
    │   ├── index.html            # Frontend HTML
    │   ├── nginx.conf            # Configuración de Nginx
    │   └── Dockerfile            # Configuración del contenedor del frontend
    └── docker-compose.yml        # Orquestación de Docker
    
    ```

## Código del Arduino

El siguiente código es para un Arduino que utiliza un sensor DHT11 para medir la temperatura y enviar los datos a través del puerto serial. Este código debe cargarse en el Arduino antes de conectarlo a la Raspberry Pi.

```cpp
#include <DHT.h>

#define DHTPIN 2      // Pin donde está conectado el sensor DHT11
#define DHTTYPE DHT11 // Tipo de sensor (DHT11)

DHT dht(DHTPIN, DHTTYPE);

void setup() {
  Serial.begin(9600); // Inicializa la comunicación serial a 9600 baudios
  dht.begin();        // Inicializa el sensor DHT11
}

void loop() {
  float temperature = dht.readTemperature(); // Lee la temperatura en grados Celsius

  // Verifica si la lectura fue exitosa
  if (isnan(temperature)) {
    Serial.println("Error al leer el sensor DHT11");
  } else {
    Serial.print("Temperatura: ");
    Serial.print(temperature);
    Serial.println(" °C");
  }

  delay(2000); // Espera 2 segundos antes de la próxima lectura
}
```

### **Bloque 5: Instrucciones para Cargar el Código**

```markdown
### **Instrucciones para Cargar el Código**

1. **Instala la Biblioteca DHT:**
   Asegúrate de tener instalada la biblioteca `DHT` en tu IDE de Arduino. Puedes instalarla desde el Administrador de Librerías:
   - Ve a `Herramientas > Administrar Bibliotecas`.
   - Busca `DHT` y selecciona la biblioteca creada por Adafruit.

2. **Conecta el Sensor DHT11:**
   Conecta el sensor DHT11 al Arduino:
   - **Pin VCC** del sensor al pin `5V` del Arduino.
   - **Pin GND** del sensor al pin `GND` del Arduino.
   - **Pin DATA** del sensor al pin `2` del Arduino (o el pin definido en `DHTPIN`).

3. **Carga el Código:**
   - Abre el IDE de Arduino.
   - Copia y pega el código anterior.
   - Selecciona el puerto y la placa correctos (`Herramientas > Puerto` y `Herramientas > Placa`).
   - Haz clic en `Cargar` para cargar el código en el Arduino.

4. **Verifica la Salida Serial:**
   - Abre el Monitor Serial (`Herramientas > Monitor Serial`) para verificar que el Arduino está enviando las lecturas de temperatura.
```



### IN PROGRESS ...
