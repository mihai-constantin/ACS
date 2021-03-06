# Laborator 01 - Docker

## Comezi de baza
* docker image pull <image> : descarcare image din Docker Hub daca aceasta nu este deja pe local
* docker image ls : listare imagini prezente pe sistemul nostru
* docker container run <image> <command> : rularea unei comenzi folosind un container bazat pe imagea data
* docker container run alpine ls -l
* docker container run -it alpine : rulare iterativa a containerului bazat pe imaginea alpine
* docker container ls : listare containere care ruleaza
* docker container ls -a : listare tuturor containerelor rulate la un moment dat
* docker container run -d -it alpine : rulare in background a containerului
* docker attach <hash> : atasare la container (daca se iese din container, acesta se opreste automat)
* docker exec <hash> : atasare la container (daca se iese din container, acesta nu se opreste automat)
* docker stop <hash> : oprire container
* docker rm <hash> : stergere container
* docker image inspect <image> : afisare detalii cu privire la imagea data

## Dockerfile
* FROM <image> : imaginea de la care se pleaca

* COPY source dst : copiaza fisierul sursa de pe sistemul local la destinatie in containerul pe care il cream

* RUN <command> : rulare comanda in container

* EXPOSE <port-number> : expunere port in afara containerului

* CMD <command> : specificare comanda care va fi executata la pornirea containerului

* comanda din directorul unde se afla fisierul Dockerfile: docker build -t my-app .

* rulare imagine: docker container run -p 8888:5000 my-app

## Publicarea unei imagini intr-un registru
* docker login : autentificare pe Docker Hub
* docker tag my-app mihaiconstantin98/idp:demo : creare alias pentru imaginea my-app
* docker push mihaiconstantin09/idp:demo : publicare imagine pe Docker Hub
* docker container run -p 8888:5000 mihaiconstantin98/idp:demo : rulare imagine 

## Build automat aplicatie (linkare cu GitHub)
* in momentul in care se da push pe master, se ruleaza automat un build pe DockerHub
* se creaza o noua imagine cu tag-ul latest

## Networking
* bridge - permite comunicatia doar dintre containere aflate pe aceeasi masina Docker
* overlay - permite comunicatia dintre doua containere care ruleaza pe masini Docker diferite
* host
* macvlan
* none

### Comenzi
* creare containere
  * docker container run --name c1 -d -it alpine
  * docker container run --name c2 -d -it alpine 
* deconectare de la reteaua by default bridge
  * docker network disconnect bridge c1
  * docker network disconnect bridge c2
* creare retea de tip bridge
  * docker network create -d bridge c1-c2-bridge
* conectare la reteaua bridge creata anterior a containerelor c1 si c2
  * docker network connect c1-c2-bridge c1
  * docker network connect c1-c2-bridge c2

## Volume si bind mounts
* name volumes
  * docker container run --name c2 -d --mount source=test,target=/test alpine sh -c 'ping 8.8.8.8 > /test/ping.txt'
* bind mounts
  * docker container run --name c3 -d -it --mount type=bind,source="$(pwd)"/testidp/,target=/testidp2 alpine

## Exercitii
1. Comenzi de baza pentru imaginea busybox
2. Creare imagine pe baza de Dockerfile
    * docker build -t my-app .
    * docker container run -p 12345:8080 my-app
3. Aplicatie de adaugare de carti intr-o biblioteca
    ```
    Creare container pentru baza de date : laborator1-db

    docker network create -d bridge laborator1-db-network \
    docker volume create laborator1-db-persistent-volume \ 
    docker run -d \
    -it \
    --name laborator1-db \
    --mount type=bind,source="$(pwd)"/init-db.sql,target=/docker-entrypoint-initdb.d/init-db.sql \
    --mount source=laborator1-db-persistent-volume,target=/var/lib/postgresql/data \
    --network laborator1-db-network \
    --env POSTGRES_USER=admin \
    --env POSTGRES_PASSWORD=admin \
    --env POSTGRES_DB=books \
    postgres:latest
    ```

    ```
    Creare container pentru aplicatie : laborator1-api

    docker build -t api-laborator-1-image . \
    docker run -d \
    -it \
    --name laborator1-api \
    --network laborator1-db-network \
    -p 5555:80 \
    --env PGUSER=admin \
    --env PGPASSWORD=admin \
    --env PGDATABASE=books \
    --env PGHOST=laborator1-db \
    --env PGPORT=5432 \
    <hash-api-laborator-1-image>
    ```
    