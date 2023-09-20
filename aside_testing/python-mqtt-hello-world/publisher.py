#!python
# -*- coding: utf-8; mode: python -*-

import json
import time
import random
import paho.mqtt.client as mqtt
import mqtt_config as cfg

IDENTIFIER = 'sensor01'

#Función que simula lectura de un sensor de temperatura
def take_reading():
    return {
        'identificador': IDENTIFIER,
        'valor': random.randint(20, 40),
        'unidad': 'Celsius',
        'timestamp': time.time()
    }


def main():
    publisher = mqtt.Client(client_id='test_publisher', clean_session=False)
    publisher.username_pw_set(cfg.mqtt_credentials["user"], cfg.mqtt_credentials["pwd"])
    publisher.connect(host=cfg.mqtt_broker["host"], port=cfg.mqtt_broker["port"])

    while 1:
        read = take_reading()
        print("Publicando: {}".format(read))

        publisher.publish(
            'temperature/{}'.format(IDENTIFIER),
            json.dumps(read)
        )

        time.sleep(2)


if __name__ == '__main__':
    main()

sys.exit(0)