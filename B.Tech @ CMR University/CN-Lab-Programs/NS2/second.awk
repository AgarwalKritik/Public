# Copyright (C) 2021 Kritik Agarwal <https://github.com/Kritik007>

# Simulate a four node point-to-point network, and connect the links as follows: n0-n2, n1-n2 and n2-n3. 
# Apply TCP agent between n0-n3 and UDP n1-n3. 
# Apply relevant applications over TCP and UDP agents changing the parameter and determine the number of packets by TCP/UDP.

BEGIN {
	#include<stdio.h>
	countu=0;
	countt=0;
}
{
	if($5=="cbr")
		countu++;
	if($5=="tcp")
		countt++;
}
END {
	printf("\nNo. of UDP Packets = %d \nNo. of TCP Packets = %d\n\n",countu,countt);
}
