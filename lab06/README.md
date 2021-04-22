# Laborator 06 - Portainer. CI/CD

```bash
docker stack deploy -c docker-compose-swarm-kong-plugins.yml lab06
docker stack ps lab06
docker service ls
```

* JWT Token. Prometheus + Grafana
  * vizualizare json kong: ip:8001
  * prometheus: ip:9090
  * grafana: ip:3000
    * importare [dashboard](https://grafana.com/grafana/dashboards/7424) kong

```bash
docker stack deploy -c portainer.yml portainer
```

* Dashboard Portainer: docker-machine-ip:9000

<img src="skel/portainer.png" alt="drawing" />
