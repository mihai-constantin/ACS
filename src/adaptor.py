import json
import paho.mqtt.client as mqtt

def on_connect(client, userdata, flags, rc):
    print("Connected with result code " + str(rc))
    client.subscribe("#")

def on_message(client, userdata, msg):
    # print(msg.topic + "  " + str(msg.payload))
    
    # convert from bytes to str
    payload = msg.payload.decode()
    # convert from str to dict
    payload = json.loads(payload)
    # print ('=== MESSAGE ===')
    # print(json.dumps(payload, indent = 4, sort_keys = True, default = str))
    print('Received a message by topic [' + msg.topic + ']')
    print('Data timestamp is: ' + payload['timestamp'])
    for key in payload:
        if key != 'timestamp' and not isinstance(payload[key], str):
            print(msg.topic.replace('/', '.') + '.' + key, payload[key])
    print()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

client.connect("localhost", 1883, 60)

# client.loop_start()
client.loop_forever()