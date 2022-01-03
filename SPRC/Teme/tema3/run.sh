# docker swarm init
docker swarm init

# set up a docker registry
docker service create --name registry --publish published=5000,target=5000 registry:2

# check status
docker service ls

# build images
docker build adaptor/ --tag 127.0.0.1:5000/sprc3_adaptor
# docker build client/ --tag 127.0.0.1:5000/sprc3_client
docker build grafana/ --tag 127.0.0.1:5000/sprc3_grafana

# push images to registry
docker push 127.0.0.1:5000/sprc3_adaptor
# docker push 127.0.0.1:5000/sprc3_client
docker push 127.0.0.1:5000/sprc3_grafana

# deploy app
docker stack deploy -c stack.yml sprc3
