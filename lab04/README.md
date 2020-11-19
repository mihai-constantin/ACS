# Laborator 4 - Docker

## Task1 - Build de imagine pe baza unui Dockerfile

* build de imagine cu nume specific (task1): docker build -t task1 .
* rulare container: docker container run --name container-task1 -p 8080:80 **<image-hash**

## Task2 - Docker compose
* rulare de 2 microservicii pe baza unui docker-compose
* rulare pe portul 8081 al host-ului (mapare cu portul 80 din container)
* creare de volum pentru serviciul wordpress pentru persistenta datelor intre rulari succesive
* comanda rulare: docker-compose up
* stergere: docker-compose down --volumes
