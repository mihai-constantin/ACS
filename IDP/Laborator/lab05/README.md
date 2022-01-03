# Laborator 05 - API Gateway. Kong

* Accesare rute fara a folosi in cererea http valoarea portului
  * pentru serviciul de books si pentru adminer

* Restrictionare acces la serviciul de books pe baza unor chei + ACL

```bash
docker stack deploy -c docker-compose-swarm-kong.yml lab05
docker stack ps lab05
docker service ls
```

* JWT Token. Prometheus + Grafana
```bash
docker stack deploy -c docker-compose-swarm-kong-plugins.yml lab05
```
  * vizualizare json kong: ip:8001
  * prometheus: ip:9090
  * grafana: ip:3000
    * importare [dashboard](https://grafana.com/grafana/dashboards/7424) kong
