# Copyright (C) 2021 Kritik Agarwal <https://github.com/Kritik007>

# Simulate a three nodes point-to-point network with duplex links between them. 
# Set the queue size vary the bandwidth and find the number of packetsdropped.

set ns [new Simulator]
set nf [open first.nam w]
$ns namtrace-all $nf
set tr [open first.tr w]
$ns trace-all $tr
  
set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]

$ns duplex-link $n0 $n1 1Mb 10ms DropTail
$ns duplex-link $n1 $n2 512Kb 10ms DropTail

set udp0 [new Agent/UDP]
$ns attach-agent $n0 $udp0

$ns queue-limit $n0 $n1 10

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0

set null0 [new Agent/Null] 
$ns attach-agent $n2 $null0
$ns connect $udp0 $null0

$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"

proc finish {} {
        global ns nf tr
        $ns flush-trace
        close $nf
        close $tr        
        exec nam first.nam &
        exec awk -f first.awk first.tr &
        exit 0
        }
        
 $ns at 5.0 "finish"
 $ns run
