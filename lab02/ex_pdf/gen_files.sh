#!/bin/bash

mkdir -p files
for i in $(seq 0 99); do
	chunk=$(($RANDOM))
	base64 /dev/urandom | head -c ${chunk} > files/f${i}
done
