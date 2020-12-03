# Laborator 5 - Protocoale pentru IoT. MQTT

## Task1 - Build de imagine
* creare container pe baza imaginii de eclipse-mosquitto
    * docker pull eclipse-mosquitto
    * docker run -it -p 1883:1883 -p 9001:9001 eclipse-mosquitto
    
## Task2 - Aplicatie de chat
* conectare la container
* subscribe la sprc/chat/#
* afisare mesaje la care este abonat
* citire mesaje de la tastatura + publish la un topic de forma /sprc/chat/<nume_student>

## Task 3 - Conectare la server
* in loc de localhost se foloseste broker.hivemq.com
