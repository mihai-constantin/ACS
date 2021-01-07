import random
from random import randint
from datetime import datetime, timedelta
import json

import paho.mqtt.client as mqtt

topics = ['UPB', 'UMFCD', 'Mihai', 'Damian', 'Oana']
stations = ['RPi_1', 'RPi_2', 'RPi_3', 'RPi_4']
properties = ['BAT', 'HUMID', 'PRJ', 'TMP', 'AQI', 'RSSI', 'Alarm', 'status', 'timestamp']

def generate_date(min_year = 2010, max_year = datetime.now().year - 1):
  start = datetime(min_year, 1, 1, 00, 00, 00)
  years = max_year - min_year + 1
  end = start + timedelta(days = 365 * years)
  return start + (end - start) * random.random()

def create_payload():
  # generate between 3 to 6 properties indices
  indices = random.sample(range(0, len(properties)), randint(3, 6))

  data = {}
  for idx in indices:
    if properties[idx] == 'status':
      data[properties[idx]] = 'OK'
    elif properties[idx] == 'timestamp':
      data[properties[idx]] = generate_date()
    else:
      data[properties[idx]] = randint(0, 1000)

  if not 'timestamp' in data:
    data['timestamp'] = datetime.now()

  # return data
  return json.dumps(data, default = str)

def create_message():
  # generate topic and station
  idx_topic = randint(0, len(topics) - 1)
  idx_station = randint(0, len(stations) - 1)

  return {
    'topic': topics[idx_topic] + "/" + stations[idx_station],
    'payload': create_payload()
  }

def on_connect(client, userdata, flags, rc):
  print("Connected with result code " + str(rc))

def on_message(client, userdata, msg):
  print(msg.topic + "  " + str(msg.payload))

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# connect to mosquitto broker
client.connect("localhost", 1883, 60)

message = create_message()
print('Message sent to broker')
print(json.dumps(message, indent = 4, sort_keys = True, default = str))

# send message to broker
print(json.dumps(message['payload']))
client.publish(message['topic'], message['payload'])
