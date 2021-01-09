import json
import logging
import paho.mqtt.client as mqtt
from influxdb import InfluxDBClient

influx_db_client = InfluxDBClient(host='localhost', port=8086)
influx_db_client.switch_database('db1')

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("#")

def create_data_object(topic, payload):
    data_obj = {}
    data_obj['measurement'] = 'data'
    data_obj['tags'] = {}
    data_obj['tags']['location'] = topic[0: topic.find('/')]
    data_obj['tags']['station'] = topic[topic.find('/') + 1 :]
    data_obj['time'] = payload['timestamp']
    data_obj['fields'] = {}
    for key in payload:
        if key != 'timestamp' and not isinstance(payload[key], str):
            # print(msg.topic.replace('/', '.') + '.' + key, payload[key])
            data_obj['fields'][key] = float(payload[key])
    # print("")
    return data_obj

def on_message(client, userdata, msg):
    # convert from bytes to str
    payload = msg.payload.decode()
    # convert from str to dict
    payload = json.loads(payload)
    # print('Received a message by topic [' + msg.topic + ']')
    # print('Data timestamp is: ' + payload['timestamp'])

    data = []
    data_obj = create_data_object(msg.topic, payload)
    # print(json.dumps(data_obj, indent = 4, sort_keys = True, default = str))
    data.append(data_obj)
    influx_db_client.write_points(data, database='db1', time_precision='s', protocol='json')

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("localhost", 1883, 60)
print('Connected to Broker!')

# client.loop_start()
client.loop_forever()
