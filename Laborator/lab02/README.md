# Laborator 02 - Docker Compose

## Comezi de baza

```bash
docker-compose start                       # pornește containerele
docker-compose stop                        # oprește containerele
docker-compose pause                       # pune în stare de pauză containerele unui serviciu (se trimite SIGPAUSE)
docker-compose unpause                     # scoate din starea de pauză containerele
docker-compose ps                          # listează containerele active
docker-compose up                          # face build, recreează, pornește și atașeaza containere la un serviciu
docker-compose up -d                       # serviciile rulează în fundal, detașate de terminalul care le-a inițializat
docker-compose up --build                  # creează imaginile înainte de pornire
docker-compose -f my-docker-compose.yml up # se folosește fișierul de Compose specificat în loc de cel implicit
docker-compose down                        # oprește containerele și le șterge, împreună cu rețelele, volumele și imaginile create la up
docker-compose rm                          # șterge toate containerele oprite (se poate specifica la final și numele containerului care trebuie șters)
docker-compose rm -s -v                    # cu -s se opresc toate containerele și cu -v se șterg și volumele anonime atașate
```
## Exercitii
1. Docker compose pentru api de carti de la lab 01
2. Adaugare serviciu de adminer pentru baza de date 
    * docker-compose -f docker-compose-full.yml up --build
3. Secrete. Spargere docker-compose in 2 parti
    * docker-compose -f docker-compose.yml -f docker-compose-secrets.yml up --build
  