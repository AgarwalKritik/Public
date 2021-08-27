# Copyright (C) 2021 Kritik Agarwal <https://github.com/Kritik007>

# Simulate a four node point-to-point network, and connect the links as follows: n0-n2, n1-n2 and n2-n3. 
# Apply TCP agent between n0-n3 and UDP n1-n3. 
# Apply relevant applications over TCP and UDP agents changing the parameter and determine the number of packets by TCP/UDP.

set ns [new Simulator]
$ns color 0 blue
$ns color 1 green
set nf [open second.nam w]
$ns namtrace-all $nf
set tr [open second.tr w]
$ns trace-all $tr

set n0 [$ns node]
set n1 [$ns node]
set n2 [$ns node]
set n3 [$ns node]

$ns duplex-link $n0 $n2 1Mb 10ms DropTail
$ns duplex-link-op $n0 $n2 orient right-down
$ns duplex-link $n1 $n2 1Mb 10ms DropTail
$ns duplex-link-op $n1 $n2 orient right-up
$ns duplex-link $n2 $n3 1Mb 10ms DropTail
$ns duplex-link-op $n2 $n3 orient right

$ns queue-limit $n0 $n2 10
$ns queue-limit $n1 $n2 10
$ns queue-limit $n2 $n3 10

set tcp0 [new Agent/TCP]
$tcp0 set fid_ 0
$ns attach-agent $n0 $tcp0
set sink0 [new Agent/TCPSink]
$ns attach-agent $n3 $sink0
$ns connect $tcp0 $sink0

set ftp0 [new Application/FTP]
$ftp0 attach-agent $tcp0

Agent/TCP set packetSize_ 1000

set udp0 [new Agent/UDP]
$udp0 set fid_ 1
$ns attach-agent $n1 $udp0
set null0 [new Agent/Null] 
$ns attach-agent $n3 $null0
$ns connect $udp0 $null0

set cbr0 [new Application/Traffic/CBR]
$cbr0 set packetSize_ 500
$cbr0 set interval_ 0.005
$cbr0 attach-agent $udp0

$ns at 0.75 "$ftp0 start"
$ns at 4.75 "$ftp0 stop"

$ns at 0.5 "$cbr0 start"
$ns at 4.5 "$cbr0 stop"

proc finish {} {
        global ns nf tr
        $ns flush-trace
        close $nf
        close $tr        
        exec nam second.nam &
        exec awk -f second.awk second.tr &
        exit 0
        }

$ns at 5.0 "finish"
$ns run
