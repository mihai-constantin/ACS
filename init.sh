# docker swarm init
docker swarm init

# set up a docker registry
docker service create --name registry --publish published=5000,target=5000 registry:2

# check status
docker service ls

docker-compose up -d --build
docker-compose down --volumes

# push the generated image to the registry
docker-compose push
