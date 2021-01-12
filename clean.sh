docker stack rm sprc3
docker service rm registry
docker swarm leave --force

if [[ $* == *--volumes* ]]; then
  docker volume rm sprc3_grafana-volume sprc3_influxdb-volume
fi