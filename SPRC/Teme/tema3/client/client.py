import random
from random import randint
from datetime import datetime, timedelta
import json
import time

import paho.mqtt.client as mqtt

locations = ['UPB', 'UMFCD']
stations = ['RPi_1', 'RPi_2', 'RPi_3']
metrics = ['BAT', 'HUMID', 'TMP', 'AQI', 'RSSI', 'Alarm', 'status', 'timestamp']
metric_values = {}

def init_metrics():
  for metric in metrics:
    metric_values[metric] = {}
    
  for station in stations:
    for metric in metrics:
      metric_values[metric][station] = random.uniform(25.0, 50.0)

def generate_date(min_year = 2010, max_year = datetime.now().year - 1):
  start = datetime(min_year, 1, 1, 00, 00, 00)
  years = max_year - min_year + 1
  end = start + timedelta(days = 365 * years)
  return start + (end - start) * random.random()

def create_payload(data, indices, station):
  for idx in indices:
    if metrics[idx] == 'status':
      data[metrics[idx]] = 'OK'
    elif metrics[idx] != 'timestamp':
      val = metric_values[metrics[idx]][station]
      percentage = random.uniform(0, 0.01)
      k = random.randint(0, 1)
      data[metrics[idx]] = val + val * percentage if k == 0 else val - val * percentage
      metric_values[metrics[idx]][station] = data[metrics[idx]]

  return json.dumps(data, default = str)

def create_message(data, indices, idx_location, station):
  
  return {
    'topic': locations[idx_location] + "/",
    'payload': create_payload(data, indices, station)
  }

def on_connect(client, userdata, flags, rc):
  print("Connected with result code " + str(rc))

def on_message(client, userdata, msg):
  print(msg.topic + "  " + str(msg.payload))

# init values for metrics
init_metrics()

client = mqtt.Client()
client.on_connect = on_connect
client.on_message = on_message

# connect to mosquitto broker
client.connect("localhost", 1883, 60)
client.loop_start()

while True:
  # generate between 3 to 6 metrics indices
  indices = random.sample(range(0, len(metrics)), randint(6, 8))

  # generate topic and station
  idx_location = randint(0, len(locations) - 1)

  data = {}
  data['timestamp'] = datetime.now() - timedelta(hours = 2) if 7 in indices else generate_date()
  
  for station in stations:
    message = create_message(data, indices, idx_location, station)
    message['topic'] = message['topic'] + station

    # print('Message sent to broker')
    # print(json.dumps(message, indent = 4, sort_keys = True, default = str))

    # send message to broker
    client.publish(message['topic'], message['payload'])
    time.sleep(1)

  time.sleep(10)
