# Copyright (C) 2021 Kritik Agarwal <https://github.com/Kritik007>

# Simulate the transmission of ping messages over a network topology 
# consisting of 6 nodes and find the number of packets dropped due to congestion.

BEGIN {
	#include<stdio.h>
	count=0;
}
{
	if($1=="d")
		count++;
}
END {
	printf("The no.of drop packets  are:%d\n",count);
}
