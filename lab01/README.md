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