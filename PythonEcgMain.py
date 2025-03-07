# python 3.11

import random
import csv
from paho.mqtt import client as mqtt_client


broker = 'BrokerName'
port = 1883
topic = "arduino/simple"
# Generate a Client ID with the subscribe prefix.
client_id = f'subscribe-{random.randint(0, 100)}'
# username = 'emqx'
# password = 'public'


def connect_mqtt() -> mqtt_client:
    def on_connect(client, userdata, flags, rc):
        if rc == 0:
            print("Connected to MQTT Broker!")
        else:
            print("Failed to connect, return code %d\n", rc)

    client = mqtt_client.Client()
    # client.username_pw_set(username, password)
    client.on_connect = on_connect
    client.connect(broker, port)
    return client


def subscribe(client: mqtt_client):
    def on_message(client, userdata, msg):
        print(msg.payload.decode())
        with open('ValueHeart.csv', 'a+', newline='') as csvfile:
            spamwriter = csv.writer(csvfile, delimiter =',',quotechar =',',quoting=csv.QUOTE_MINIMAL)
            variable =msg.payload.decode()
            spamwriter.writerow([f'{variable}'])
            
    client.subscribe(topic)
    client.on_message = on_message


def run():
    client = connect_mqtt()
    subscribe(client)
    client.loop_forever()


if __name__ == '__main__':
    run()
