# Copyright (C) 2021 Kritik Agarwal <https://github.com/Kritik007>

# Simulate a three nodes point-to-point network with duplex links between them. 
# Set the queue size vary the bandwidth and find the number of packetsdropped.

BEGIN {
	#include<stdio.h>
	count=0;
}
{
	if($1=="r")
		count++;
}
END {
	printf("The no.of packets dropped are: %d\n",count);
}
