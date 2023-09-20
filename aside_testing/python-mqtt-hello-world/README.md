# MQTT y python
Este ejemplo consiste de un suscriptor y un publicador. El publicador simula ser un sensor de temperatura (genera datos aleatorios en formato json) y los publica en un canal. El suscriptor está suscrito a ese canal. En la conexión usa credenciales, y se pueden modificar estas, la dirección y el puerto desde [`mqtt_config.py`](mqtt_config.py)

# Pasos:
1. Inicia el broker con mosquitto: asegúrate que esté iniciado el Servicio en Windows, y ejecuta `mosquitto -v` desde una terminal para ver el puerto (suele ser 1883) y los logs
2. Ejecuta `publisher.py`
3. Ejecuta `subscriber.py`

# Dependencias
- python3-paho-mqtt:  https://pypi.org/project/paho-mqtt/
- mosquitto: https://mosquitto.org/download/