# Laborator 4 - Persistenta in Docker Swarm - NFS, GlusterFS, SSHFS

## NFS - Network File System
* nu ofera criptare

```bash
lab04$ docker run -d --name nfs --privileged -v nfsshare -e SHARED_DIRECTORY=/nfsshare itsthenetwork/nfs-server-alpine:latest # creare container pentru server-ul de nfs
```

```Dockerfile
volumes:
    db-data-nfs:
        driver: local
        driver_opts:
           type: nfs
           o: "nfsvers=3,addr=192.168.99.1,nolock,soft,rw"
           device: :/database/data
    db-config-nfs:
        driver: local
        driver_opts:
           type: nfs
           o: "nfsvers=3,addr=192.168.99.1,nolock,soft,rw"
           device: :/database/config
```

## GlusterFS
* nu ofera criptare

## SSHFS
* ofera criptare
* [sandbox](https://training.play-with-docker.com/docker-volume-sshfs/)
